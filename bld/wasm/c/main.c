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


#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#ifdef __WATCOMC__
#include <process.h>
#endif
#include <ctype.h>
#include <malloc.h>

#include "asmglob.h"
#include "asmalloc.h"
#include "asmops1.h"
#include "asmins1.h"
#include "asmsym.h"
#include "directiv.h"
#include "fatal.h"
#include "asmerr.h"

#ifdef TRMEM
#include "memutil.h"
#endif

#include "womp.h"
#include "objprs.h"
#include "genmsomf.h"
#ifdef __OSI__
 #include "ostype.h"
#endif

extern void             Fatal( unsigned msg, ... );
extern void             WriteObjModule( void );
extern void             ObjRecInit( void );
extern void             DelErrFile();
extern void             PrintStats();
extern void             AsmInit( int, int, int );
extern int              AsmScan( char *, char * );
extern void             PrintfUsage( int first_ln );
extern void             MsgPrintf1( int resourceid, char *token );
extern void             InputQueueLine( char * );
extern int              InputQueueFile( char * );
extern void             PushLineQueue(void);
extern void             AddStringToIncludePath( char * );
extern int              cpu_directive( uint_16 );

extern struct asm_code  *Code;          // store information for assembler
extern struct asm_tok   *AsmBuffer[];   // buffer to store token
extern const char       *FingerMsg[];

File_Info               AsmFiles;       // files information
pobj_state              pobjState;      // object file information for WOMP

struct  option {
    char        *option;
    unsigned    value;
    void        (*function)(void);
};

static struct SWData {
    char naming_convention;
    char protect_mode;
    int cpu;
    int fpu;
} SWData = { 0, 0, -1, -1 };

#define MAX_NESTING 15
#define BUF_SIZE 512

static char ParamBuf[ BUF_SIZE ];
static unsigned char SwitchChar;
static unsigned OptValue;
static char *OptScanPtr;
static char *OptParm;

#if defined( __DOS__ )

extern  unsigned char    _DOS_Switch_Char();
#pragma aux     _DOS_Switch_Char = \
    0x52            /* push dx */\
    0xb4 0x37       /* mov ah,37h    */\
    0xb0 0x00       /* mov al,00h    */\
    0xcd 0x21       /* int 21h       */\
    0x88 0xd0       /* mov al,dl     */\
    0x5a            /* pop dx        */;
#endif

unsigned char _dos_switch_char()
{
#if defined( __DOS__ )
        return( _DOS_Switch_Char() );
#elif defined( __UNIX__ )
        return( '-' );
#else
        return( '/' );
#endif
}

static char *CopyOfParm(void)
/*******************************************/
{
    unsigned    len;

    len = OptScanPtr - OptParm;
    memcpy( ParamBuf, OptParm, len );
    ParamBuf[ len ] = '\0';
    return( ParamBuf );
}

static void StripQuotes( char *fname )
/*******************************************/
{
    char *s;
    char *d;

    if( *fname == '"' ) {
        // string will shrink so we can reduce in place
        d = fname;
        for( s = d + 1; *s && *s != '"'; ++s ) {
            if( *s == '\0' )break;
            if( s[0] == '\\' && s[1] == '"' ) {
                ++s;
            }
            *d++ = *s;
        }
        *d = '\0';
    }
}

static char *GetAFileName(void)
/*******************************************/
{
    char *fname;
    fname = CopyOfParm();
    StripQuotes( fname );
    return( fname );
}

static void SetTargName( char *name, unsigned len )
/*******************************************/
{
    char        *p;

    if( Options.build_target != NULL ) {
        AsmFree( Options.build_target );
        Options.build_target = NULL;
    }
    if( name == NULL || len == 0 ) return;
    Options.build_target = AsmAlloc( len + 1 );
    p = Options.build_target;
    while( len != 0 ) {
        *p++ = toupper( *name++ );
        --len;
    }
    *p++ = '\0';
}

