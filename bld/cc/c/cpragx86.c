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
* Description:  Pragmas specific to x86 targets.
*
****************************************************************************/


#include "cvars.h"
#include "cgswitch.h"
#include "pragdefn.h"
#include "pdefn2.h"
#include "asminlin.h"
#include "asmstmt.h"

local   void    GetParmInfo( void );
local   void    GetRetInfo( void );
local   void    GetSTRetInfo( void );
local   void    GetSaveInfo( void );
local   int     GetByteSeq( void );

extern  TREEPTR     CurFuncNode;

static  int             AsmFuncNum;
static  hw_reg_set      AsmRegsSaved = HW_D( HW_FULL );
#if _CPU == 386
static  hw_reg_set      STOSBParms[] = {
    HW_D( HW_EAX ), HW_D( HW_EDX ), HW_D( HW_ECX ),
    HW_D( HW_EMPTY )
};
#endif

void PragmaInit( void )
/*********************/
{
    int         cpu;
    int         fpu;
    int         use32;

#if _CPU == 386
    use32 = 1;
    cpu = 3;
#else
    use32 = 0;
    cpu = 0;
#endif
    AsmFuncNum = 0;
    switch( GET_CPU( ProcRevision ) ) {
    case CPU_86:    cpu = 0; break;
    case CPU_186:   cpu = 1; break;
    case CPU_286:   cpu = 2; break;
    case CPU_386:   cpu = 3; break;
    case CPU_486:   cpu = 4; break;
    case CPU_586:   cpu = 5; break;
    case CPU_686:   cpu = 6; break;
    }
    switch( GET_FPU( ProcRevision ) ) {
    case FPU_NONE:  fpu = 0; break;
    default:        fpu = 1; break;
    }

    AsmInit( cpu, fpu, use32, 1 );

    HeadLibs = NULL;

    PragmaAuxCallInfoInit( WatcallInfo.cclass & FAR, CompFlags.use_stdcall_at_number );

#if _CPU == 386
    HW_CTurnOff( AsmRegsSaved, HW_EAX );
    HW_CTurnOff( AsmRegsSaved, HW_EBX );
    HW_CTurnOff( AsmRegsSaved, HW_ECX );
    HW_CTurnOff( AsmRegsSaved, HW_EDX );
    HW_CTurnOff( AsmRegsSaved, HW_ESI );
    HW_CTurnOff( AsmRegsSaved, HW_EDI );
#else
    HW_CTurnOff( AsmRegsSaved, HW_ABCD );
    HW_CTurnOff( AsmRegsSaved, HW_SI );
    HW_CTurnOff( AsmRegsSaved, HW_DI );
    HW_CTurnOff( AsmRegsSaved, HW_ES );
#endif

#if _CPU == 386
    /* these are internal, and will never be pointed to by
       an aux_entry, so we don't have to worry about them
       or their fields being freed */

    STOSBInfo = WatcallInfo;
    STOSBInfo.cclass = NO_FLOAT_REG_RETURNS |
                       NO_STRUCT_REG_RETURNS |
                       SPECIAL_STRUCT_RETURN;
    STOSBInfo.parms = STOSBParms;
    STOSBInfo.objname = "*";
#endif

    DefaultInfo = *DftCallConv;
}


static int GetAliasInfo( void )
/*****************************/
{
    int         isfar16;
    char        buff[256];

    CurrAlias = &DefaultInfo;
    if( CurToken != T_LEFT_PAREN ) return( 1 );
    NextToken();
    if( CurToken != T_ID ) return( 0 );
    PragCurrAlias();
    strcpy( buff, Buffer );
    NextToken();
    if( CurToken == T_RIGHT_PAREN ) {
        NextToken();
        return( 1 );
    } else if( CurToken == T_COMMA ) {
        NextToken();
        if( CurToken != T_ID ) return( 0 );
        isfar16 = PragRecog( "far16" );
        CreateAux( buff );
        PragCurrAlias();
        NextToken();
        if( CurToken == T_RIGHT_PAREN ) {
            *CurrInfo = *CurrAlias;
            NextToken();
        }
        if( isfar16 ) {
            CurrInfo->flags |= AUX_FLAG_FAR16;
        }
        PragEnding();
        return( 0 ); /* process no more! */
    } else {
        return( 0 ); // shut up the compiler
    }
}


