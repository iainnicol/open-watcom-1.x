/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


//
// WF77AUX  : auxiliary information processing
//

#include "ftnstd.h"
#include "global.h"
#include "fcgbls.h"
#include "wf77aux.h"
#include "errcod.h"
#include "cpopt.h"
#include "progsw.h"
#include "fmemmgr.h"
#include "ferror.h"

#if _OPT_CG == _ON
  #include "fio.h"
  #include "sdfile.h"
  #if ( _TARGET == _8086 || _TARGET == _80386 )
    #include "asminlin.h"
  #elif ( _TARGET == _AXP || _TARGET == _PPC )
    #include "asinline.h"
  #else
    #error Unknow Target
  #endif
#endif

#include <string.h>
#include <ctype.h>
#if _OPT_CG == _ON
#include <sys/types.h>
#include <sys/stat.h>
#endif


extern  int             KwLookUp(char **,int,char *,int,int);
extern  int             MkHexConst(char *,char *,int);
extern  void            Suicide(void);
extern  char            *SkipBlanks(char *);
extern  int             Spawn(void (*)());
extern  void            ReadSrc(void);
extern  aux_info        *AuxLookupName(char *,int);
extern  sym_id          SymFind(char *,uint);
extern  void            FreeChain(void **);

static  aux_info        *CurrAux;
static  char            *TokStart;
static  char            *TokEnd;
static  aux_info        *AliasInfo;
static  char            SymName[MAX_SYMLEN];
static  int             SymLen;

#if _OPT_CG == _ON

#if ( _TARGET == _8086 || _TARGET == _80386 )
static  arr_info        *ArrayInfo;
#endif

extern  char            *RegNames[];
extern  hw_reg_set      RegValue[];
extern  byte            MaxReg;
#if _TARGET == _8086
extern  hw_reg_set      WinParms[];
#elif _TARGET == _80386
extern  hw_reg_set      StackParms[];
#endif
extern  aux_info        IFInfo;
extern  aux_info        IFCharInfo;
extern  aux_info        IFChar2Info;
extern  aux_info        IFVarInfo;
extern  aux_info        IFXInfo;
extern  aux_info        CoRtnInfo;
extern  aux_info        RtRtnInfo;
extern  aux_info        RtVarInfo;
extern  aux_info        RtStopInfo;

extern  char            MsHexConst[];
extern  char            MsPragCallBytes[];
extern  char            MsArray[];

#if _TARGET == _8086

#define _FLIBM          5
#define _FLIB7M         6
#define _FLIBL          5
#define _FLIB7L         6
#define _CLIBM          5
#define _CLIBL          5
#define _MATHM          5
#define _MATH7M         7
#define _MATHL          5
#define _MATH7L         7
#define _EMU87          5
#define _NOEMU87        7
#define _WRESL          5
#define _WRESM          5

static  char            _flibm[] = { "flibm" };
static  char            _flib7m[] = { "flib7m" };
static  char            _flibl[] = { "flibl" };
static  char            _flib7l[] = { "flib7l" };
static  char            _clibm[] = { "clibm" };
static  char            _clibl[] = { "clibl" };
static  char            _mathm[] = { "mathm" };
static  char            _math7m[] = { "math87m" };
static  char            _mathl[] = { "mathl" };
static  char            _math7l[] = { "math87l" };
static  char            _emu87[] = { "emu87" };
static  char            _noemu87[] = { "noemu87" };
static  char            _wresl[] = { "wresl" };
static  char            _wresm[] = { "wresm" };

#elif _TARGET == _80386

#define _FLIB           4
#define _FLIB7          5
#define _FLIBS          5
#define _FLIB7S         6
#define _CLIB           6
#define _CLIBS          6
#define _MATH           6
#define _MATHS          6
#define _MATH7          8
#define _MATH7S         8
#define _EMU387         6
#define _NOEMU387       8
#define _WRESF          5
#define _WRESFS         6

static  char            _flib[] = { "flib" };
static  char            _flibs[] = { "flibs" };
static  char            _flib7[] = { "flib7" };
static  char            _flib7s[] = { "flib7s" };
static  char            _clib[] = { "clib3r" };
static  char            _clibs[] = { "clib3s" };
static  char            _math[] = { "math3r" };
static  char            _maths[] = { "math3s" };
static  char            _math7[] = { "math387r" };
static  char            _math7s[] = { "math387s" };
static  char            _emu387[] = { "emu387" };
static  char            _noemu387[] = { "noemu387" };
static  char            _wresf[] = { "wresf" };
static  char            _wresfs[] = { "wresfs" };

#elif _TARGET == _AXP

#define _FLIB           4
#define _CLIB           4
#define _MATH           4
#define _WRESAXP        7

static  char            _flib[] = { "flib" };
static  char            _clib[] = { "clib" };
static  char            _math[] = { "math" };
static  char            _wresaxp[] = { "wresaxp" };

#elif _TARGET == _PPC

#define _FLIB           4
#define _CLIB           4
#define _MATH           4
#define _WRESPPC        7

static  char            _flib[] = { "flib" };
static  char            _clib[] = { "clib" };
static  char            _math[] = { "math" };
static  char            _wresppc[] = { "wresppc" };

#else
  #error Unknown Platform
#endif

#define MAX_REG_SETS    16
#define MAXIMUM_BYTESEQ 127

#if ( _TARGET == _8086 || _TARGET == _80386 )
  #define ASM_CODE_BUFF_TYPE    char*
#elif _TARGET == _AXP || _TARGET == _PPC
  #define AsmSymFini    AsmFini
  #define CodeBuffer    AsmCodeBuffer
  #define Address       AsmCodeAddress
  #define ASM_CODE_BUFF_TYPE    uint_32*
#else
  #error Unknown Target
#endif

#else

#if _8087 == _ON
  #define _WFLIB                6
  static  char            _wflib[] = { "wflib7" };
  #if _TARGET == _80386
    #define _FLIB                       5
    static  char            _flib[] = { "flib7" };
    #define _MATH               8
    static  char            _math[] = { "math387r" };
    #define _NOEMU              8
    static  char            _noemu[] = { "noemu387" };
  #else
    #define _FLIB                       6
    static  char            _flib[] = { "flib7l" };
    #define _MATH               7
    static  char            _math[] = { "math87l" };
    #define _NOEMU              7
    static  char            _noemu[] = { "noemu87" };
  #endif
#else
  #define _WFLIB                5
  static  char            _wflib[] = { "wflib" };
  #if _TARGET == _80386
    #define _FLIB                       4
    static  char            _flib[] = { "flib" };
    #define _MATH               6
    static  char            _math[] = { "math3r" };
  #else
    #define _FLIB                       5
    static  char            _flib[] = { "flibl" };
    #define _MATH               5
    static  char            _math[] = { "mathl" };
  #endif
#endif

#if _TARGET == _80386
  #define _CLIB         6
  static  char            _clib[] = { "clib3r" };
  #define _WRES         5
  static  char            _wres[] = { "wresf" };
#else
  #define _CLIB         5
  static  char            _clib[] = { "clibl" };
  #define _WRES         5
  static  char            _wres[] = { "wresl" };
#endif

#endif