static void SetCPU(void)
/*******************************************/
{
    char                *tmp;

    switch( OptValue ) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        SWData.cpu = OptValue;
        break;
    case 7:
        SWData.fpu = OptValue;
        break;
    }
    for( tmp=OptParm; tmp < OptScanPtr; tmp++ ) {
        if( *tmp == 'r' ) {
            SWData.naming_convention = *tmp;
        } else if( *tmp == 's' ) {
            SWData.naming_convention = *tmp;
        } else if( *tmp == '_' ) {
            SWData.naming_convention = *tmp;
        } else if( *tmp == 'p' ) {
            SWData.protect_mode = TRUE;
        } else if( *tmp == '"' ) {
            char *dest;
            tmp++;
            dest = strchr(tmp, '"');
            if( Options.default_name_mangler != NULL ) {
                AsmFree( Options.default_name_mangler );
            }
            Options.default_name_mangler = AsmAlloc( dest - tmp + 1 );
            dest = Options.default_name_mangler;
            for( ; *tmp != '"'; dest++, tmp++ ) {
                *dest = *tmp;
            }
            *dest = NULLC;
        } else {
            MsgPrintf1( MSG_UNKNOWN_OPTION, CopyOfParm() );
            exit( 1 );
        }
    }
}

static void SetFPU(void)
/*******************************************/
{
    switch( OptValue ) {
    case 'i':
        Options.floating_point = DO_FP_EMULATION;
        break;
    case '7':
        Options.floating_point = NO_FP_EMULATION;
        break;
    case 'c':
        Options.floating_point = NO_FP_ALLOWED;
        break;
    case 0:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        SWData.fpu = OptValue;
        break;
    }
}

static void SetMemoryModel(void)
/*******************************************/
{
    char buffer[20];
    char *model;

    switch( OptValue ) {
    case 'c':
        model = "COMPACT";
        break;
    case 'f':
        model = "FLAT";
        break;
    case 'h':
        model = "HUGE";
        break;
    case 'l':
        model = "LARGE";
        break;
    case 'm':
        model = "MEDIUM";
        break;
    case 's':
        model = "SMALL";
        break;
    case 't':
        model = "TINY";
        break;
    default:
        strcpy( buffer, "/m" );
        strcat( buffer, (char *)&OptValue );
        MsgPrintf1( MSG_UNKNOWN_OPTION, buffer );
        exit( 1 );
    }

    strcpy( buffer, ".MODEL " );
    strcat( buffer, model );
    InputQueueLine( buffer );

    return;    
}

static void Ignore(void) {};

static void Set_BT(void) { SetTargName( OptParm,  OptScanPtr - OptParm ); }

static void Set_C(void) { Options.output_data_in_code_records = FALSE; }

static void Set_D(void) { Options.debug_flag = (OptValue != 0) ? TRUE : FALSE; }

static void DefineMacro(void) { add_constant( CopyOfParm() ); }

static void SetErrorLimit(void) { Options.error_limit = OptValue; }

static void SetStopEnd(void) { Options.stop_at_end = TRUE; }

static void Set_FR(void) { get_fname( GetAFileName(), ERR ); }

static void Set_FI(void) { InputQueueFile( GetAFileName() ); }

static void Set_FO(void) { get_fname( GetAFileName(), OBJ ); }

static void SetInclude(void) { AddStringToIncludePath( GetAFileName() ); }

static void Set_S(void) { Options.sign_value = TRUE; }

static void Set_N(void) { set_some_kinda_name( OptValue, CopyOfParm() ); }

static void Set_O(void) { Options.allow_c_octals = TRUE; }

static void Set_WE(void) { Options.warning_error = TRUE; }

static void Set_WX(void) { Options.warning_level = 4; }

static void SetWarningLevel(void) { Options.warning_level = OptValue; }

static void Set_ZLD(void) { Options.emit_dependencies = FALSE; }

static void Set_ZQ(void) { Options.quiet = TRUE; }

static void HelpUsage(void) { usage_msg();}

#ifdef DEBUG_OUT
static void Set_D6(void) { Options.debug = TRUE; DebugMsg(( "debugging output on \n" )); }
#endif