void PragAux( void )
/******************/
{
    struct {
        unsigned    f_call   : 1;
        unsigned    f_loadds : 1;
        unsigned    f_export : 1;
        unsigned    f_parm   : 1;
        unsigned    f_value  : 1;
        unsigned    f_modify : 1;
        unsigned    f_frame  : 1;
        unsigned    uses_auto: 1;
    } have;

    if( !GetAliasInfo() ) return;
    CurrEntry = NULL;
    if( CurToken != T_ID ) return;
    SetCurrInfo();
    NextToken();
    *CurrInfo = *CurrAlias;
    PragObjNameInfo();
    have.f_call   = 0;
    have.f_loadds = 0;
    have.f_export = 0;
    have.f_parm   = 0;
    have.f_value  = 0;
    have.f_modify = 0;
    have.f_frame = 0;
    have.uses_auto = 0; /* BBB - Jan 26, 1994 */
    for( ;; ) {
        if( !have.f_call && CurToken == T_EQUAL ) {
            have.uses_auto = GetByteSeq();
            have.f_call = 1;
        } else if( !have.f_call && PragRecog( "far" ) ) {
            CurrInfo->cclass |= FAR;
            have.f_call = 1;
        } else if( !have.f_call && PragRecog( "near" ) ) {
            CurrInfo->cclass &= ~FAR;
            have.f_call = 1;
        } else if( !have.f_loadds && PragRecog( "loadds" ) ) {
            CurrInfo->cclass |= LOAD_DS_ON_ENTRY;
            have.f_loadds = 1;
        } else if( !have.f_export && PragRecog( "export" ) ) {
            CurrInfo->cclass |= DLL_EXPORT;
            have.f_export = 1;
        } else if( !have.f_parm && PragRecog( "parm" ) ) {
            GetParmInfo();
            have.f_parm = 1;
        } else if( !have.f_value && PragRecog( "value" ) ) {
            GetRetInfo();
            have.f_value = 1;
        } else if( !have.f_value && PragRecog( "aborts" ) ) {
            CurrInfo->cclass |= SUICIDAL;
            have.f_value = 1;
        } else if( !have.f_modify && PragRecog( "modify" ) ) {
            GetSaveInfo();
            have.f_modify = 1;
        } else if( !have.f_frame && PragRecog( "frame" ) ) {
            CurrInfo->cclass |= GENERATE_STACK_FRAME;
            have.f_frame = 1;
        } else {
            break;
        }
    }
    if( have.uses_auto ) {
        /*
           We want to force the calling routine to set up a [E]BP frame
           for the use of this pragma. This is done by saying the pragma
           modifies the [E]SP register. A kludge, but it works.
        */
        HW_CTurnOff( CurrInfo->save, HW_SP );
    }
    PragEnding();
}

typedef enum {
    FIXWORD_NONE,
    FIXWORD_FLOAT,
    FIXWORD_SEGMENT,
    FIXWORD_OFFSET,
    FIXWORD_RELOFF
} fix_words;

local fix_words FixupKeyword( void )
/**********************************/
{
    if( CurToken == T_FLOAT ) {
        NextToken();                    /* 20-jun-92 */
        return( FIXWORD_FLOAT );
    }
    if( PragRecog( "seg" ) )    return( FIXWORD_SEGMENT );
    if( PragRecog( "offset" ) ) return( FIXWORD_OFFSET );
    if( PragRecog( "reloff" ) ) return( FIXWORD_RELOFF );
    return( FIXWORD_NONE );
}