#if _OPT_CG == _ON
  #if _TARGET == _80386
    static      char    __Syscall[] = { "aux __syscall \"*\""
                                    "parm caller []"
                                    "value struct struct caller []"
                                    "modify [eax ecx edx]" };
    static      char    __Cdecl[] =   { "aux __cdecl \"_*\""
                                    "parm caller loadds []"
                                    "value struct float struct routine [eax]"
                                    "modify [eax ebx ecx edx]" };
    static      char    __Pascal[] =  { "aux __pascal \"^\""
                                    "parm reverse routine []"
                                    "value struct float struct caller []"
                                    "modify [eax ebx ecx edx]" };
    static      char    __Stdcall[] = { "aux __stdcall \"_*@#\""
                                    "parm routine []"
                                    "value struct []"
                                    "modify [eax ecx edx]" };
  #elif _TARGET == _8086
    static      char    __Pascal[] =  { "aux __pascal \"^\""
                                    "parm routine reverse []"
                                    "value struct float struct caller []"
                                    "modify [ax bx cx dx]" };
    static      char    __Cdecl[] =   { "aux __cdecl \"_*\""
                                    "parm caller []"
                                    "value struct float struct routine [ax]"
                                    "modify [ax bx cx dx]" };
  #endif
#else
  #if _TARGET == _80386
    #if _OPSYS == _OS2
      static    char    __Syscall[] = { "aux __syscall \"*\"" };
    #endif
  #endif
  static        char    __Cdecl[] =   { "aux __cdecl \"_*\"" };
  static        char    __Pascal[] =  { "aux __pascal \"^\"" };
#endif

extern  aux_info        DefaultInfo;

default_lib             *DefaultLibs;
aux_info                *AuxInfo;
aux_info                FortranInfo;
aux_info                ProgramInfo;
#if _OPT_CG == _ON
dep_info                *DependencyInfo;
#endif


void            InitAuxInfo() {
//=============================

#if ( _OPT_CG == _ON )
#if ( _TARGET == _8086 || _TARGET == _80386 )
    int         cpu;
    int         fpu;
    int         use32;

#if _TARGET == _8086
    use32 = 0;
#elif _TARGET == _80386
    use32 = 1;
#endif
    cpu = 0;
    fpu = 0;
#if _TARGET == _8086
    if( CPUOpts & CPUOPT_80186 ) cpu = 1;
    if( CPUOpts & CPUOPT_80286 ) cpu = 2;
#endif
    if( CPUOpts & CPUOPT_80386 ) cpu = 3;
    if( CPUOpts & CPUOPT_80486 ) cpu = 4;
    if( CPUOpts & CPUOPT_80586 ) cpu = 5;
    if( CPUOpts & CPUOPT_80686 ) cpu = 6;
    if( CPUOpts & ( CPUOPT_FPI87 | CPUOPT_FPI ) ) fpu = 1;
    AsmInit( cpu, fpu, use32, 1 );
#elif _TARGET == _AXP || _TARGET == _PPC
    AsmInit();
#else
    #error Unknown Target
#endif
#endif

    DefaultLibs = NULL;
    AuxInfo = NULL;
#if _OPT_CG == _ON
    DependencyInfo = NULL;
#if _TARGET == _8086 || _TARGET == _80386

#if _TARGET == _8086
    // Change auxiliary information for calls to run-time routines to match
    // the options used to compile the run-time routines
    if( CGOpts & CGOPT_M_LARGE ) {
        if( !(CGOpts & CGOPT_WINDOWS) ) {
            HW_CTurnOff( IFXInfo.save_info, HW_DS );
            HW_CTurnOff( RtRtnInfo.save_info, HW_DS );
            HW_CTurnOff( RtStopInfo.save_info, HW_DS );
            HW_CTurnOff( RtVarInfo.save_info, HW_DS );
            HW_CTurnOff( CoRtnInfo.save_info, HW_DS );
            HW_CTurnOff( IFInfo.save_info, HW_DS );
            HW_CTurnOff( IFCharInfo.save_info, HW_DS );
            HW_CTurnOff( IFChar2Info.save_info, HW_DS );
            HW_CTurnOff( IFVarInfo.save_info, HW_DS );
        }
        HW_CTurnOff( IFXInfo.save_info, HW_ES );
        HW_CTurnOff( RtRtnInfo.save_info, HW_ES );
        HW_CTurnOff( RtStopInfo.save_info, HW_ES );
        HW_CTurnOff( RtVarInfo.save_info, HW_ES );
        HW_CTurnOff( CoRtnInfo.save_info, HW_ES );
        HW_CTurnOff( IFInfo.save_info, HW_ES );
        HW_CTurnOff( IFCharInfo.save_info, HW_ES );
        HW_CTurnOff( IFChar2Info.save_info, HW_ES );
        HW_CTurnOff( IFVarInfo.save_info, HW_ES );
    }
#endif

    if( !(CGOpts & CGOPT_SEG_REGS) ) {
        if( _FloatingDS( CGOpts ) ) {
            HW_CTurnOff( DefaultInfo.save_info, HW_DS );
        }
        if( _FloatingES( CGOpts ) ) {
            HW_CTurnOff( DefaultInfo.save_info, HW_ES );
        }
#if _TARGET == _8086
        if( CPUOpts & (CPUOPT_80386 | CPUOPT_80486 | CPUOPT_80586 | CPUOPT_80686) ) {
#endif
            if( _FloatingFS( CGOpts ) ) {
                HW_CTurnOff( DefaultInfo.save_info, HW_FS );
            }
            if( _FloatingGS( CGOpts ) ) {
                HW_CTurnOff( DefaultInfo.save_info, HW_GS );
            }
#if _TARGET == _8086
        }
#endif
    }
    if( OZOpts & OZOPT_O_FRAME ) {
        DefaultInfo.call_info |= GENERATE_STACK_FRAME;
    }
#endif
#if _TARGET == _80386
    if( CGOpts & CGOPT_STK_ARGS ) {
        DefaultInfo.call_info |= CALLER_POPS | NO_8087_RETURNS;
        DefaultInfo.parm_info = StackParms;
        HW_CTurnOff( DefaultInfo.save_info, HW_EAX );
        HW_CTurnOff( DefaultInfo.save_info, HW_EDX );
        HW_CTurnOff( DefaultInfo.save_info, HW_ECX );
        HW_CTurnOff( DefaultInfo.save_info, HW_FLTS );

        IFXInfo.call_info |= CALLER_POPS | NO_8087_RETURNS;
        IFXInfo.parm_info = StackParms;

        HW_CTurnOff( IFXInfo.save_info, HW_FLTS );
        HW_CTurnOff( RtRtnInfo.save_info, HW_FLTS );
        HW_CTurnOff( RtStopInfo.save_info, HW_FLTS );
        HW_CTurnOff( RtVarInfo.save_info, HW_FLTS );
        HW_CTurnOff( CoRtnInfo.save_info, HW_FLTS );
        HW_CTurnOff( IFInfo.save_info, HW_FLTS );
        HW_CTurnOff( IFCharInfo.save_info, HW_FLTS );
        HW_CTurnOff( IFChar2Info.save_info, HW_FLTS );
        HW_CTurnOff( IFVarInfo.save_info, HW_FLTS );
    }
#endif
#if _TARGET == _8086
    if( CGOpts & CGOPT_WINDOWS ) {
        DefaultInfo.parm_info = WinParms;
        IFXInfo.parm_info = WinParms;
    }
#endif
#endif
    FortranInfo = DefaultInfo;
    ProgramInfo = DefaultInfo;
#if _OPT_CG == _ON
  #if _TARGET == _80386
    DoPragma( __Syscall );
    DoPragma( __Stdcall );
  #endif
#if _TARGET == _8086 || _TARGET == _80386
    DoPragma( __Pascal );
    DoPragma( __Cdecl );
#endif
#else
  #if _TARGET == _80386
    #if _OPSYS == _OS2
      DoPragma( __Syscall );
      CurrAux->call_info &= ~AUX_CALL_MASK;
      CurrAux->call_info = AUX_SYSCALL;
    #endif
  #endif
    DoPragma( __Cdecl );
    CurrAux->call_info &= ~AUX_CALL_MASK;
    CurrAux->call_info |= AUX_CDECL;
    DoPragma( __Pascal );
    CurrAux->call_info &= ~AUX_CALL_MASK;
    CurrAux->call_info |= AUX_PASCAL;
#endif
}