static struct option const cmdl_options[] = {
    { "0$",     0,        SetCPU },
    { "1$",     1,        SetCPU },
    { "2$",     2,        SetCPU },
    { "3$",     3,        SetCPU },
    { "4$",     4,        SetCPU },
    { "5$",     5,        SetCPU },
    { "6$",     6,        SetCPU },
    { "7$",     7,        SetCPU },
    { "?",      0,        HelpUsage },
    { "bt=$",   0,        Set_BT },
    { "c",      0,        Set_C },
    { "d0",     0,        Set_D },
    { "d1",     1,        Set_D },
    { "d2",     2,        Set_D },
    { "d3",     3,        Set_D },
#ifdef DEBUG_OUT
    { "d6",     6,        Set_D6 },
#endif    
    { "d+",     0,        Ignore },
    { "d$",     0,        DefineMacro },
    { "e",      0,        SetStopEnd },
    { "e=#",    0,        SetErrorLimit },
    { "fe=@",   0,        Set_FR },
    { "fi=@",   0,        Set_FI },
    { "fo=@",   0,        Set_FO },
    { "fp0",    0,        SetFPU },
    { "fp2",    2,        SetFPU },
    { "fp3",    3,        SetFPU },
    { "fp4",    4,        SetFPU },
    { "fp5",    5,        SetFPU },
    { "fp6",    6,        SetFPU },
    { "fpi87",  '7',      SetFPU },
    { "fpi",    'i',      SetFPU },
    { "fpc",    'c',      SetFPU },
    { "fr=@",   0,        Set_FR },
    { "h",      0,        HelpUsage },
    { "hc",     'c',      Ignore },
    { "hd",     'd',      Ignore },
    { "hw",     'w',      Ignore },
    { "i=@",    0,        SetInclude },
    { "j",      0,        Set_S },
    { "mc",     'c',      SetMemoryModel },
    { "mf",     'f',      SetMemoryModel },
    { "mh",     'h',      SetMemoryModel },
    { "ml",     'l',      SetMemoryModel },
    { "mm",     'm',      SetMemoryModel },
    { "ms",     's',      SetMemoryModel },
    { "mt",     't',      SetMemoryModel },
    { "nc=$",   'c',      Set_N },
    { "nd=$",   'd',      Set_N },
    { "nm=$",   'm',      Set_N },
    { "nt=$",   't',      Set_N },
    { "o",      0,        Set_O },
    { "q",      0,        Set_ZQ },
    { "s",      0,        Set_S },
    { "u",      0,        Ignore },
    { "we",     0,        Set_WE },
    { "wx",     0,        Set_WX },
    { "w=#",    0,        SetWarningLevel },
    { "zld",    0,        Set_ZLD },
    { "zq",     0,        Set_ZQ },
    { 0,        0,        0 }
};

global_options Options = {
    /* sign_value       */      FALSE,
    /* stop_at_end      */      FALSE,
    /* quiet            */      FALSE,
    /* banner_printed   */      FALSE,
    /* debug_flag       */      FALSE,
    /* naming_convention*/      DO_NOTHING,
    /* floating_point   */      DO_FP_EMULATION,
    /* output_data_in_code_records */   TRUE,

    /* error_count      */      0,
    /* warning_count    */      0,
    /* error_limit      */      20,
    /* warning_level    */      2,
    /* warning_error    */      FALSE,
    /* build_target     */      NULL,

    /* code_class       */      NULL,
    /* data_seg         */      NULL,
    /* test_seg         */      NULL,
    /* module_name      */      NULL,

    #ifdef DEBUG_OUT
    /* debug            */      FALSE,
    #endif
    /* default_name_mangler */  NULL,
    /* allow_c_octals   */      FALSE,
    /* emit_dependencies */     TRUE
};

static int OptionDelimiter( char c )
/*********************************/
{
    if( c == ' ' || c == '-' || c == '\0' || c == '\t' || c == SwitchChar ) {
        return( 1 );
    }
    return( 0 );
}

static int isvalidident( char *id )
/*********************************/
{
    char *s;
    char lwr_char;

    if( isdigit( *id ) ) return( ERROR ); /* can't start with a number */
    for( s = id; *s != '\0'; s++ ) {
        lwr_char = tolower( *s );
        if( !( lwr_char == '_' || lwr_char == '.' || lwr_char == '$'
                || lwr_char == '@' || lwr_char == '?'
                || isdigit( lwr_char )
                || islower( lwr_char ) ) ) {
            return( ERROR );
        }
    }
    return( NOT_ERROR );
}

static void get_os_include( void )
/********************************/
{
    char *env;
    char *tmp;

    /* add OS_include to the include path */

    tmp = AsmTmpAlloc( strlen( Options.build_target ) + 10 );
    strcpy( tmp, Options.build_target );
    strcat( tmp, "_INCLUDE" );

    env = getenv( tmp );
    if( env != NULL ) AddStringToIncludePath( env );
}