enum sym_state AsmQueryExternal( char *name )
/*******************************************/
{
    SYM_HANDLE  sym_handle;
    SYM_ENTRY   sym;

    sym_handle = SymLook( CalcHash( name, strlen( name ) ), name );
    if( sym_handle == 0 ) return( SYM_UNDEFINED );
    SymGet( &sym, sym_handle );
    switch( sym.stg_class ) {
    case SC_AUTO:
    case SC_REGISTER:
        return( SYM_STACK );
    }
    return( SYM_EXTERNAL );
}

#if _CPU == 8086
    #define SYM_INT     SYM_INT2
    #define SYM_FFAR    SYM_FAR2
    #define SYM_FNEAR   SYM_NEAR2
    #define SYM_DFAR    SYM_INT4
    #define SYM_DNEAR   SYM_INT2
#else
    #define SYM_INT     SYM_INT4
    #define SYM_FFAR    SYM_FAR4
    #define SYM_FNEAR   SYM_NEAR2
    #define SYM_DFAR    SYM_INT6
    #define SYM_DNEAR   SYM_INT4
#endif

static int AsmCodePtrType( type_modifiers flags )
/***********************************************/
{
    if( flags & FLAG_FAR ) {
        return( SYM_FFAR );
    } else if( flags & FLAG_NEAR ) {
        return( SYM_FNEAR );
    } else if( TargetSwitches & BIG_CODE ) {
        return( SYM_FFAR );
    } else {
        return( SYM_FNEAR );
    }
}


static int AsmPtrType( TYPEPTR typ, type_modifiers flags )
/********************************************************/
{

    SKIP_TYPEDEFS( typ );
    if( typ->decl_type == TYPE_FUNCTION ) {
        return( AsmCodePtrType( flags ) );
    } else if( flags & (FLAG_FAR|FLAG_HUGE) ) {
        return( SYM_DFAR );
    } else if( flags & FLAG_NEAR ) {
        return( SYM_DNEAR );
    } else if( TargetSwitches & BIG_DATA ) {
        return( SYM_DFAR );
    } else {
        return( SYM_DNEAR );
    }
}

/* matches enum DataType in ctypes.h */
static enum sym_type AsmDataType[TYPE_LAST_ENTRY] = {
    SYM_INT1,       /* TYPE_CHAR,*/
    SYM_INT1,       /* TYPE_UCHAR,*/
    SYM_INT2,       /* TYPE_SHORT,*/
    SYM_INT2,       /* TYPE_USHORT,*/
    SYM_INT,        /* TYPE_INT,*/
    SYM_INT,        /* TYPE_UINT,*/
    SYM_INT4,       /* TYPE_LONG,*/
    SYM_INT4,       /* TYPE_ULONG,*/
    SYM_INT8,       /* TYPE_LONG64,*/
    SYM_INT8,       /* TYPE_ULONG64,*/
    SYM_FLOAT4,     /* TYPE_FLOAT,*/
    SYM_FLOAT8,     /* TYPE_DOUBLE,*/
    0,              /* TYPE_POINTER,*/
    0,              /* TYPE_ARRAY,*/
    0,              /* TYPE_STRUCT,*/
    0,              /* TYPE_UNION,*/
    0,              /* TYPE_FUNCTION,*/
    0,              /* TYPE_FIELD,*/
    SYM_INT1,       /* TYPE_VOID,*/
    0,              /* TYPE_ENUM,*/
    0,              /* TYPE_TYPEDEF,*/
    0,              /* TYPE_UFIELD,*/
    0,              /* TYPE_DOT_DOT_DOT,*/
    SYM_INT1,       /* TYPE_PLAIN_CHAR,*/
    SYM_INT2,       /* TYPE_WCHAR,  */
    SYM_FLOAT10,    /* TYPE_LONG_DOUBLE */
    0,              /* TYPE_FCOMPLEX, */
    0,              /* TYPE_DCOMPLEX, */
    0,              /* TYPE_LDCOMPLEX, */
    SYM_FLOAT4,     /* TYPE_FIMAGINARY, */
    SYM_FLOAT8,     /* TYPE_DIMAGINARY, */
    SYM_FLOAT10,    /* TYPE_LDIMAGINARY, */
    SYM_INT1,       /* TYPE_BOOL, */
};