void            FiniAuxInfo() {
//=============================

    void        *next;

    while( AuxInfo != NULL ) {
        next = AuxInfo->link;
        FreeAuxEntry( AuxInfo );
        AuxInfo = next;
    }
    FreeAuxElements( &FortranInfo );
    FreeChain( &DefaultLibs );
    // in case of fatal error, FiniAuxInfo() is called
    // from TDPurge()
#if _OPT_CG == _ON
#if ( _TARGET == _8086 || _TARGET == _80386 )
    FreeChain( &ArrayInfo );
#endif
    FreeChain( &DependencyInfo );
    AsmSymFini();
#endif
}


#if _OPT_CG == _ON

void    SubAuxInit() {
//====================

#if ( _TARGET == _8086 || _TARGET == _80386 )
// Initialize aux information for a subprogram.

    ArrayInfo = NULL;
#endif
}


void    SubAuxFini() {
//====================

#if ( _TARGET == _8086 || _TARGET == _80386 )
// Finalize aux information for a subprogram.

    arr_info    *next;
    sym_id      arr;

    while( ArrayInfo != NULL ) {
        next = ArrayInfo->link;
        arr = SymFind( ArrayInfo->arr, strlen( ArrayInfo->arr ) );
        if( ( arr != NULL ) && ( arr->ns.flags & SY_SUBSCRIPTED ) &&
            ( arr->ns.typ != TY_CHAR ) &&
            ( ( arr->ns.flags & SY_SUB_PARM ) || _Allocatable( arr ) ) ) {
            arr->ns.si.va.dim_ext->dim_flags |= DIM_EXTENDED;
        }
        FMemFree( ArrayInfo );
        ArrayInfo = next;
    }
#endif
}

#if ( _TARGET == _8086 || _TARGET == _80386 )
static  void    AddArrayInfo( char *arr_name, uint arr_len ) {
//============================================================

// Process aux information for an array.

    arr_info    **arr;
    arr_info    *new_arr;

    for( arr = &ArrayInfo; *arr != NULL; arr = &(*arr)->link ) {
        if( strlen( &(*arr)->arr ) != arr_len ) continue;
        if( memcmp( &(*arr)->arr, arr_name, arr_len ) == 0 ) return;
    }
    new_arr = FMemAlloc( sizeof( arr_info ) + arr_len );
    new_arr->link = NULL;
    memcpy( &new_arr->arr, arr_name, arr_len );
    new_arr->arr[arr_len] = NULLCHAR;
    *arr = new_arr;
}
#endif

void    AddDependencyInfo( source *fi ) {
//=======================================

// Add dependency information for an included file.

    char        *p;
    dep_info    **dep;
    dep_info    *new_dep;
    struct stat stat_info;
    char        buff[MAX_FILE];

    p = _fullpath( buff, fi->name, MAX_FILE );
    if( p != NULL ) {
        for( dep = &DependencyInfo; *dep != NULL; dep = &(*dep)->link ) {
            if( strcmp( &(*dep)->fn, p ) == 0 ) return;
        }
        if( fstat( ((a_file *)(fi->fileptr))->handle, &stat_info ) != -1 ) {
            new_dep = FMemAlloc( sizeof( dep_info ) + strlen( p ) );
            new_dep->link = NULL;
            strcpy( &new_dep->fn, p );
            new_dep->time_stamp = stat_info.st_mtime;
            *dep = new_dep;
        }
    }
}

#endif


static  void    AddDefaultLib( char *lib_ptr, int lib_len, char priority ) {
//==========================================================================

    default_lib         **lib;
    default_lib         *new_lib;

#if _OPT_CG == _ON
    if( !( Options & OPT_DFLT_LIB ) ) return;
#endif
    for( lib = &DefaultLibs; *lib != NULL; lib = &(*lib)->link ) {
        if( strlen( &(*lib)->lib[1] ) != lib_len ) continue;
        if( memcmp( &(*lib)->lib[1], lib_ptr, lib_len ) == 0 ) return;
    }
    new_lib = FMemAlloc( sizeof( default_lib ) + lib_len );
    new_lib->link = NULL;
    new_lib->lib[0] = priority;
    memcpy( &new_lib->lib[1], lib_ptr, lib_len );
    new_lib->lib[1+lib_len] = NULLCHAR;
    *lib = new_lib;
}