static void do_init_stuff( char **cmdline )
/******************************************/
{
    char        *env;
    char        *src;
    char        *dst;
    char        buff[80];

    if( !MsgInit() ) exit(1);

    AsmInit(-1, -1, -1);                // initialize hash table
    strcpy( buff, "__WASM__=" );
    dst = &buff[ strlen(buff) ];
    src = (char *)FingerMsg[0];
    while( !isdigit( *src ) ) ++src;
    while( isdigit( *src ) ) {
        *dst++ = *src++;
    }
    dst[0] = '0';
    dst[1] = '0';
    dst[2] = '\0';
    if( *src == '.' ) {
        if( isdigit( src[1] ) ) dst[0] = src[1];
        if( isdigit( src[2] ) ) dst[0] = src[2];
    }
    add_constant( buff );
    do_envvar_cmdline( "WASM", 0 );
    parse_cmdline( cmdline );
    ModuleInit();
    set_build_target();
    set_cpu_parameters();
    set_fpu_parameters();
    get_os_include();
    env = getenv( "INCLUDE" );
    if( env != NULL ) AddStringToIncludePath( env );
    if( !Options.quiet && !Options.banner_printed ) {
        Options.banner_printed = TRUE;
        trademark();
    }
    open_files();
    PushLineQueue();
}

#ifndef __WATCOMC__
char **_argv;
#endif

#ifdef __UNIX__