local int AsmType( TYPEPTR typ, type_modifiers flags )
/****************************************************/
{
    SKIP_TYPEDEFS( typ );
    switch( typ->decl_type ) {
    case TYPE_STRUCT:
    case TYPE_UNION:
        return( SYM_INT1 );
    case TYPE_ARRAY:
        return( AsmType( typ->object, flags ) );
    case TYPE_FIELD:
    case TYPE_UFIELD:
        return( AsmDataType[ typ->u.f.field_type ] );
    case TYPE_FUNCTION:
        return( AsmCodePtrType( flags ) );
    case TYPE_POINTER:
        return( AsmPtrType( typ->object, typ->u.p.decl_flags ) );
    case TYPE_ENUM:
        typ = typ->object;
        /* fall through */
    default:
        return( AsmDataType[ typ->decl_type ] );
    }
}

enum sym_type AsmQueryType( char *name )
/**************************************/
{
    SYM_HANDLE  sym_handle;
    SYM_ENTRY   sym;

    sym_handle = SymLook( CalcHash( name, strlen( name ) ), name );
    if( sym_handle == 0 ) return( SYM_INT1 );
    SymGet( &sym, sym_handle );
    return( AsmType( sym.sym_type, sym.attrib ) );
}

static int InsertFixups( unsigned char *buff, unsigned i )
/********************************************************/
{
                        /* additional slop in buffer to simplify the code */
    unsigned char       temp[ MAXIMUM_BYTESEQ + 1 + 2 * sizeof( long ) ];
    struct asmfixup     *fix;
    struct asmfixup     *head;
    struct asmfixup     *chk;
    struct asmfixup     *next;
    struct asmfixup     **owner;
    unsigned char       *dst;
    unsigned char       *src;
    unsigned char       *end;
    byte_seq            *seq;
    byte_seq_len        perform_fixups;
    unsigned char       cg_fix;
    SYM_HANDLE          sym_handle;
    SYM_ENTRY           sym;
    char                *name;
    unsigned            skip;
    int                 mutate_to_segment;
    int                 uses_auto;
#if _CPU == 8086
    int                 fixup_padding;
#endif

    uses_auto = 0;
    perform_fixups = 0;
    head = FixupHead;
    if( head != NULL ) {
        FixupHead = NULL;
        /* sort the fixup list in increasing fixup_loc's */
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
        /* insert fixup escape sequences */
        while( src < end ) {
            if( fix != NULL && fix->fixup_loc == (src - buff) ) {
                name = fix->name;
                if( name != NULL ) {
                    sym_handle = SymLook( CalcHash( name, strlen( name ) ),
                                name );
                    if( sym_handle == 0 ) {
                        CErr2p( ERR_UNDECLARED_SYM, name );
                        return( 0 );
                    }
                    SymGet( &sym, sym_handle );
                    sym.flags |= SYM_REFERENCED | SYM_ADDR_TAKEN;
                    switch( sym.stg_class ) {
                    case SC_REGISTER:
                    case SC_AUTO:
                        sym.flags |= SYM_USED_IN_PRAGMA;
                        CurFuncNode->op.func.flags &= ~FUNC_OK_TO_INLINE;
                        uses_auto = 1;
                        break;
                    }
                    SymReplace( &sym, sym_handle );
                }
                /* insert fixup information */
                skip = 0;
                *dst++ = FLOATING_FIXUP_BYTE;
                mutate_to_segment = 0;
#if _CPU == 8086
                fixup_padding = 0;
#endif
                switch( fix->fixup_type ) {
                case FIX_SEG:
                    if( name == NULL ) {
                        /* special case for floating point fixup */
                        if( src[0] == 0x9b ) {
                           // FWAIT instruction as first byte
                        } else if( ( src[0] == 0x90 ) && ( src[1] == 0x9B ) ) {
                           // inline assembler FWAIT instruction 0x90, 0x9b
                        } else if( ( src[0] & 0xd8 ) == 0xd8 ) {
                           // FPU instruction, add FWAIT before it
                            *dst++ = 0x9b;
                        } else {
                            // FIXME - probably wrong use of float !!!!
                        }
                    } else {
                        skip = 2;
                        cg_fix = FIX_SYM_SEGMENT;
                    }
                    break;
                case FIX_RELOFF8:
                    CErr2p( ERR_UNREACHABLE_SYM, name );
                    break;
                case FIX_RELOFF16:
                    skip = 2;
                    cg_fix = FIX_SYM_RELOFF;
                    break;
                case FIX_RELOFF32:
                    skip = 4;
                    cg_fix = FIX_SYM_RELOFF;
#if _CPU == 8086
                    fixup_padding = 1;
#endif
                    break;
                case FIX_PTR16:
                    mutate_to_segment = 1;
                    /* fall through */
                case FIX_OFF16:
                    skip = 2;
                    cg_fix = FIX_SYM_OFFSET;
                    break;
                case FIX_PTR32:
                    mutate_to_segment = 1;
                    /* fall through */
                case FIX_OFF32:
                    skip = 4;
                    cg_fix = FIX_SYM_OFFSET;
#if _CPU == 8086
                    fixup_padding = 1;
#endif
                    break;
                }
                if( skip != 0 ) {
                    *dst++ = cg_fix;
                    *((unsigned long *)dst) = sym_handle;
                    dst += sizeof( long );
                    *((unsigned long *)dst) = fix->offset;
                    dst += sizeof( long );
                    src += skip;
                }
#if _CPU == 8086
                if( fixup_padding ) {
                    // add offset fixup padding to 32-bit
                    // cg create only 16-bit offset fixup
                    *dst++ = 0;
                    *dst++ = 0;
                    //
                }
#endif
                if( mutate_to_segment ) {
                    /*
                        Since the CG escape sequences don't allow for
                        FAR pointer fixups, we have to split them into two.
                        This is done by doing the offset fixup first, then
                        mutating the fixup structure to look like a segment
                        fixup one near pointer size later.
                    */
                    fix->fixup_type = FIX_SEG;
                    fix->fixup_loc += skip;
                    fix->offset = 0;
                } else {
                    head = fix;
                    fix = fix->next;
                    if( head->external ) {
                        *owner = fix;
                        if( head->name != NULL ) {
                            CMemFree( head->name );
                        }
                        CMemFree( head );
                    } else {
                        owner = &head->next;
                    }
                }
            } else {
                if( *src == FLOATING_FIXUP_BYTE ) {
                    *dst++ = FLOATING_FIXUP_BYTE;
                }
                *dst++ = *src++;
            }
            if( dst > &temp[ MAXIMUM_BYTESEQ ] ) {
                CErr1( ERR_TOO_MANY_BYTES_IN_PRAGMA );
                return( 0 );
            }
        }
        buff = temp;
        i = dst - temp;
        perform_fixups = DO_FLOATING_FIXUPS;
    }
    seq = (byte_seq *)CMemAlloc( sizeof( byte_seq ) + i );
    seq->length = i | perform_fixups;
    memcpy( &seq->data[0], buff, i );
    CurrInfo->code = seq;
    return( uses_auto );
}