void    DefaultLibInfo() {
//========================

#if _OPT_CG == _ON
#if _TARGET == _80386
    if( CGOpts & CGOPT_STK_ARGS ) {
        if( CPUOpts & CPUOPT_FPC ) {
            AddDefaultLib( _flibs, _FLIBS, '1' );
            AddDefaultLib( _maths, _MATHS, '1' );
        } else {
            AddDefaultLib( _flib7s, _FLIB7S, '1' );
            AddDefaultLib( _math7s, _MATH7S, '1' );
        }
        AddDefaultLib( _clibs, _CLIBS, '1' );
        if( Options & OPT_RESOURCES ) {
            AddDefaultLib( _wresfs, _WRESFS, '1' );
        }
    } else {
        if( CPUOpts & CPUOPT_FPC ) {
            AddDefaultLib( _flib, _FLIB, '1' );
            AddDefaultLib( _math, _MATH, '1' );
        } else {
            AddDefaultLib( _flib7, _FLIB7, '1' );
            AddDefaultLib( _math7, _MATH7, '1' );
        }
        AddDefaultLib( _clib, _CLIB, '1' );
        if( Options & OPT_RESOURCES ) {
            AddDefaultLib( _wresf, _WRESF, '1' );
        }
    }
    if( CPUOpts & CPUOPT_FPI ) {
        AddDefaultLib( _emu387, _EMU387, '1' );
    } else if( CPUOpts & CPUOPT_FPI87 ) {
        AddDefaultLib( _noemu387, _NOEMU387, '1' );
    }
#elif _TARGET == _8086
    if( CGOpts & CGOPT_M_MEDIUM ) {
        if( CPUOpts & CPUOPT_FPC ) {
            AddDefaultLib( _flibm, _FLIBM, '1' );
            AddDefaultLib( _mathm, _MATHM, '1' );
        } else {
            AddDefaultLib( _flib7m, _FLIB7M, '1' );
            AddDefaultLib( _math7m, _MATH7M, '1' );
        }
        AddDefaultLib( _clibm, _CLIBM, '1' );
        if( Options & OPT_RESOURCES ) {
            AddDefaultLib( _wresm, _WRESM, '1' );
        }
    } else {
        if( CPUOpts & CPUOPT_FPC ) {
            AddDefaultLib( _flibl, _FLIBL, '1' );
            AddDefaultLib( _mathl, _MATHL, '1' );
        } else {
            AddDefaultLib( _flib7l, _FLIB7L, '1' );
            AddDefaultLib( _math7l, _MATH7L, '1' );
        }
        AddDefaultLib( _clibl, _CLIBL, '1' );
        if( Options & OPT_RESOURCES ) {
            AddDefaultLib( _wresl, _WRESL, '1' );
        }
    }
    if( CPUOpts & CPUOPT_FPI ) {
        AddDefaultLib( _emu87, _EMU87, '1' );
    } else if( CPUOpts & CPUOPT_FPI87 ) {
        AddDefaultLib( _noemu87, _NOEMU87, '1' );
    }
#elif _TARGET == _AXP
    AddDefaultLib( _flib, _FLIB, '1' );
    AddDefaultLib( _math, _MATH, '1' );
    AddDefaultLib( _clib, _CLIB, '1' );
    if( Options & OPT_RESOURCES ) {
        AddDefaultLib( _wresaxp, _WRESAXP, '1' );
    }
#elif _TARGET == _PPC
    AddDefaultLib( _flib, _FLIB, '1' );
    AddDefaultLib( _math, _MATH, '1' );
    AddDefaultLib( _clib, _CLIB, '1' );
    if( Options & OPT_RESOURCES ) {
        AddDefaultLib( _wresppc, _WRESPPC, '1' );
    }
#else
  #error Unknown Platform
#endif
#else
    AddDefaultLib( _wflib, _WFLIB, '1' );
    AddDefaultLib( _flib, _FLIB, '1' );
    AddDefaultLib( _math, _MATH, '1' );
    AddDefaultLib( _clib, _CLIB, '1' );
    if( Options & OPT_RESOURCES ) {
        AddDefaultLib( _wres, _WRES, '1' );
    }
    #if _8087 == _ON
        AddDefaultLib( _noemu, _NOEMU, '1' );
    #endif
#endif
}


static  void    FreeAuxEntry( aux_info *aux ) {
//=============================================

    FreeAuxElements( aux );
    FMemFree( aux );
}


static  void    FreeAuxElements( aux_info *aux ) {
//================================================

    FreeArgList( aux );
#if _OPT_CG == _ON
    if( aux->parm_info != DefaultInfo.parm_info ) {
        FMemFree( aux->parm_info );
        aux->parm_info = DefaultInfo.parm_info;
    }
    if( aux->call_bytes != DefaultInfo.call_bytes ) {
        FMemFree( aux->call_bytes );
        aux->call_bytes = DefaultInfo.call_bytes;
    }
#endif
    if( aux->object_name != DefaultInfo.object_name ) {
        FMemFree( aux->object_name );
        aux->object_name = DefaultInfo.object_name;
    }
}


static  void    FreeArgList( aux_info *aux ) {
//============================================

    FreeChain( &aux->arg_info );
}


aux_info        *NewAuxEntry( char *name, int name_len ) {
//========================================================

    aux_info    *aux;

    aux = FMemAlloc( sizeof( aux_info ) + name_len );
    aux->sym_len = name_len;
    memcpy( aux->sym_name, name, name_len );
    aux->sym_name[ name_len ] = NULLCHAR;
    aux->link = AuxInfo;
#if _OPT_CG == _ON
    aux->parm_info = DefaultInfo.parm_info;
    aux->call_bytes = DefaultInfo.call_bytes;
#endif
    aux->object_name = DefaultInfo.object_name;
    aux->arg_info = NULL;
    AuxInfo = aux;
    return( aux );
}


static  bool    CurrToken( char *tok ) {
//======================================

    char    *ptr;

    ptr = TokStart;
    for(;;) {
        if( ptr == TokEnd ) break;
        if( toupper( *ptr ) != *tok ) break;
        ptr++;
        tok++;
    }
    if( ( ptr == TokEnd ) && ( *tok == '\0' ) ) return( TRUE );
    return( FALSE );
}


static  bool    RecToken( char *tok ) {
//=====================================

    if( CurrToken( tok ) ) {
        ScanToken();
        return( TRUE );
    }
    return( FALSE );
}


void            Pragma() {
//========================

// Process a pragma.

#if (_OPT_CG == _ON) && ( _TARGET == _8086 || _TARGET == _80386 )
    char        *arr;
    uint        arr_len;
#endif

    struct {
        unsigned f_far    : 1;
        unsigned f_far16  : 1;
        unsigned f_loadds : 1;
        unsigned f_export : 1;
        unsigned f_parm   : 1;
        unsigned f_value  : 1;
        unsigned f_modify : 1;
    } have;

    if( RecToken( "LIBRARY" ) ) {
        if( RecToken( "\0" ) ) {
            DefaultLibInfo();
        } else {
            while( !RecToken( "\0" ) ) {
                AddDefaultLib( TokStart, TokEnd - TokStart, '9' );
                ScanToken();
            }
        }
#if (_OPT_CG == _ON) && ( _TARGET == _8086 || _TARGET == _80386 )
    } else if( RecToken( "ARRAY" ) ) {
        SymbolId();
        TokUpper();
        arr = TokStart;
        arr_len = TokEnd - TokStart;
        ScanToken();
#if _TARGET == _80386
        if( RecToken( "FAR" ) ) {
            if( _SmallDataModel( CGOpts ) ) {
                AddArrayInfo( arr, arr_len );
            }
        }
#elif _TARGET == _8086
        if( RecToken( "FAR" ) ) {
            if( _SmallDataModel( CGOpts ) ) {
                AddArrayInfo( arr, arr_len );
            }
        } else if( RecToken( "HUGE" ) ) {
            if( CGOpts & CGOPT_M_LARGE ) {
                AddArrayInfo( arr, arr_len );
            }
        }
#endif
#endif
    } else {
        AliasInfo = &FortranInfo;
        if( RecToken( "LINKAGE" ) ) {
            ReqToken( "(" );
            SymbolName();
            ReqToken( "," );
            AliasName();
            ProcessAlias();
            ReqToken( ")" );
        } else {
            ReqToken( "AUX" );
            if( RecToken( "(" ) ) {
                AliasName();
                ReqToken( ")" );
            }
            SymbolName();
            ProcessAlias();
            ObjectName();

#if (_OPT_CG == _ON)
            have.f_far    = 0;
            have.f_loadds = 0;
            have.f_export = 0;
            have.f_value  = 0;
            have.f_modify = 0;
#endif
            have.f_parm   = 0;
            for( ;; ) {
                if( !have.f_parm && RecToken( "PARM" ) ) {
                    GetParmInfo();
                    have.f_parm = 1;
#if _OPT_CG == _ON
                } else if( !have.f_far && RecToken( "=" ) ) {
                    GetByteSeq();
#if ( _TARGET == _8086 || _TARGET == _80386 )
                    have.f_far = 1;
                } else if( !have.f_far && RecToken( "FAR" ) ) {
                    CurrAux->call_info |= FAR;
                    have.f_far = 1;
#if _TARGET == _80386
                } else if( !have.f_far16 && RecToken( "FAR16" ) ) {
                    CurrAux->call_info |= FAR16_CALL;
                    have.f_far16 = 1;
#endif
                } else if( !have.f_far && RecToken( "NEAR" ) ) {
                    CurrAux->call_info &= ~FAR;
                    have.f_far = 1;
                } else if( !have.f_loadds && RecToken( "LOADDS" ) ) {
                    CurrAux->call_info |= LOAD_DS_ON_ENTRY;
                    have.f_loadds = 1;
#endif
                } else if( !have.f_export && RecToken( "EXPORT" ) ) {
                    CurrAux->call_info |= DLL_EXPORT;
                    have.f_export = 1;
#if ( _TARGET == _8086 || _TARGET == _80386 )
                } else if( !have.f_value && RecToken( "VALUE" ) ) {
                    GetRetInfo();
                    have.f_value = 1;
#endif
                } else if( !have.f_value && RecToken( "ABORTS" ) ) {
                    CurrAux->call_info |= SUICIDAL;
                    have.f_value = 1;
#if ( _TARGET == _8086 || _TARGET == _80386 )
                } else if( !have.f_modify && RecToken( "MODIFY" ) ) {
                    GetSaveInfo();
                    have.f_modify = 1;
#endif
#endif
                } else {
                    break;
                }
            }
        }
    }
}