int main( int argc, char **argv )
/********************************/
{
    argc = argc;
#ifndef __WATCOMC__
    _argv = argv;
#endif

#else

int main()
/********************************/
{
    char       *argv[2];
    int        len;
    char       *buff;
#endif

    main_init();
    SwitchChar = _dos_switch_char();
#ifndef __UNIX__
    len = _bgetcmd( NULL, INT_MAX ) + 1;
    buff = malloc( len );
    if( buff != NULL ) {
        argv[0] = buff;
        argv[1] = NULL;
        _bgetcmd( buff, len );
    } else {
        return(-1);
    }
    do_init_stuff( argv );
#else
    do_init_stuff( &argv[1] );
#endif
    WriteObjModule();           // main body: parse the source file
    if( !Options.quiet ) {
        PrintStats();
    }
    MsgFini();
    main_fini();
#ifndef __UNIX__
    free( buff );
#endif
    return( Options.error_count ); /* zero if no errors */
    }

static void usage_msg( void )
/***************************/
{
    PrintfUsage( MSG_USE_BASE );
    exit(1);
}

int trademark( void )
/*******************/
{
    int         count = 0;

    if( !Options.quiet ) {
        while( FingerMsg[count] != NULL ) {
            printf( "%s\n", FingerMsg[count++] );
        }
    }
    return( count );
}

static void free_names( void )
/***************************/
/* Free names set as cmdline options */
{
    if( Options.build_target != NULL ) {
        AsmFree( Options.build_target );
    }
    if( Options.code_class != NULL ) {
        AsmFree( Options.code_class );
    }
    if( Options.data_seg != NULL ) {
        AsmFree( Options.data_seg );
    }
    if( Options.module_name != NULL ) {
        AsmFree( Options.module_name );
    }
    if( Options.text_seg != NULL ) {
        AsmFree( Options.text_seg );
    }
}

static void main_init( void )
/***************************/
{
    int         i;

#ifdef TRMEM
    MemInit();
#endif
    for( i=ASM; i<=OBJ; i++ ) {
        AsmFiles.file[i] = NULL;
        AsmFiles.fname[i] = NULL;
    }
    ObjRecInit();
    GenMSOmfInit();
}

static void main_fini( void )
/***************************/
{
    free_names();
    GenMSOmfFini();
    AsmShutDown();
}

static void open_files( void )
/****************************/
{
    /* open ASM file */
    AsmFiles.file[ASM] = fopen( AsmFiles.fname[ASM], "r" );

    if( AsmFiles.file[ASM] == NULL ) {
        Fatal( MSG_CANNOT_OPEN_FILE, AsmFiles.fname[ASM] );
    }

    /* open OBJ file */
    pobjState.file_out = ObjWriteOpen( AsmFiles.fname[OBJ] );
    if( pobjState.file_out == NULL ) {
        Fatal( MSG_CANNOT_OPEN_FILE, AsmFiles.fname[OBJ] );
    }
    pobjState.pass = POBJ_WRITE_PASS;

    /* delete any existing ERR file */
    DelErrFile();
}

static void get_fname( char *token, int type )
/********************************************/
/*
 * figure out the source file name & store it in AsmFiles
 * fill in default object file name if it is null
 */
{
    char        *def_drive, *def_dir, *def_fname, *def_ext;
    char        *drive, *dir, *fname, *ext;
    char        buffer[ _MAX_PATH2 ];
    char        buffer2[ _MAX_PATH2 ];
    char        name [ _MAX_PATH  ];
    char        msgbuf[80];

    /* get filename for source file */

    if( type == ASM ) {
        if( token == NULL ) {
            MsgGet( SOURCE_FILE, msgbuf );
            Fatal( MSG_CANNOT_OPEN_FILE, msgbuf );
        }
        if( AsmFiles.fname[ASM] != NULL ) {
            Fatal( MSG_TOO_MANY_FILES );
        }

        _splitpath2( token, buffer, &drive, &dir, &fname, &ext );
        if( *ext == '\0' ) {
            ext = ASM_EXT;
        }
        _makepath( name, drive, dir, fname, ext );
        AsmFiles.fname[ASM] = AsmAlloc( strlen( name ) + 1 );
        strcpy( AsmFiles.fname[ASM], name );

        _makepath( name, drive, dir, NULL, NULL );
        /* add the source path to the include path */
        AddStringToIncludePath( name );

        if( AsmFiles.fname[OBJ] == NULL ) {
            /* set up default object and error filename */
            ext = OBJ_EXT;
            _makepath( name, NULL, NULL, fname, ext );
        } else {
            _splitpath2( AsmFiles.fname[OBJ], buffer2, &def_drive,
                         &def_dir, &def_fname, &def_ext );
            if( *def_fname == NULLC ) def_fname = fname;
            if( *def_ext == NULLC ) def_ext = OBJ_EXT;

            _makepath( name, def_drive, def_dir, def_fname, def_ext );
            AsmFree( AsmFiles.fname[OBJ] );
        }
        AsmFiles.fname[OBJ] = AsmAlloc( strlen( name ) + 1 );
        strcpy( AsmFiles.fname[OBJ], name );

        if( AsmFiles.fname[ERR] == NULL ) {
            ext = ERR_EXT;
            _makepath( name, NULL, NULL, fname, ext );
        } else {
            _splitpath2( AsmFiles.fname[ERR], buffer2, &def_drive,
                         &def_dir, &def_fname, &def_ext );
            if( *def_fname == NULLC ) def_fname = fname;
            if( *def_ext == NULLC ) def_ext = ERR_EXT;
            _makepath( name, def_drive, def_dir, def_fname, def_ext );
            AsmFree( AsmFiles.fname[ERR] );
        }
        AsmFiles.fname[ERR] = AsmAlloc( strlen( name ) + 1 );
        strcpy( AsmFiles.fname[ERR], name );

    } else {
        /* get filename for object file */
        _splitpath2( token, buffer, &drive, &dir, &fname, &ext );
        if( AsmFiles.fname[ASM] != NULL ) {
            _splitpath2( AsmFiles.fname[ASM], buffer2, &def_drive,
                         &def_dir, &def_fname, &def_ext );
            if( *fname == NULLC ) {
                fname = def_fname;
            }
        }
        if( *ext == NULLC ) {
            ext = type == ERR ? ERR_EXT : OBJ_EXT;
        }
        _makepath( name, drive, dir, fname, ext );
        if( AsmFiles.fname[type] != NULL ) {
            AsmFree( AsmFiles.fname[type] );
        }
        AsmFiles.fname[type] = AsmAlloc( strlen( name ) + 1 );
        strcpy( AsmFiles.fname[type], name );
    }
}

static void do_envvar_cmdline( char *envvar )
/******************************************************/
{
    char *cmdline;
    int  level = 0;

    cmdline = getenv( envvar );
    if( cmdline != NULL ) {
        ProcOptions( cmdline, &level );
    }
    return;
}

static void add_constant( char *string )
/**************************************/
{
    char *tmp;
    char *one = "1";

    tmp = strchr( string, '=' );
    if( tmp == NULL ) {
        tmp = strchr( string, '#' );
        if( tmp == NULL ) {
            tmp = one;
        } else {
            *tmp = '\0';
            tmp++;
        }
    } else {
        *tmp = '\0';
        tmp++;
    }

    if( isvalidident( string ) == ERROR ) {
        AsmError( SYNTAX_ERROR ); // fixme
        return;
    }

    StoreConstant( string, tmp, FALSE ); // don't allow it to be redef'd
    return;
}

static void set_cpu_parameters( void )
{
    int token;
    
    if( SWData.naming_convention == 'r' ) {
        Options.naming_convention = ADD_USCORES;
        add_constant( "__REGISTER__" );
    } else if( SWData.naming_convention == 's' ) {
        add_constant( "__STACK__" );
        Options.naming_convention = DO_NOTHING;
    } else if( SWData.naming_convention == '_' ) {
        if( Options.naming_convention == DO_NOTHING ) {
            Options.naming_convention = REMOVE_USCORES;
        } else {
            Options.naming_convention = DO_NOTHING;
        }
    }
    switch( SWData.cpu ) {
    case 0:
        token = T_DOT_8086;
        break;
    case 1:
        token = T_DOT_186;
        break;
    case 2:
        token =  SWData.protect_mode ? T_DOT_286P : T_DOT_286;
        break;
    case 3:
        token =  SWData.protect_mode ? T_DOT_386P : T_DOT_386;
        break;
    case 4:
        token =  SWData.protect_mode ? T_DOT_486P : T_DOT_486;
        break;
    case 5:
        token =  SWData.protect_mode ? T_DOT_586P : T_DOT_586;
        break;
    case 6:
        token =  SWData.protect_mode ? T_DOT_686P : T_DOT_686;
        break;
    default: // default CPU is 8086
        token = T_DOT_8086;
        break;
    }
    cpu_directive( token );
}

static void set_fpu_parameters( void )
/**********************************/
{
    switch( Options.floating_point ) {
    case DO_FP_EMULATION:
        add_constant("__FPI__");
        break;
    case NO_FP_EMULATION:
        add_constant("__FPI87__");
        break;
    case NO_FP_ALLOWED:
        add_constant("__FPC__");
        cpu_directive( T_DOT_NO87 );
        return;
    }
    switch( SWData.fpu ) {
    case -1: // default FPU is none
        cpu_directive( T_DOT_NO87 );
        break;
    case 0:
    case 1:
        cpu_directive( T_DOT_8087 );
        break;
    case 2:
        cpu_directive( T_DOT_287 );
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        cpu_directive( T_DOT_387 );
        break;
    case 7:
        switch( SWData.cpu ) {
        case 0:
        case 1:
            cpu_directive( T_DOT_8087 );
            break;
        case 2:
            cpu_directive( T_DOT_287 );
            break;
        case 3:
        case 4:
        case 5:
        case 6:
            cpu_directive( T_DOT_387 );
            break;
        default: // default CPU is 8086
            cpu_directive( T_DOT_8087 );
            break;
        }
        break;
    default: // default FPU is none
        cpu_directive( T_DOT_NO87 );
        break;
    }
}

static int set_build_target( void )
/*********************************/
{
    char *tmp;
    char *uscores = "__";

    if( Options.build_target == NULL ) {
        #define MAX_OS_NAME_SIZE 7
        Options.build_target = AsmAlloc( MAX_OS_NAME_SIZE + 1 );
        #if defined(__OSI__)
            if( __OS == OS_DOS ) {
                strcpy( Options.build_target, "DOS" );
            } else if( __OS == OS_OS2 ) {
                strcpy( Options.build_target, "OS2" );
            } else if( __OS == OS_NT ) {
                strcpy( Options.build_target, "NT" );
            } else if( __OS == OS_WIN ) {
                strcpy( Options.build_target, "WINDOWS" );
            } else {
                strcpy( Options.build_target, "XXX" );
            }
        #elif defined(__QNX__)
            strcpy( Options.build_target, "QNX" );
        #elif defined(__LINUX__)
            strcpy( Options.build_target, "LINUX" );
        #elif defined(__DOS__)
            strcpy( Options.build_target, "DOS" );
        #elif defined(__OS2__)
            strcpy( Options.build_target, "OS2" );
        #elif defined(__NT__)
            strcpy( Options.build_target, "NT" );
        #else
            #error unknown host OS
        #endif
    }

    strupr( Options.build_target );
    tmp = AsmTmpAlloc( strlen( Options.build_target ) + 5 ); // null + 4 uscores
    strcpy( tmp, uscores );
    strcat( tmp, Options.build_target );
    strcat( tmp, uscores );

    add_constant( tmp ); // always define something

    if( stricmp( Options.build_target, "DOS" ) == 0 ) {
        add_constant( "__MSDOS__" );
    } else if( stricmp( Options.build_target, "NETWARE" ) == 0 ) {
        if( (Code->info.cpu&P_CPU_MASK) >= P_386 ) {
            add_constant( "__NETWARE_386__" );
        } else {
            /* do nothing ... __NETWARE__ already defined */
        }
    } else if( stricmp( Options.build_target, "WINDOWS" ) == 0 ) {
        if( (Code->info.cpu&P_CPU_MASK) >= P_386 ) {
            add_constant( "__WINDOWS_386__" );
        } else {
            /* do nothing ... __WINDOWS__ already defined */
        }
    } else if( stricmp( Options.build_target, "QNX" ) == 0 ) {
        add_constant( "__UNIX__" );
    } else if( stricmp( Options.build_target, "LINUX" ) == 0 ) {
        add_constant( "__UNIX__" );
    }
    return( NOT_ERROR );
}

static void set_some_kinda_name( char token, char *name )
/*******************************************************/
/* set:  code class / data seg. / module name / text seg */
{
    int len;
    char **tmp;

    len = strlen( name ) + 1;
    switch( token ) {
    case 'c':
        tmp = &Options.code_class;
        break;
    case 'd':
        tmp = &Options.data_seg;
        break;
    case 'm':
        tmp = &Options.module_name;
        break;
    case 't':
        tmp = &Options.text_seg;
        break;
    default:
        return;
    }
    if( *tmp != NULL ) {
        AsmFree(*tmp);
    }
    *tmp = AsmAlloc( len );
    strcpy( *tmp, name );
    return;
}

static char *CollectEnvOrFileName( char *str )
/*******************************************/
{
    char        *env;
    char        ch;

    while( *str == ' ' || *str == '\t' ) ++str;
    env = ParamBuf;
    for( ;; ) {
        ch = *str;
        if( ch == '\0' ) break;
        ++str;
        if( ch == ' ' ) break;
        if( ch == '\t' ) break;
        #if !defined(__UNIX__)
            if( ch == '-' ) break;
            if( ch == SwitchChar ) break;
        #endif
        *env++ = ch;
    }
    *env = '\0';
    return( str );
}

static char *ReadIndirectFile()
/*******************************************/
{
    char        *env;
    char        *str;
    int         handle;
    int         len;
    char        ch;

    env = NULL;
    handle = open( ParamBuf, O_RDONLY | O_BINARY );
    if( handle != -1 ) {
        len = filelength( handle );
        env = AsmAlloc( len + 1 );
        read( handle, env, len );
        env[len] = '\0';
        close( handle );
        // zip through characters changing \r, \n etc into ' '
        str = env;
        while( *str ) {
            ch = *str;
            if( ch == '\r' || ch == '\n' ) {
                *str = ' ';
            }
            #if !defined(__UNIX__)
                if( ch == 0x1A ) {      // if end of file
                    *str = '\0';        // - mark end of str
                    break;
                }
            #endif
            ++str;
        }
    }
    return( env );
}

static char *ProcessOption( char *p, char *option_start )
/*******************************************/
{
    int         i;
    int         j;
    char        *opt;
    char        c;

    for( i = 0; ; i++ ) {
        opt = cmdl_options[i].option;
        if( opt == NULL ) break;
        c = tolower( *p );
        if( c == *opt ) {
            OptValue = cmdl_options[i].value;
            j = 1;
            for(;;) {
                ++opt;
                if( *opt == '\0' || *opt == '*' ) {
                    if( *opt == '\0' ) {
                        if( p - option_start == 1 ) {
                            // make sure end of option
                            if( !OptionDelimiter( p[j] ) ) break;
                        }
                    }
                    OptScanPtr = p + j;
                    cmdl_options[i].function();
                    return( OptScanPtr );
                }
                if( *opt == '#' ) {             // collect a number
                    if( p[j] >= '0' && p[j] <= '9' ) {
                        OptValue = 0;
                        for(;;) {
                            c = p[j];
                            if( c < '0' || c > '9' ) break;
                            OptValue = OptValue * 10 + c - '0';
                            ++j;
                        }
                    }
                } else if( *opt == '$' ) {      // collect an identifer
                    OptParm = &p[j];
                    for(;;) {
                        c = p[j];
                        if( c == '\0' ) break;
                        if( c == '-' ) break;
                        if( c == ' ' ) break;
                        if( c == SwitchChar ) break;
                        ++j;
                    }
                } else if( *opt == '@' ) {      // collect a filename
                    OptParm = &p[j];
                    c = p[j];
                    if( c == '"' ){ // "filename"
                        for(;;){
                            c = p[++j];
                            if( c == '"' ){
                                ++j;
                                break;
                            }
                            if( c == '\0' )break;
                            if( c == '\\' ){
                                ++j;
                            }
                        }
                    }else{
                        for(;;) {
                            c = p[j];
                            if( c == '\0' ) break;
                            if( c == ' ' ) break;
                            if( c == '\t' ) break;
                            #if !defined(__UNIX__)
                                if( c == SwitchChar ) break;
                            #endif
                            ++j;
                        }
                    }
                } else if( *opt == '=' ) {      // collect an optional '='
                    if( p[j] == '=' || p[j] == '#' ) ++j;
                } else {
                    c = tolower( p[j] );
                    if( *opt != c ) {
                        if( *opt < 'A' || *opt > 'Z' ) break;
                        if( *opt != p[j] ) break;
                    }
                    ++j;
                }
            }
        }
    }
    MsgPrintf1( MSG_UNKNOWN_OPTION, option_start );
    exit( 1 );
    return( NULL );
}

static int ProcOptions( char *str, int *level )
/*******************************************************/
{
    char *save[MAX_NESTING];
    char *buffers[MAX_NESTING];
        
    if( str != NULL ) {
        for(;;) {
            while( *str == ' ' || *str == '\t' ) ++str;
            if( *str == '@' && *level < MAX_NESTING ) {
                save[(*level)++] = CollectEnvOrFileName( str + 1 );
                buffers[*level] = NULL;
                str = getenv( ParamBuf );
                if( str == NULL ) {
                    str = ReadIndirectFile();
                    buffers[*level] = str;
                }
                if( str != NULL )  continue;
                str = save[--(*level)];
            }
            if( *str == '\0' ) {
                if( *level == 0 ) break;
                if( buffers[*level] != NULL ) {
                    AsmFree( buffers[*level] );
                    buffers[*level] = NULL;
                }
                str = save[--(*level)];
                continue;
            }
            if( *str == '-'  ||  *str == SwitchChar ) {
                str = ProcessOption(str+1, str);
            } else {  /* collect  file name */
                char *beg, *p;
                int len;

                beg = str;
                if( *str == '"' ){
                    for(;;){
                        ++str;
                        if( *str == '"' ){
                            ++str;
                            break;
                        }
                        if( *str == '\0' ) break;
                        if( *str == '\\' ){
                            ++str;
                        }
                    }
                }else{
                    for(;;) {
                        if( *str == '\0' ) break;
                        if( *str == ' '  ) break;
                        if( *str == '\t'  ) break;
                        #if !defined(__UNIX__)
                            if( *str == SwitchChar ) break;
                        #endif
                        ++str;
                    }
                }
                len = str-beg;
                p = (char *) AsmAlloc( len + 1 );
                memcpy( p, beg, len );
                p[ len ] = '\0';
                StripQuotes( p );
                get_fname( p, ASM );
                AsmFree(p);
            }
        }
    }
    return 0;
}

static void parse_cmdline( char **cmdline )
/*************************************************/
{
    char msgbuf[80];
    int  level = 0;

    if( cmdline == NULL || *cmdline == NULL || **cmdline == 0 ) {
        usage_msg();
    }
    for( ;*cmdline != NULL; ++cmdline ) {
        ProcOptions( *cmdline, &level );
    }
    if( AsmFiles.fname[ASM] == NULL ) {
        MsgGet( NO_FILENAME_SPECIFIED, msgbuf );
        Fatal( MSG_CANNOT_OPEN_FILE, msgbuf );
    }
}

/* The following are functions needed by the original stand-alone assembler */

extern enum sym_state   AsmQueryExternal( char *name )
{
    name = name;
    return SYM_UNDEFINED;
}

extern enum sym_type    AsmQueryType( char *name )
{
    name = name;
    return SYM_INT1;
}