local void AddAFix( unsigned i, char *name, unsigned type, unsigned long off )
/****************************************************************************/
{
    struct asmfixup     *fix;

    fix = (struct asmfixup *)CMemAlloc( sizeof( *fix ) );
    fix->external = 1;
    fix->fixup_loc = i;
    fix->name = name;
    fix->offset = off;
    fix->fixup_type = type;
    fix->next = FixupHead;
    FixupHead = fix;
}

local void FreeAsmFixups( void )
/******************************/
{
    struct asmfixup     *fix;

    for( ;; ) {
        fix = FixupHead;
        if( fix == NULL ) break;
        FixupHead = fix->next;
        CMemFree( fix );
    }
}


local int GetByteSeq( void )
/**************************/
{
    unsigned char       buff[ MAXIMUM_BYTESEQ + 32 ];
    char                *name;
    unsigned long       offset;
    unsigned            fixword;
    int                 uses_auto;
    char                too_many_bytes;

    AsmSysInit( buff );
    CompFlags.pre_processing = 1;       /* enable macros */
    NextToken();
    too_many_bytes = 0;
    uses_auto = 0;
    for( ;; ) {
        if( CurToken == T_STRING ) {    /* 06-sep-91 */
            AsmLine( Buffer );
            NextToken();
            if( CurToken == T_COMMA ) {
                NextToken();
            }
        } else if( CurToken == T_CONSTANT ) {
            AsmCodeBuffer[AsmCodeAddress++] = Constant;
            NextToken();
        } else {
            fixword = FixupKeyword();
            if( fixword == FIXWORD_NONE )
                break;
            if( fixword == FIXWORD_FLOAT ) {
#if _CPU == 8086
                if( GET_FPU_EMU( ProcRevision ) ) {
                    AddAFix( AsmCodeAddress, NULL, FIX_SEG, 0 );
                }
#endif
            } else { /* seg or offset */
                if( CurToken != T_ID ) {
                    CErr1( ERR_EXPECTING_ID );
                } else {
                    name = CStrSave( Buffer );
                    offset = 0;
                    NextToken();
                    if( CurToken == T_PLUS ) {
                        NextToken();
                        if( CurToken == T_CONSTANT ) {
                            offset = Constant;
                            NextToken();
                        }
                    } else if( CurToken == T_MINUS ) {
                        NextToken();
                        if( CurToken == T_CONSTANT ) {
                            offset = -Constant;
                            NextToken();
                        }
                    }
                }
                switch( fixword ) {
                case FIXWORD_RELOFF:
#if _CPU == 8086
                    AddAFix( AsmCodeAddress, name, FIX_RELOFF16, offset );
                    AsmCodeAddress += 2;
#else
                    AddAFix( AsmCodeAddress, name, FIX_RELOFF32, offset );
                    AsmCodeAddress += 4;
#endif
                    break;
                case FIXWORD_OFFSET:
#if _CPU == 8086
                    AddAFix( AsmCodeAddress, name, FIX_OFF16, offset );
                    AsmCodeAddress += 2;
#else
                    AddAFix( AsmCodeAddress, name, FIX_OFF32, offset );
                    AsmCodeAddress += 4;
#endif
                    break;
                case FIXWORD_SEGMENT:
                    AddAFix( AsmCodeAddress, name, FIX_SEG, 0 );
                    AsmCodeAddress += 2;
                    break;
                }
            }
        }
        if( AsmCodeAddress > MAXIMUM_BYTESEQ ) {
            if( ! too_many_bytes ) {
                CErr1( ERR_TOO_MANY_BYTES_IN_PRAGMA );
                too_many_bytes = 1;
            }
            AsmCodeAddress = 0;          // reset index to we don't overrun buffer
        }
    }
    if( too_many_bytes ) {
        FreeAsmFixups();
        uses_auto = 0;
    } else {
        uses_auto = InsertFixups( buff, AsmCodeAddress );
    }
    CompFlags.pre_processing = 2;
    AsmSysFini();
    return( uses_auto );
}