void    DoPragma( char *ptr ) {
//=============================

    int         status;

    TokStart = ptr;
    TokEnd = ptr;
    ScanToken();
    for(;;) {
        status = Spawn( &Pragma );
        if( status != 0 ) {
            if( ProgSw & PS_FATAL_ERROR ) {
                Suicide();
            }
#if _OPT_CG == _ON
            AsmSymFini();
#endif
            break;
        }
        if( RecToken( "\0" ) ) break;
    }
}


void    ProcPragma( char *ptr ) {
//===============================

#if _OPT_CG == _ON
    // don't process auxiliary pragma's until pass 2
    if( ProgSw & PS_DONT_GENERATE ) return;
#endif
    DoPragma( ptr );
}


static  void    ScanToken() {
//===========================

    char    *ptr;
    int     found_token;
    int     first;

    ptr = TokEnd;
    ptr = SkipBlanks( ptr );
    TokStart = ptr;
    first = TRUE;
    found_token = FALSE;
    for(;;) {
        switch( *ptr ) {
        case ' ' :
        case '\t' :
        case '\0' :
            found_token = TRUE;
            break;
        case '"' :
            if( first ) {
                for(;;) {
                    ++ptr;
                    if( *ptr == '\0' ) break;
                    if( *ptr == '"' ) {
                        ++ptr;
                        break;
                    }
                }
            }
            found_token = TRUE;
            break;
        case '[' :
        case ']' :
        case '(' :
        case ')' :
        case ',' :
        case '=' :
        case '*' :
            if( first ) {
                ++ptr;
            }
            found_token = TRUE;
            break;
        case '\\' :
            if( first ) {
                ReadSrc();
                ptr = SrcBuff;
                if( ( *ptr == '*' ) || ( *ptr == 'C' ) || ( *ptr == 'c' ) ) {
                    ++ptr;
                } else {
                    Error( PR_BAD_CONTINUATION );
                    Suicide();
                }
                ptr = SkipBlanks( ptr );
                TokStart = ptr;
            } else {
                found_token = TRUE;
            }
            break;
        default :
            first = FALSE;
            ptr++;
        }
        if( found_token ) break;
    }
    TokEnd = ptr;
}


#if ((_OPT_CG == _ON ) && ( _TARGET == _8086 || _TARGET == _80386))
static  void    TokUpper() {
//==========================

    char        *ptr;

    ptr = TokStart;
    while( ptr != TokEnd ) {
        *ptr = toupper( *ptr );
        ++ptr;
    }
}

#endif


static  void    ReqToken( char *tok ) {
//=====================================

    if( !RecToken( tok ) ) {
        *TokEnd = NULLCHAR;
        Error( PR_BAD_SYNTAX, tok, TokStart );
        Suicide();
    }
}


static  void            AliasName() {
//===================================

    aux_info    *alias;

    SymbolId();
    alias = AuxLookupName( TokStart, TokEnd - TokStart );
    if( alias != NULL ) {
        AliasInfo = alias;
    }
    ScanToken();
}


static  void            SymbolName() {
//====================================

    if( RecToken( "DEFAULT" ) ) {
        SymLen = 0;
    } else {
        SymbolId();
        SymLen = TokEnd - TokStart;
        if( SymLen > MAX_SYMLEN ) {
            SymLen = MAX_SYMLEN;
        }
        memcpy( SymName, TokStart, SymLen );
        ScanToken();
    }
}


static  void            ProcessAlias() {
//======================================

    if( SymLen == 0 ) { // "DEFAULT"
        CurrAux = AliasInfo;
    } else {
        CurrAux = AuxLookupName( SymName, SymLen );
        if( CurrAux != AliasInfo ) { // Consider: c$pragma aux (sp) sp
            if( CurrAux == NULL ) {
                CurrAux = NewAuxEntry( SymName, SymLen );
            } else {
                FreeAuxElements( CurrAux );
            }
        }
        CopyAuxInfo( CurrAux, AliasInfo );
    }
}


void            CopyAuxInfo( aux_info *dst, aux_info *src ) {
//===========================================================

    if( dst != src ) {
        dst->call_info = src->call_info;
#if _OPT_CG == _ON
        dst->save_info = src->save_info;
        dst->return_info = src->return_info;
        dst->struct_info = src->struct_info;
        if( src->parm_info != DefaultInfo.parm_info ) {
            DupParmInfo( dst, src );
        }
        if( src->call_bytes != DefaultInfo.call_bytes ) {
            DupCallBytes( dst, src );
        }
#endif
        if( src->object_name != DefaultInfo.object_name ) {
            DupObjectName( dst, src );
        }
        DupArgInfo( dst, src );
    }
}


#if _OPT_CG == _ON