hw_reg_set PragRegName( char *str )
/*********************************/
{
    int         index;
    char        *p;
    hw_reg_set  name;

    if( *str == '\0' ) {
        HW_CAsgn( name, HW_EMPTY );
        return( name );
    }
    if( *str == '_' ) {
        ++str;
        if( *str == '_' ) {
            ++str;
        }
    }
    index = 0;
    p = Registers;
    while( *p != '\0' ) {
        if( stricmp( p, str ) == 0 )
            return( RegBits[ index ] );
        index++;
        while( *p++ != '\0' ) {
            ;
        }
    }
    if( strcmp( str, "8087" ) == 0 ) {
        HW_CAsgn( name, HW_FLTS );
    } else {
        CErr2p( ERR_BAD_REGISTER_NAME, str );
        HW_CAsgn( name, HW_EMPTY );
    }
    return( name );
}



local void GetParmInfo( void )
/****************************/
{
    struct {
        unsigned f_pop           : 1;
        unsigned f_reverse       : 1;
        unsigned f_loadds        : 1;
        unsigned f_nomemory      : 1;
        unsigned f_list          : 1;
    } have;

    have.f_pop           = 0;
    have.f_reverse       = 0;
    have.f_loadds        = 0;
    have.f_nomemory      = 0;
    have.f_list          = 0;
    for( ;; ) {
        if( !have.f_pop && PragRecog( "caller" ) ) {
            CurrInfo->cclass |= CALLER_POPS;
            have.f_pop = 1;
        } else if( !have.f_pop && PragRecog( "routine" ) ) {
            CurrInfo->cclass &= ~ CALLER_POPS;
            have.f_pop = 1;
        } else if( !have.f_reverse && PragRecog( "reverse" ) ) {
            CurrInfo->cclass |= REVERSE_PARMS;
            have.f_reverse = 1;
        } else if( !have.f_nomemory && PragRecog( "nomemory" ) ) {
            CurrInfo->cclass |= NO_MEMORY_READ;
            have.f_nomemory = 1;
        } else if( !have.f_loadds && PragRecog( "loadds" ) ) {
            CurrInfo->cclass |= LOAD_DS_ON_CALL;
            have.f_loadds = 1;
        } else if( !have.f_list && PragRegSet() != T_NULL ) {
            PragManyRegSets();
            have.f_list = 1;
        } else {
            break;
        }
    }
}