static  void    DupCallBytes( aux_info *dst, aux_info *src ) {
//============================================================
#if _TARGET == _8086 || _TARGET == _80386

    byte_seq    *new_seq;
    uint        seq_len;
    seq_len = src->call_bytes->length & ~DO_FLOATING_FIXUPS;
    new_seq = FMemAlloc( sizeof( byte_seq ) + seq_len );
    memcpy( new_seq->data, src->call_bytes->data, seq_len );
    dst->call_bytes = new_seq;
    dst->call_bytes->length = src->call_bytes->length;

#elif _TARGET == _AXP || _TARGET == _PPC

    risc_byte_seq       *new_seq;
    uint                seq_len;
    byte_seq_reloc      **lnk;
    byte_seq_reloc      *new;
    byte_seq_reloc      *head;
    byte_seq_reloc      *reloc;

    seq_len = src->call_bytes->length;
    new_seq = FMemAlloc( sizeof( byte_seq ) + seq_len );
    memcpy( new_seq->data, src->call_bytes->data, seq_len );
    dst->call_bytes = new_seq;
    dst->call_bytes->length = src->call_bytes->length;

    head = NULL;
    lnk = &head;
    for( reloc = src->call_bytes->relocs; reloc; reloc = reloc->next ) {
        new = FMemAlloc( sizeof( byte_seq_reloc ) );
        new->off = reloc->off;
        new->type = reloc->type;
        new->sym = reloc->sym;
        new->next = NULL;
        *lnk = new;
        lnk = &new->next;
    }
    dst->call_bytes->relocs = head;

#else
  #error Unknown Target
#endif
}


static  void    DupParmInfo( aux_info *dst, aux_info *src ) {
//===========================================================

    hw_reg_set  *new_reg_set;
    hw_reg_set  *reg_set;
    int         size;

    reg_set = src->parm_info;
    size = 0;
    while( !HW_CEqual( reg_set[ size ], HW_EMPTY ) ) {
        ++size;
    }
    ++size;
    new_reg_set = FMemAlloc( size * sizeof( hw_reg_set ) );
    memcpy( new_reg_set, reg_set, size * sizeof( hw_reg_set ) );
    dst->parm_info = new_reg_set;
}

#endif


static  void    DupObjectName( aux_info *dst, aux_info *src ) {
//=============================================================

    char        *new_name;

    new_name = FMemAlloc( strlen( src->object_name ) + sizeof( char ) );
    strcpy( new_name, src->object_name );
    dst->object_name = new_name;
}


static  void    DupArgInfo( aux_info *dst, aux_info *src ) {
//==========================================================

    pass_by     *new_arg;
    pass_by     *args;
    pass_by     **curr_arg;

    args = src->arg_info;
    curr_arg = &dst->arg_info;
    while( args != NULL ) {
        new_arg = FMemAlloc( sizeof( pass_by ) );
        new_arg->info = args->info;
        new_arg->link = NULL;
        *curr_arg = new_arg;
        curr_arg = &new_arg->link;
        args = args->link;
    }
}


static  void            SymbolId() {
//==================================

    char        *ptr;

    ptr = TokStart;
    if( ( isalpha( *ptr ) == 0 ) && ( *ptr != '$' ) && ( *ptr != '_' ) ) {
        Error( PR_SYMBOL_NAME );
        Suicide();
    }
    for(;;) {
        ptr++;
        if( ptr == TokEnd ) break;
        if( ( isalnum( *ptr ) == 0 ) && ( *ptr != '$' ) && ( *ptr != '_' ) ) {
            Error( PR_SYMBOL_NAME );
            Suicide();
        }
    }
}


static  void            ObjectName() {
//====================================

    int         obj_len;
    char        *name;

    if( *TokStart != '"' ) return;
    if( TokStart == TokEnd - sizeof( char ) ) Suicide();
    if( *(TokEnd - sizeof( char )) != '"' ) Suicide();
    obj_len = TokEnd - TokStart - 2*sizeof( char );
    name = FMemAlloc( obj_len + sizeof( char ) );
    if( CurrAux->object_name != DefaultInfo.object_name ) {
        FMemFree( CurrAux->object_name );
    }
    memcpy( name, TokStart + sizeof( char ), obj_len );
    name[ obj_len ] = NULLCHAR;
    CurrAux->object_name = name;
    ScanToken();
}


#if _OPT_CG == _ON

enum    sym_state       AsmQueryExternal( char *name ) {
//======================================================

    name = name;
    return( SYM_UNDEFINED );
}


#if ( _TARGET == _8086 || _TARGET == _80386 )
enum    sym_type        AsmQueryType( char *name ) {
//==================================================

    name = name;
    return( SYM_INT1 );
}


static  void    InsertFixups( unsigned char *buff, unsigned i ) {
//===============================================================
                        // additional slop in buffer to simplify the code
    unsigned char       temp[MAXIMUM_BYTESEQ+2*sizeof(byte)];
    struct asmfixup     *fix;
    struct asmfixup     *head;
    struct asmfixup     *chk;
    struct asmfixup     *next;
    struct asmfixup     **owner;
    byte                *dst;
    byte                *src;
    byte                *end;
    byte_seq            *seq;
    byte_seq_len        perform_fixups;
    char                *name;

    perform_fixups = 0;
    head = FixupHead;
    if( head != NULL ) {
        FixupHead = NULL;
        // sort the fixup list in increasing fixup_loc's
        for( fix = head; fix != NULL; fix = next ) {
            owner = &FixupHead;
            for( ;; ) {
                chk = *owner;
                if( chk == NULL ) break;
                if( chk->fixup_loc > fix->fixup_loc ) break;
                owner = &chk->next;
            }
            next = fix->next;
            fix->next = *owner;
            *owner = fix;
        }
        dst = temp;
        src = buff;
        end = src + i;
        fix = FixupHead;
        owner = &FixupHead;
        // insert fixup escape sequences
        while( src < end ) {
            if( (fix != NULL) && (fix->fixup_loc == (src - buff)) ) {
                name = fix->name;
                // insert fixup information
                *dst++ = FLOATING_FIXUP_BYTE;
                // only expect a 'fixup_type' of FIX_SEG
                switch( fix->fixup_type ) {
                case FIX_SEG:
                    if( name == NULL ) {
                        // special case for floating point fixup
                        if( *src != 0x9b ) { /* FWAIT */
                            *dst++ = 0x9b;
                        }
                        break;
                    }
                default:
                    Error( PR_SYMBOL_UNRESOLVED, name );
                    return;
                }
                head = fix;
                fix = fix->next;
                if( head->external ) {
                    *owner = fix;
                    if( head->name != NULL ) {
                        FMemFree( head->name );
                    }
                    FMemFree( head );
                } else {
                    owner = &head->next;
                }
            } else {
                if( *src == FLOATING_FIXUP_BYTE ) {
                    *dst++ = FLOATING_FIXUP_BYTE;
                }
                *dst++ = *src++;
            }
            if( dst > &temp[ MAXIMUM_BYTESEQ ] ) {
                Error( PR_BYTE_SEQ_LIMIT );
                Suicide();
            }
        }
        buff = temp;
        i = dst - temp;
        perform_fixups = DO_FLOATING_FIXUPS;
    }
    seq = FMemAlloc( sizeof( byte_seq ) + i );
    seq->length = i | perform_fixups;
    memcpy( &seq->data, buff, i );
    if( CurrAux->call_bytes != DefaultInfo.call_bytes ) {
        FMemFree( CurrAux->call_bytes );
    }
    CurrAux->call_bytes = seq;
}

#elif _TARGET == _AXP || _TARGET == _PPC

uint_32 AsmQuerySPOffsetOf( char *name ) {
//========================================

    return( 0 );
}


static  void    InsertFixups( unsigned char *buff, unsigned i ) {
//===============================================================

    risc_byte_seq       *seq;
    asmreloc            *reloc;
    byte_seq_reloc      *head;
    byte_seq_reloc      *new;
    byte_seq_reloc      **lnk;

    head = NULL;
    lnk = &head;
    for( reloc = AsmRelocs; reloc; reloc = reloc->next ) {
        new = FMemAlloc( sizeof( byte_seq_reloc ) );
        new->off = reloc->offset;
        new->type = reloc->type;
        new->sym = (void *)SymFind( reloc->name, strlen( reloc->name ) );
        new->next = NULL;
        *lnk = new;
        lnk = &new->next;
    }

    seq = FMemAlloc( sizeof( byte_seq ) + i );
    seq->relocs = head;
    seq->length = i;
    memcpy( &seq->data, buff, i );
    if( CurrAux->call_bytes != DefaultInfo.call_bytes ) {
        FMemFree( CurrAux->call_bytes );
    }
    CurrAux->call_bytes = seq;
}
#endif

#if _TARGET == _8086

static  void    AddAFix( unsigned i, char *name, unsigned type,
                         unsigned long off ) {
//============================================

    struct asmfixup     *fix;

    fix = FMemAlloc( sizeof( *fix ) );
    fix->external = 1;
    fix->fixup_loc = i;
    fix->name = name;
    fix->offset = off;
    fix->fixup_type = type;
    fix->next = FixupHead;
    FixupHead = fix;
}

#endif


static  void            GetByteSeq() {
//====================================

    int         seq_len;
    int         len;
    char        *ptr;
    char        buff[MAXIMUM_BYTESEQ+32]; // extra for assembler
#if _TARGET == _8086
    bool        float_specified;

    float_specified = FALSE;
#endif
    seq_len = 0;
    for(;;) {
        if( *TokStart == '"' ) {
            if( TokStart == TokEnd - sizeof( char ) ) Suicide();
            if( *(TokEnd - sizeof( char )) != '"' ) Suicide();
            *(char *)(TokEnd - sizeof( char )) = NULLCHAR;
            Address = seq_len;
            CodeBuffer = (ASM_CODE_BUFF_TYPE)&buff[0];
            AsmLine( &TokStart[1] );
            if( Address <= MAXIMUM_BYTESEQ ) {
                seq_len = Address;
            } else {
                Error( PR_BYTE_SEQ_LIMIT );
                Suicide();
            }
            ScanToken();
        } else if( RecToken( "FLOAT" ) ) {
#if _TARGET == _8086
            AddAFix( seq_len, NULL, FIX_SEG, 0 );
#endif
        } else {
            ptr = TokStart;
            if( ( *ptr != 'Z' ) && ( *ptr != 'z' ) ) break;
            ++ptr;
            len = MkHexConst( ptr, ptr, TokEnd - TokStart - 1 );
            if( len == 0 ) {
                Error( PR_BAD_BYTE_SEQ );
                Suicide();
            }
            if( seq_len + len <= MAXIMUM_BYTESEQ ) {
                memcpy( buff + seq_len, ptr, len );
                seq_len += len;
            } else {
                Error( PR_BYTE_SEQ_LIMIT );
                Suicide();
            }
            ScanToken();
        }
    }
    InsertFixups( buff, seq_len );
    AsmSymFini();
}


#if ( _TARGET == _8086 || _TARGET == _80386 )
static  hw_reg_set      RegSet() {
//================================

    hw_reg_set  reg_set;
    int         reg;

    HW_CAsgn( reg_set, HW_EMPTY );
    for(;;) {
        TokUpper();
        reg = KwLookUp( RegNames, MaxReg, TokStart, TokEnd-TokStart, TRUE );
        if( reg == 0 ) break;
        HW_TurnOn( reg_set, RegValue[ reg - 1 ] );
        ScanToken();
    }
    ReqToken( "]" );
    return( reg_set );
}


static  hw_reg_set      *RegSets() {
//==================================

    hw_reg_set  reg_sets[MAX_REG_SETS];
    hw_reg_set  *regs;
    int         num_sets;

    num_sets = 0;
    while( RecToken( "[" ) ) {
        reg_sets[ num_sets ] = RegSet();
        if( ( num_sets < MAX_REG_SETS ) &&
            !HW_CEqual( reg_sets[num_sets], HW_EMPTY ) ) {
            ++num_sets;
        }
    }
    HW_CAsgn( reg_sets[ num_sets ], HW_EMPTY );
    regs = FMemAlloc( ( num_sets + 1 ) * sizeof( hw_reg_set ) );
    memcpy( regs, reg_sets, ( num_sets + 1 ) * sizeof( hw_reg_set ) );
    return( regs );
}
#endif

#endif


static  void            GetParmInfo() {
//=====================================

// Collect argument information.

    struct {
#if ( _TARGET == _8086 || _TARGET == _80386 )
        unsigned f_pop           : 1;
        unsigned f_reverse       : 1;
        unsigned f_loadds        : 1;
        unsigned f_nomemory      : 1;
        unsigned f_list          : 1;
#endif
        unsigned f_args          : 1;
    } have;

#if ( _TARGET == _8086 || _TARGET == _80386 )
    have.f_pop           = 0;
    have.f_reverse       = 0;
    have.f_loadds        = 0;
    have.f_nomemory      = 0;
    have.f_list          = 0;
#endif
    have.f_args          = 0;
    for(;;) {
        if( !have.f_args && RecToken( "(" ) ) {
            GetArgList();
            have.f_args = 1;
#if _OPT_CG == _ON && ( _TARGET == _8086 || _TARGET == _80386 )
        } else if( !have.f_pop && RecToken( "CALLER" ) ) {
            CurrAux->call_info |= CALLER_POPS;
            have.f_pop = 1;
        } else if( !have.f_pop && RecToken( "ROUTINE" ) ) {
            CurrAux->call_info &= ~CALLER_POPS;
            have.f_pop = 1;
        } else if( !have.f_reverse && RecToken( "REVERSE" ) ) {
            // arguments are processed in reverse order by default
            CurrAux->call_info &= ~REVERSE_PARMS;
            have.f_reverse = 1;
        } else if( !have.f_nomemory && RecToken( "NOMEMORY" ) ) {
            CurrAux->call_info |= NO_MEMORY_READ;
            have.f_nomemory = 1;
        } else if( !have.f_loadds && RecToken( "LOADDS" ) ) {
            CurrAux->call_info |= LOAD_DS_ON_CALL;
            have.f_loadds = 1;
        } else if( !have.f_list && CurrToken( "[" ) ) {
            if( CurrAux->parm_info != DefaultInfo.parm_info ) {
                FMemFree( CurrAux->parm_info );
            }
            CurrAux->parm_info = RegSets();
            have.f_list = 1;
#endif
        } else {
            break;
        }
    }
}