local void GetRetInfo( void )
/***************************/
{
    struct {
        unsigned f_no8087        : 1;
        unsigned f_list          : 1;
        unsigned f_struct        : 1;
    } have;

    have.f_no8087  = 0;
    have.f_list    = 0;
    have.f_struct  = 0;
    CurrInfo->cclass &= ~ NO_8087_RETURNS;               /* 29-mar-90 */
    for( ;; ) {
        if( !have.f_no8087 && PragRecog( "no8087" ) ) {
            have.f_no8087 = 1;
            HW_CTurnOff( CurrInfo->returns, HW_FLTS );
            CurrInfo->cclass |= NO_8087_RETURNS;
        } else if( !have.f_list && PragRegSet() != T_NULL ) {
            have.f_list = 1;
            CurrInfo->cclass |= SPECIAL_RETURN;
            CurrInfo->returns = PragRegList();
        } else if( !have.f_struct && PragRecog( "struct" ) ) {
            have.f_struct = 1;
            GetSTRetInfo();
        } else {
            break;
        }
    }
}


local void GetSTRetInfo( void )
/*****************************/
{
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
    for( ;; ) {
        if( !have.f_float && PragRecog( "float" ) ) {
            have.f_float = 1;
            CurrInfo->cclass |= NO_FLOAT_REG_RETURNS;
        } else if( !have.f_struct && PragRecog( "struct" ) ) {
            have.f_struct = 1;
            CurrInfo->cclass |= NO_STRUCT_REG_RETURNS;
        } else if( !have.f_allocs && PragRecog( "routine" ) ) {
            have.f_allocs = 1;
            CurrInfo->cclass |= ROUTINE_RETURN;
        } else if( !have.f_allocs && PragRecog( "caller" ) ) {
            have.f_allocs = 1;
            CurrInfo->cclass &= ~ROUTINE_RETURN;
        } else if( !have.f_list && PragRegSet() != T_NULL ) {
            have.f_list = 1;
            CurrInfo->cclass |= SPECIAL_STRUCT_RETURN;
            CurrInfo->streturn = PragRegList();
        } else {
            break;
        }
    }
}