static  void    GetArgList() {
//============================

    pass_by     *arg;
    pass_by     **curr_arg;
    unsigned_16 pass_info;

    FreeArgList( CurrAux );
    if( RecToken( ")" ) ) return;
    curr_arg = &CurrAux->arg_info;
    for(;;) {
        pass_info = 0;
        if( RecToken( "VALUE" ) ) {
            pass_info |= PASS_BY_VALUE;
            if( RecToken( "*" ) ) {
                if( RecToken( "1" ) ) {
                    pass_info |= ARG_SIZE_1;
                } else if( RecToken( "2" ) ) {
                    pass_info |= ARG_SIZE_2;
                } else if( RecToken( "4" ) ) {
                    pass_info |= ARG_SIZE_4;
                } else if( RecToken( "8" ) ) {
                    pass_info |= ARG_SIZE_8;
                } else {
                    Error( PR_BAD_PARM_SIZE );
                    Suicide();
                }
#if ( _TARGET == _8086 || _TARGET == _80386 )
            } else if( RecToken( "FAR" ) ) {
                pass_info |= ARG_FAR;

                #if ( _TARGET == _8086 )
                    pass_info |= ARG_SIZE_2;
                #elif ( _TARGET == _80386 )
                    pass_info |= ARG_SIZE_4;
                #endif

            } else if( RecToken( "NEAR" ) ) {
                pass_info |= ARG_NEAR;

                #if ( _TARGET == _8086 )
                    pass_info |= ARG_SIZE_2;
                #elif ( _TARGET == _80386 )
                    pass_info |= ARG_SIZE_4;
                #endif

            } else {
                #if ( _TARGET == _8086 )
                    pass_info |= ARG_SIZE_2;
                #elif ( _TARGET == _80386 )
                    pass_info |= ARG_SIZE_4;
                #endif
#endif
            }
        } else if( RecToken( "REFERENCE" ) ) {
            pass_info |= PASS_BY_REFERENCE;
#if ( _TARGET == _8086 || _TARGET == _80386 )
            if( RecToken( "FAR" ) ) {
                pass_info |= ARG_FAR;
            } else if( RecToken( "NEAR" ) ) {
                pass_info |= ARG_NEAR;
            }
#endif
            if( RecToken( "DESCRIPTOR" ) ) {
                pass_info |= PASS_BY_DESCRIPTOR;
            } else if( RecToken( "NODESCRIPTOR" ) ) {
                pass_info |= PASS_BY_NODESCRIPTOR;
            }
        } else if( RecToken( "DATA_REFERENCE" ) ) {
            pass_info |= PASS_BY_DATA | PASS_BY_REFERENCE;
#if ( _TARGET == _8086 || _TARGET == _80386 )
            if( RecToken( "FAR" ) ) {
                pass_info |= ARG_FAR;
            } else if( RecToken( "NEAR" ) ) {
                pass_info |= ARG_NEAR;
            }
#endif
        } else {
            Error( PR_BAD_PARM_ATTR );
            Suicide();
        }
        arg = FMemAlloc( sizeof( pass_by ) );
        arg->link = NULL;
        arg->info = pass_info;
        *curr_arg = arg;
        curr_arg = &arg->link;
        if( !RecToken( "," ) ) break;
    }
    ReqToken( ")" );
}


#if _OPT_CG == _ON

#if ( _TARGET == _8086 || _TARGET == _80386 )
static  void            GetRetInfo() {
//====================================

    struct {
        unsigned f_no8087        : 1;
        unsigned f_list          : 1;
        unsigned f_struct        : 1;
    } have;

    have.f_no8087  = 0;
    have.f_list    = 0;
    have.f_struct  = 0;
    // "3s" default is NO_8087_RETURNS - turn off NO_8087_RETURNS
    // flag so that "3s" model programs can use 387 pragmas
    CurrAux->call_info &= ~NO_8087_RETURNS;
    for(;;) {
        if( !have.f_no8087 && RecToken( "NO8087" ) ) {
            CurrAux->call_info |= NO_8087_RETURNS;
            HW_CTurnOff( CurrAux->return_info, HW_FLTS );
            have.f_no8087 = 1;
        } else if( !have.f_list && RecToken( "[" ) ) {
            CurrAux->call_info |= SPECIAL_RETURN;
            CurrAux->return_info = RegSet();
            have.f_list = 1;
        } else if( !have.f_struct && RecToken( "STRUCT" ) ) {
            GetSTRetInfo();
            have.f_struct = 1;
        } else {
            break;
        }
    }
}


static  void    GetSTRetInfo() {
//==============================

    struct {
        unsigned f_float        : 1;
        unsigned f_struct       : 1;
        unsigned f_allocs       : 1;
        unsigned f_list         : 1;
    } have;

    have.f_float  = 0;
    have.f_struct = 0;
    have.f_allocs = 0;
    have.f_list   = 0;
    for(;;) {
        if( !have.f_float && RecToken( "FLOAT" ) ) {
            CurrAux->call_info |= NO_FLOAT_REG_RETURNS;
            have.f_float = 1;
        } else if( !have.f_struct && RecToken( "STRUCT" ) ) {
            CurrAux->call_info |= NO_STRUCT_REG_RETURNS;
            have.f_struct = 1;
        } else if( !have.f_allocs && RecToken( "ROUTINE" ) ) {
            CurrAux->call_info |= ROUTINE_RETURN;
            have.f_allocs = 1;
        } else if( !have.f_allocs && RecToken( "CALLER" ) ) {
            CurrAux->call_info &= ~ROUTINE_RETURN;
            have.f_allocs = 1;
        } else if( !have.f_list && RecToken( "[" ) ) {
            CurrAux->call_info |= SPECIAL_STRUCT_RETURN;
            CurrAux->struct_info = RegSet();
            have.f_list = 1;
        } else {
            break;
        }
    }
}


static  void            GetSaveInfo() {
//=====================================

    hw_reg_set  modlist;
    hw_reg_set  default_flt_n_seg;
    hw_reg_set  flt_n_seg;

    struct {
        unsigned f_exact        : 1;
        unsigned f_nomemory     : 1;
        unsigned f_list         : 1;
    } have;

    have.f_exact    = 0;
    have.f_nomemory = 0;
    have.f_list     = 0;
    for(;;) {
        if( !have.f_exact && RecToken( "EXACT" ) ) {
            CurrAux->call_info |= MODIFY_EXACT;
            have.f_exact = 1;
        } else if( !have.f_nomemory && RecToken( "NOMEMORY" ) ) {
            CurrAux->call_info |= NO_MEMORY_CHANGED;
            have.f_nomemory = 1;
        } else if( !have.f_list && RecToken( "[" ) ) {
            modlist = RegSet();
            have.f_list = 1;
        } else {
            break;
        }
    }
    if( have.f_list ) {
        HW_Asgn( default_flt_n_seg, DefaultInfo.save_info );
        HW_CTurnOn( CurrAux->save_info, HW_FULL );
        if( !have.f_exact && !(CGOpts & CGOPT_SEG_REGS) ) {
            HW_CAsgn( flt_n_seg, HW_FLTS );
            HW_CTurnOn( flt_n_seg, HW_SEGS );
            HW_TurnOff( CurrAux->save_info, flt_n_seg );
            HW_OnlyOn( default_flt_n_seg, flt_n_seg );
            HW_TurnOn( CurrAux->save_info, default_flt_n_seg );
        }
        HW_TurnOff( CurrAux->save_info, modlist );
    }
}
#endif
#endif