local void GetSaveInfo( void )
/****************************/
{
    hw_reg_set  modlist;
    hw_reg_set  default_flt_n_seg;
    hw_reg_set  flt_n_seg;

    struct {
        unsigned    f_exact     : 1;
        unsigned    f_nomemory  : 1;
        unsigned    f_list      : 1;
    } have;

    have.f_exact    = 0;
    have.f_nomemory = 0;
    have.f_list     = 0;
    for( ;; ) {
        if( !have.f_exact && PragRecog( "exact" ) ) {
            CurrInfo->cclass |= MODIFY_EXACT;
            have.f_exact = 1;
        } else if( !have.f_nomemory && PragRecog( "nomemory" ) ) {
            CurrInfo->cclass |= NO_MEMORY_CHANGED;
            have.f_nomemory = 1;
        } else if( !have.f_list && PragRegSet() != T_NULL ) {
            modlist = PragRegList();
            have.f_list = 1;
        } else {
            break;
        }
    }
    if( have.f_list ) {
        HW_CTurnOn( CurrInfo->save, HW_FULL );
        if( !have.f_exact && !CompFlags.save_restore_segregs ) {
            HW_Asgn( default_flt_n_seg, DefaultInfo.save );
            HW_CAsgn( flt_n_seg, HW_FLTS );
            HW_CTurnOn( flt_n_seg, HW_SEGS );
            HW_TurnOff( CurrInfo->save, flt_n_seg );
            HW_OnlyOn( default_flt_n_seg, flt_n_seg );
            HW_TurnOn( CurrInfo->save, default_flt_n_seg );
        }
        HW_TurnOff( CurrInfo->save, modlist );
    }
}

void AsmSysInit( unsigned char *buf )
/***********************************/
{
    AsmCodeBuffer = buf;
    AsmCodeAddress = 0;
    AsmSaveCPUInfo();
}

void AsmSysFini( void )
/*********************/
{
    AsmSymFini();
    AsmRestoreCPUInfo();
}

void AsmSysMakeInlineAsmFunc( int code_ovrflw )
/*********************************************/
{
    int                 code_length;
    SYM_HANDLE          sym_handle;
    TREEPTR             tree;
    int                 uses_auto;
    char                name[8];

    code_length = AsmCodeAddress;
    if( code_length != 0 ) {
        sprintf( name, "F.%d", AsmFuncNum );
        ++AsmFuncNum;
        CreateAux( name );
        *CurrInfo = DefaultInfo;
        CurrInfo->use = 1;
        CurrInfo->save = AsmRegsSaved;  // indicate no registers saved
        uses_auto = InsertFixups( AsmCodeBuffer, code_length );
        if( uses_auto ) {
            /*
               We want to force the calling routine to set up a [E]BP frame
               for the use of this pragma. This is done by saying the pragma
               modifies the [E]SP register. A kludge, but it works.
            */
            HW_CTurnOff( CurrInfo->save, HW_SP );
        }
        CurrEntry->info = CurrInfo;
        CurrEntry->next = AuxList;
        AuxList = CurrEntry;
        CurrEntry = NULL;
        sym_handle = MakeFunction( CStrSave( name ),
                        FuncNode( GetType( TYPE_VOID ), 0, NULL ) );
        tree = LeafNode( OPR_FUNCNAME );
        tree->op.sym_handle = sym_handle;
        tree = ExprNode( tree, OPR_CALL, NULL );
        tree->expr_type = GetType( TYPE_VOID );
        AddStmt( tree );
    }
}

char const *AsmSysDefineByte( void )
/**********************************/
{
    return( "db " );
}
