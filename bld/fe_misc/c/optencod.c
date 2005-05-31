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


#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "lsspec.h"
#include "encodlng.h"

// functions that are supplied by the host environment
#define FN_UNGET        "OPT_UNGET"         // void ( void )
#define FN_GET_LOWER    "OPT_GET_LOWER"     // int ( void )
#define FN_RECOG        "OPT_RECOG"         // int ( int )
#define FN_RECOG_LOWER  "OPT_RECOG_LOWER"   // int ( int )
#define FN_END          "OPT_END"           // int ( void )

#define FN_NUMBER       "OPT_GET_NUMBER"    // int ( unsigned * )
#define FN_NUMBER_DEFAULT "OPT_GET_NUMBER_DEFAULT"  // int ( unsigned *, unsigned )
#define FN_NUMBER_MULTIPLE "OPT_GET_NUMBER_MULTIPLE"    // int ( OPT_NUMBER ** )
#define FN_CHAR         "OPT_GET_CHAR"      // int ( int * )
#define FN_CHAR_OPT     "OPT_GET_CHAR_OPT"  // int ( int * )
#define FN_ID           "OPT_GET_ID"        // int ( OPT_STRING ** )
#define FN_ID_OPT       "OPT_GET_ID_OPT"    // int ( OPT_STRING ** )
#define FN_FILE         "OPT_GET_FILE"      // int ( OPT_STRING ** )
#define FN_FILE_OPT     "OPT_GET_FILE_OPT"  // int ( OPT_STRING ** )
#define FN_DIR          "OPT_GET_DIR"       // int ( OPT_STRING ** )
#define FN_DIR_OPT      "OPT_GET_DIR_OPT"   // int ( OPT_STRING ** )
#define FN_PATH         "OPT_GET_PATH"      // int ( OPT_STRING ** )
#define FN_PATH_OPT     "OPT_GET_PATH_OPT"  // int ( OPT_STRING ** )

#define FN_CLEAN_STRING "OPT_CLEAN_STRING"    // void ( OPT_STRING ** )
#define FN_CLEAN_NUMBER "OPT_CLEAN_NUMBER"    // void ( OPT_NUMBER ** )

#define FN_PROCESS      "OPT_PROCESS"       // int ( OPT_STORAGE * )
#define FN_INIT         "OPT_INIT"          // void ( OPT_STORAGE * )
#define FN_FINI         "OPT_FINI"          // void ( OPT_STORAGE * )

#define USE_SWITCH_THRESHOLD    (4)
#define CONSOLE_WIDTH           (79)

unsigned line;
FILE *gfp;
FILE *ofp;
FILE *pfp;
FILE *ufp;
FILE *mfp;
FILE *bfp;

#define BUFF_SIZE       1024
static char ibuff[BUFF_SIZE];
static char tagbuff[BUFF_SIZE];
static char tokbuff[BUFF_SIZE];
static char enumbuff[BUFF_SIZE];
static char hdrbuff[BUFF_SIZE];
static char maxusgbuff[BUFF_SIZE];

typedef struct option OPTION;
typedef struct codeseq CODESEQ;

#define CHAIN_YES       0x01
#define CHAIN_USAGE     0x02
static char alternateEqual;
static char chainOption[256];
static char *chainUsage[256][LANG_MAX];
static char lastChain;
static unsigned maxUsageLen;
static char *pageUsage[LANG_MAX];
static unsigned targetMask;
static unsigned targetAnyMask;
static unsigned targetDbgMask;
static unsigned nextTargetMask = 1;

typedef enum tag_id {
#define TAG( s )        TAG_##s ,
#include "opttags.h"
    TAG_UNKNOWN,
    TAG_NULL
} tag_id;

static tag_id getsUsage = TAG_NULL;

#define TAG( s )        #s ,
char *tagNames[] = {
#include "opttags.h"
    NULL };

#define TAG( s )        void do##s( char * );
#include "opttags.h"

#define TAG( s )        do##s ,
void (*processTag[])( char * ) = {
#include "opttags.h"
    NULL };

static char *validTargets[] = {
    "any",
    "i86",
    "386",
    "axp",
    "ppc",
    "dbg",
    "linux",
    "qnx",
    "sparc",
    NULL
};

static const char * const langName[] = {
    #define LANG_DEF( id, dbcs )        #id ,
    LANG_DEFS
    #undef LANG_DEF
};

static uint_8 const langMaxChar[] = {
    #define LANG_DEF( id, dbcs )        dbcs ,
    LANG_DEFS
    #undef LANG_DEF
};

static char *usageMsg[] = {
    "optencod [-i] [-q] [-u <usage-u>] <gml-file> <option-h> <parse-c> <usage-h> <target>*",
    "where:",
    "    <gml-file> is the tagged input GML file",
    "    <parse-h> is the output file for the command line parser",
    "    <usage-h> is the output file for the usage message",
    "    <usage-u> is the output file for the QNX usage file",
    "    <target> can be chosen from:",
    NULL
};

static struct {
    unsigned    international : 1;
    unsigned    quiet : 1;
    unsigned    no_equal : 1;
    unsigned    alternate_equal : 1;
} optFlag;

typedef struct target TARGET;
struct target {
    TARGET      *next;
    unsigned    mask;
    char        name[1];
};
static TARGET *targetList;

struct option {
    OPTION      *next;
    OPTION      *synonym;
    char        *lang_usage[LANG_MAX];
    char        *check;
    char        *special;
    char        *special_arg_usage;
    char        *field_name;
    char        *value_field_name;
    char        *enumerate;
    char        *immediate;
    char        *code;
    unsigned    number_default;
    unsigned    target;
    unsigned    ntarget;
    unsigned    default_specified : 1;
    unsigned    is_simple : 1;
    unsigned    is_immediate : 1;
    unsigned    is_code : 1;
    unsigned    is_internal : 1;
    unsigned    is_multiple : 1;
    unsigned    is_number : 1;
    unsigned    is_id : 1;
    unsigned    is_char : 1;
    unsigned    is_file : 1;
    unsigned    is_dir : 1;
    unsigned    is_optional : 1;
    unsigned    is_path : 1;
    unsigned    is_special : 1;
    unsigned    is_prefix : 1;
    unsigned    is_timestamp : 1;
    unsigned    is_negate : 1;
    unsigned    nochain : 1;
    char        name[1];
};
static OPTION *optionList;
static OPTION *uselessOptionList;

#define HAS_OPT_STRING( o ) ( (o)->is_id || (o)->is_file || (o)->is_dir || (o)->is_path || (o)->is_special )
#define HAS_OPT_NUMBER( o ) ( (o)->is_number && (o)->is_multiple )

struct codeseq {
    CODESEQ     *sibling;
    CODESEQ     *children;
    OPTION      *option;
    int         c;
    unsigned    sensitive : 1;
    unsigned    accept : 1;
    unsigned    chain : 1;
};

typedef struct name NAME;
struct name {
    NAME        *next;
    char        name[1];
};

static NAME *enumList;
static NAME *enumeratorList;

typedef struct title TITLE;
struct title {
    TITLE       *next;
    unsigned    target;
    unsigned    ntarget;
    char        *lang_title[LANG_MAX];
};
static TITLE *titleList;
static TITLE *targetTitle;

enum {
    EC_CONTINUE         = 0x01,
    EC_NULL             = 0
};

static void fail( char *msg, ... )
{
    va_list args;

    if( line ) {
        fprintf( stderr, "error on line %u\n", line );
    }
    va_start( args, msg );
    vfprintf( stderr, msg, args );
    va_end( args );
    exit( EXIT_FAILURE );
}

static void dumpUsage( void )
{
    char **p;

    for( p = usageMsg; *p; ++p ) {
        fprintf( stderr, "%s\n", *p );
    }
    fprintf( stderr, "        " );
    for( p = validTargets; *p; ++p ) {
        fprintf( stderr, "%s ", *p );
    }
    fprintf( stderr, "\n", *p );
}

static void emitPrintf( unsigned depth, char *msg, ... )
{
    va_list args;
    unsigned i;

    for( i = ( depth >> 1 ); i != 0; --i ) {
        fprintf( pfp, "\t" );
    }
    if( depth & 1 ) {
        fprintf( pfp, "    " );
    }
    va_start( args, msg );
    vfprintf( pfp, msg, args );
    va_end( args );
}

static void addTarget( char *t )
{
    size_t len;
    TARGET *p;

    len = strlen( t );
    p = malloc( sizeof( *p ) + len );
    p->mask = nextTargetMask;
    p->next = targetList;
    targetList = p;
    strcpy( p->name, t );
    nextTargetMask <<= 1;
    if( nextTargetMask == 0 ) {
        fail( "too many targets defined\n" );
    }
}

static unsigned findTarget( char *t )
{
    TARGET *p;

    for( p = targetList; p != NULL; p = p->next ) {
        if( strcmp( t, p->name ) == 0 ) {
            return( p->mask );
        }
    }
    fail( "invalid target name '%s'\n", t );
    return( 0 );
}

static char *findName( NAME **h, char *n )
{
    NAME *p;

    for( p = *h; p != NULL; p = p->next ) {
        if( strcmp( n, p->name ) == 0 ) {
            return( p->name );
        }
    }
    return( NULL );
}

static char *addName( NAME **h, char *n )
{
    size_t len;
    NAME *p;

    len = strlen( n );
    p = malloc( sizeof(*p) + len );
    strcpy( p->name, n );
    p->next = *h;
    *h = p;
    return( p->name );
}

static char *addEnumerator( char *enumerate, char *field_name )
{
    char *n;

    strcpy( enumbuff, "OPT_" );
    strcat( enumbuff, enumerate );
    strcat( enumbuff, "_" );
    strcat( enumbuff, field_name );
    n = findName( &enumeratorList, enumbuff );
    if( n == NULL ) {
        n = addName( &enumeratorList, enumbuff );
    }
    return( n );
}

static void procCmdLine( int argc, char **argv )
{
    char **t;
    unsigned mask;

    if( argc < 5 ) {
        dumpUsage();
        exit( EXIT_FAILURE );
    }
    if( strcmp( argv[1], "-i" ) == 0 ) {
        optFlag.international = 1;
        --argc;
        ++argv;
    }
    if( strcmp( argv[1], "-q" ) == 0 ) {
        optFlag.quiet = 1;
        --argc;
        ++argv;
    }
    if( strcmp( argv[1], "-u" ) == 0 ) {
        mfp = fopen( argv[2], "wb" );
        if( !mfp ) fail( "cannot open '%s' for output", argv[2] );
        argc -= 2;
        argv += 2;
    }
    if( argc < 5 ) {
        dumpUsage();
        exit( EXIT_FAILURE );
    }
    ++argv;
    gfp = fopen( argv[0], "r" );
    if( !gfp ) fail( "cannot open '%s' for input", argv[0] );
    ++argv;
    ofp = fopen( argv[0], "w" );
    if( !ofp ) fail( "cannot open '%s' for output", argv[0] );
    ++argv;
    pfp = fopen( argv[0], "w" );
    if( !pfp ) fail( "cannot open '%s' for output", argv[0] );
    ++argv;
    ufp = fopen( argv[0], "w" );
    if( !ufp ) fail( "cannot open '%s' for output", argv[0] );
    ++argv;
    for( t = validTargets; *t; ++t ) {
        addTarget( *t );
    }
    targetAnyMask = findTarget( "any" );
    targetDbgMask = findTarget( "dbg" );
    targetMask |= targetAnyMask;
    while( *argv ) {
        mask = findTarget( *argv );
        targetMask |= mask;
        ++argv;
    }
}

static char *skipSpace( char *p )
{
    while( *p && isspace( *p ) ) {
        ++p;
    }
    return( p );
}

static char *copyNonSpaceUntil( char *i, char *o, char t )
{
    for( ; *i; ++i ) {
        if( isspace( *i ) ) break;
        if( *i == t ) {
            ++i;
            break;
        }
        *o = *i;
        ++o;
    }
    *o = '\0';
    return( i );
}

static tag_id findTag( char *t )
{
    char **c;

    for( c = tagNames; *c; ++c ) {
        if( stricmp( t, *c ) == 0 ) {
            return( c - tagNames );
        }
    }
    fail( "unknown tag: %s\n", t );
    return( TAG_UNKNOWN );
}

static tag_id isTag( char **eot )
{
    tag_id tag;
    char *p;

    p = ibuff;
    p = skipSpace( p );
    if( *p == ':' ) {
        ++p;
        p = copyNonSpaceUntil( p, tagbuff, '.' );
        tag = findTag( tagbuff );
        if( tag != TAG_UNKNOWN ) {
            *eot = p;
            return( tag );
        }
    }
    return( TAG_NULL );
}

static OPTION *pushNewOption( char *name, OPTION *same )
{
    size_t len;
    OPTION *p;

    len = strlen( name );
    p = calloc( 1, sizeof( *p ) + len );
    p->synonym = same;
    strcpy( p->name, name );
    p->is_simple = 1;
    p->next = optionList;
    optionList = p;
    return( p );
}

static char *pickUpRest( char *p )
{
    size_t len;

    len = strlen( p );
    if( len != 0 ) {
        if( p[len-1] == '\n' ) {
            p[len-1] = '\0';
        }
    }
    return( strdup( p ) );
}

// :argequal. <char>
static void doARGEQUAL( char *p )
{
    p = skipSpace( p );
    if( *p == '\0' ) {
        fail( ":argequal. must have <char> specified\n" );
    } else {
        alternateEqual = *p;
        optFlag.alternate_equal = 1;
    }
}

// :cmt comment text
static void doCMT( char *p )
{
    p = p;
}

// :internal.
static void doINTERNAL( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_internal = 1;
    }
}

// :option. <option> <synonym> ...
static void doOPTION( char *p )
{
    OPTION *synonym;

    targetTitle = NULL;
    synonym = NULL;
    while( *p ) {
        p = skipSpace( p );
        if( *p == '\0' ) break;
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        synonym = pushNewOption( tokbuff, synonym );
    }
    getsUsage = TAG_OPTION;
}

// :target. <targ> <targ> ...
static void doTARGET( char *p )
{
    unsigned mask;
    OPTION *o;

    while( *p ) {
        p = skipSpace( p );
        if( *p == '\0' ) break;
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        mask = findTarget( tokbuff );
        if( targetTitle != NULL ) {
            targetTitle->target |= mask;
        } else {
            for( o = optionList; o != NULL; o = o->synonym ) {
                o->target |= mask;
            }
        }
    }
}

// :ntarget. <targ> <targ> ...
static void doNTARGET( char *p )
{
    unsigned mask;
    OPTION *o;

    while( *p ) {
        p = skipSpace( p );
        if( *p == '\0' ) break;
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        mask = findTarget( tokbuff );
        if( targetTitle != NULL ) {
            targetTitle->ntarget |= mask;
        } else {
            for( o = optionList; o != NULL; o = o->synonym ) {
                o->ntarget |= mask;
            }
        }
    }
}

// :number. [<fn>] [<default>]
static void doNUMBER( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_number = 1;
        o->is_simple = 0;
    }
    p = skipSpace( p );
    if( *p != '\0' ) {
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        for( o = optionList; o != NULL; o = o->synonym ) {
            o->check = strdup( tokbuff );
        }
        p = skipSpace( p );
        if( *p != '\0' ) {
            p = copyNonSpaceUntil( p, tokbuff, '\0' );
            for( o = optionList; o != NULL; o = o->synonym ) {
                o->number_default = atoi( tokbuff );
                o->default_specified = 1;
            }
        }
    }
}

// :multiple.
static void doMULTIPLE( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_multiple = 1;
    }
}

// :nochain.
static void doNOCHAIN( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->nochain = 1;
    }
}

// :id. [<fn>]
static void doID( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_id = 1;
        o->is_simple = 0;
    }
    p = skipSpace( p );
    if( *p != '\0' ) {
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        for( o = optionList; o != NULL; o = o->synonym ) {
            o->check = strdup( tokbuff );
        }
    }
}

// :char. [<fn>]
static void doCHAR( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_char = 1;
        o->is_simple = 0;
    }
    p = skipSpace( p );
    if( *p != '\0' ) {
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        for( o = optionList; o != NULL; o = o->synonym ) {
            o->check = strdup( tokbuff );
        }
    }
}

// :immediate. <fn>
static void doIMMEDIATE( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_immediate = 1;
        o->is_simple = 0;
    }
    p = skipSpace( p );
    if( *p != '\0' ) {
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        for( o = optionList; o != NULL; o = o->synonym ) {
            o->immediate = strdup( tokbuff );
        }
    } else {
        fail( ":immediate. must have <fn> specified\n" );
    }
}

// :code. <source-code>
static void doCODE( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_code = 1;
        o->is_simple = 0;
    }
    p = skipSpace( p );
    if( *p != '\0' ) {
        for( o = optionList; o != NULL; o = o->synonym ) {
            o->code = strdup( p );
        }
    } else {
        fail( ":immediate. must have <fn> specified\n" );
    }
}

// :file.
static void doFILE( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_file = 1;
        o->is_simple = 0;
    }
}

// :dir.
static void doDIR( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_dir = 1;
        o->is_simple = 0;
    }
}

// :optional.
static void doOPTIONAL( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_optional = 1;
    }
}
// :negate.
static void doNEGATE( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_negate = 1;
        if( o->enumerate ){
            fail( "must be non-enumeration switch for negate tag\n" );
        }
    }
}


// :noequal.
static void doNOEQUAL( char *p )
{
    p = p;
    optFlag.no_equal = 1;
}

// :page. <text>
static void doPAGE( char *p )
{
    pageUsage[LANG_English] = pickUpRest( p );
    getsUsage = TAG_PAGE;
}

// :path.
static void doPATH( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_path = 1;
        o->is_simple = 0;
    }
}

// :chain. <char> <usage>
//
// mark options that start with <char> as chainable
// i.e., -oa -ox == -oax
static void doCHAIN( char *p )
{
    char c;

    p = skipSpace( p );
    if( *p == '\0' ) {
        fail( "missing <char> in :chain. tag\n" );
    }
    c = *p;
    chainOption[ c ] |= CHAIN_YES;
    ++p;
    p = skipSpace( p );
    chainUsage[ c ][ LANG_English ] = pickUpRest( p );
    lastChain = c;
    getsUsage = TAG_CHAIN;
}

// :enumerate. <name>
static void doENUMERATE( char *p )
{
    char *n;
    OPTION *o;

    p = skipSpace( p );
    if( *p == '\0' ) {
        fail( "missing <name> in :enumerate. tag\n" );
    }
    p = copyNonSpaceUntil( p, tokbuff, '\0' );
    n = findName( &enumList, tokbuff );
    if( n == NULL ) {
        n = addName( &enumList, tokbuff );
    }
    addEnumerator( tokbuff, "default" );
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->enumerate = strdup( tokbuff );
    }
}

// :special. <fn>
static void doSPECIAL( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_special = 1;
        o->is_simple = 0;
    }
    p = skipSpace( p );
    if( *p == '\0' ) {
        fail( "missing <fn> in :special. tag\n" );
    }
    p = copyNonSpaceUntil( p, tokbuff, '\0' );
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->special = strdup( tokbuff );
    }
    p = skipSpace( p );
    if( *p != '\0' ) {
        p = copyNonSpaceUntil( p, tokbuff, '\0' );
        for( o = optionList; o != NULL; o = o->synonym ) {
            o->special_arg_usage = strdup( tokbuff );
        }
    }
}

// :prefix.
static void doPREFIX( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_prefix = 1;
        o->is_simple = 0;
    }
}

// :usage. <usage-text>
static void doUSAGE( char *p )
{
    OPTION *o;

    for( o = optionList; o != NULL; o = o->synonym ) {
        o->lang_usage[ LANG_English ] = pickUpRest( p );
    }
}

// :jusage. <kanji-usage-text>
static void doJUSAGE( char *p )
{
    char *usage;
    OPTION *o;

    switch( getsUsage ) {
    case TAG_PAGE:
        pageUsage[LANG_Japanese] = pickUpRest( p );
        break;
    case TAG_CHAIN:
        chainUsage[lastChain][LANG_Japanese] = pickUpRest( p );
        break;
    case TAG_OPTION:
        for( o = optionList; o != NULL; o = o->synonym ) {
            usage = pickUpRest( p );
            if( *usage == '\0' ) {
                usage = strdup( o->lang_usage[LANG_English] );
            }
            o->lang_usage[LANG_Japanese] = usage;
        }
        break;
    default:
        fail( ":jusage. must follow :chain., :option., or :page.\n" );
    }
}

// :title. <text>
static void doTITLE( char *p )
{
    TITLE **i;
    TITLE *t;

    i = &titleList;
    for( t = *i; t != NULL; t = *i ) {
        i = &(t->next);
    }
    t = calloc( sizeof( *t ), 1 );
    t->next = *i;
    *i = t;
    t->target = 0;
    t->ntarget = 0;
    t->lang_title[ LANG_English ] = strdup( p );
    targetTitle = t;
}

// :jtitle. <text>
static void doJTITLE( char *p )
{
    TITLE *t;

    t = targetTitle;
    if( t == NULL ) {
        fail( ":jtitle. must follow a :title.\n" );
    }
    t->lang_title[ LANG_Japanese ] = strdup( p );
}

// :timestamp.
static void doTIMESTAMP( char *p )
{
    OPTION *o;

    p = p;
    for( o = optionList; o != NULL; o = o->synonym ) {
        o->is_timestamp = 1;
        o->is_simple = 0;
    }
}

static void checkForGMLEscape( char *p )
{
    int is_escape;
    char c1, c2;

    c1 = *p++;
    if( c1 == '\0' || ! isalpha( c1 ) ) {
        return;
    }
    c2 = *p++;
    if( c2 == '\0' || ! isalpha( c2 ) ) {
        return;
    }
    is_escape = 0;
    if( *p == '\0' || ! isalpha( *p ) ) {
        is_escape = 1;
    }
    if( is_escape ) {
        fail( "possible GML escape sequence: &%c%c\n", c1, c2 );
    }
}

static void checkForGMLEscapeSequences( void )
{
    char c;
    char *p;

    p = ibuff;
    for(;;) {
        c = *p++;
        if( c == '\0' ) break;
        if( c == '&' ) {
            checkForGMLEscape( p );
        }
    }
}

static void readInputFile( void )
{
    char *eot;
    char *check;
    tag_id tag;

    for(;;) {
        check = fgets( ibuff, sizeof(ibuff), gfp );
        if( check == NULL ) break;
        ++line;
        checkForGMLEscapeSequences();
        tag = isTag( &eot );
        if( tag == TAG_NULL ) continue;
        eot = skipSpace( eot );
        (*processTag[tag])( eot );
    }
}

static void checkForMissingUsages( void )
{
    OPTION *o;
    int start_lang;
    int end_lang;
    int i;

    for( o = optionList; o != NULL; o = o->next ) {
        if( optFlag.international ) {
            start_lang = LANG_MIN;
            end_lang = LANG_MAX;
        } else {
            start_lang = LANG_English;
            end_lang = start_lang + 1;
        }
        for( i = start_lang; i < end_lang; ++i ) {
            if( o->lang_usage[i] == NULL ) {
                fail( "option '%s' has no %s usage\n", o->name, langName[i] );
            }
        }
    }
}

static void stripUselessOptions( void )
{
    OPTION **h;
    OPTION *o;
    OPTION *n;

    h = &optionList;
    for( o = *h; o != NULL; o = n ) {
        n = o->next;
        if(( o->ntarget & targetMask ) != 0 || ( o->target & targetMask ) == 0 ) {
            o->next = uselessOptionList;
            uselessOptionList = o;
            *h = n;
        } else {
            h = &(o->next);
        }
    }
}

static char *strpcpy( char *d, char *s )
{
    size_t len;

    len = strlen( s );
    strcpy( d, s );
    return d + len;
}

static void makeFieldName( char *n, char *f )
{
    if( *n == '\\' ) {
        n++;
    }
    if( isalpha( *n ) ) {
        *f++ = *n++;
    } else {
        *f++ = '_';
    }
    for(;;) {
        if( *n == '\0' ) break;
        if( isalnum( *n ) ) {
            *f++ = *n;
        } else if( *n == '~' ) {
            f = strpcpy( f, "_tilde" );
        } else if( *n == '+' ) {
            f = strpcpy( f, "_plus" );
        } else if( *n == '!' ) {
            f = strpcpy( f, "_exclamation" );
        } else if( *n == '#' ) {
            f = strpcpy( f, "_sharp" );
        } else if( *n == '\\' ) {
            /* skip */
        }
        ++n;
    }
    *f = '\0';
}

static void startParserH( void )
{
    OPTION *o;
    NAME *e;

    fprintf( ofp, "typedef struct opt_string OPT_STRING;\n" );
    fprintf( ofp, "struct opt_string {\n" );
    fprintf( ofp, "    OPT_STRING *next;\n" );
    fprintf( ofp, "    char data[1];\n" );
    fprintf( ofp, "};\n" );
    fprintf( ofp, "typedef struct opt_number OPT_NUMBER;\n" );
    fprintf( ofp, "struct opt_number {\n" );
    fprintf( ofp, "    OPT_NUMBER *next;\n" );
    fprintf( ofp, "    unsigned number;\n" );
    fprintf( ofp, "};\n" );
    fprintf( ofp, "typedef struct opt_storage OPT_STORAGE;\n" );
    fprintf( ofp, "struct opt_storage {\n" );
    fprintf( ofp, "    unsigned     timestamp;\n" );
    for( o = optionList; o != NULL; o = o->next ) {
        if( o->synonym != NULL ) continue;
        makeFieldName( o->name, tokbuff );
        strcat( tokbuff, "_value" );
        o->value_field_name = strdup( tokbuff );
        if( o->is_number ) {
            if( HAS_OPT_NUMBER( o ) ) {
                fprintf( ofp, "    OPT_NUMBER   *%s;\n", tokbuff );
            } else {
                fprintf( ofp, "    unsigned     %s;\n", tokbuff );
            }
        } else if( o->is_char ) {
            fprintf( ofp, "    int          %s;\n", tokbuff );
        } else if( HAS_OPT_STRING( o ) ) {
            fprintf( ofp, "    OPT_STRING   *%s;\n", tokbuff );
        }
        if( o->is_timestamp ) {
            if( o->enumerate == NULL ) {
                makeFieldName( o->name, tokbuff );
                fprintf( ofp, "    unsigned     %s_timestamp;\n", tokbuff );
            }
        }
    }
    for( e = enumList; e != NULL; e = e->next ) {
        fprintf( ofp, "    unsigned     %s;\n", e->name );
        fprintf( ofp, "    unsigned     %s_timestamp;\n", e->name );
    }
    for( o = optionList; o != NULL; o = o->next ) {
        if( o->synonym != NULL ) continue;
        makeFieldName( o->name, tokbuff );
        o->field_name = strdup( tokbuff );
        if( o->enumerate == NULL ) {
            fprintf( ofp, "    unsigned     %s : 1;\n", tokbuff );
        }
    }
    fprintf( ofp, "};\n" );
}

static void finishParserH( void )
{
    NAME *e;
    unsigned value;

    value = 0;
    for( e = enumeratorList; e != NULL; e= e->next ) {
        ++value;
        fprintf( ofp, "#define %s %u\n", e->name, value );
    }
}

static CODESEQ *newCode( OPTION *o, int c, int sensitive )
{
    CODESEQ *p;

    p = calloc( 1, sizeof( *p ) );
    p->option = o;
    p->c = c;
    if( sensitive ) {
        p->sensitive = 1;
    }
    return( p );
}

static CODESEQ *addOptionCodeSeq( CODESEQ *code, OPTION *o )
{
    int sensitive;
    char *n;
    char c;
    size_t len;
    CODESEQ *head;
    CODESEQ **splice;

    len = strlen( o->name );
    head = code;
    splice = &head;
    n = &(o->name[0]);
    c = '\0';
    while( *n ) {
        c = *n++;
        sensitive = 0;
        if( c == '\\' ) {
            c = *n++;
            sensitive = 1;
        }
        for( code = *splice; code != NULL; code = *splice ) {
            if( code->sensitive == sensitive ) {
                if( sensitive ) {
                    if( code->c == c ) {
                        break;
                    }
                } else {
                    if( tolower( code->c ) == tolower( c )) {
                        break;
                    }
                }
            }
            splice = &(code->sibling);
        }
        if( code == NULL ) {
            code = newCode( o, c, sensitive );
            *splice = code;
        }
        splice = &(code->children);
    }
    if( code == NULL ) {
        code = newCode( o, '\0', 0 );
        *splice = code;
    }
    code->accept = 1;
    code->option = o;
    return( head );
}

static CODESEQ *reorderCode( CODESEQ *c )
{
    CODESEQ *a;
    CODESEQ *h;
    CODESEQ *n;
    CODESEQ **s;

    h = c;
    if( c->sibling != NULL ) {
        a = NULL;
        s = &h;
        // accepting states move to the end
        for( c = h; c != NULL; c = n ) {
            n = c->sibling;
            if( c->accept ) {
                *s = n;
                c->sibling = a;
                a = c;
            } else {
                s = &(c->sibling);
            }
        }
        *s = a;
        s = &(h->sibling);
        // sensitive states move to the front
        for( c = h; c != NULL; c = n ) {
            n = c->sibling;
            if( c->sensitive ) {
                *s = n;
                c->sibling = h;
                h = c;
            } else {
                s = &(c->sibling);
            }
        }
    }
    for( c = h; c != NULL; c = c->sibling ) {
        if( c->children != NULL ) {
            c->children = reorderCode( c->children );
        }
    }
    return( h );
}

static CODESEQ *markChainCode( CODESEQ *h )
{
    CODESEQ *c;

    for( c = h; c != NULL; c = c->sibling ) {
        if( chainOption[ c->c ] & CHAIN_YES ) {
            c->chain = 1;
        }
    }
    return( h );
}

static CODESEQ *genCode( OPTION *o )
{
    CODESEQ *head;

    head = NULL;
    for( ; o != NULL; o = o->next ) {
        head = addOptionCodeSeq( head, o );
    }
    head = reorderCode( head );
    head = markChainCode( head );
    return( head );
}

static int useSwitchStmt( CODESEQ *h )
{
    unsigned count;
    CODESEQ *c;

    count = 0;
    for( c = h; c != NULL; c = c->sibling ) {
        if( c->option->is_prefix ) {
            return( 1 );
        }
        ++count;
    }
    return( count >= USE_SWITCH_THRESHOLD );
}

static void emitSuccessCode( unsigned depth, unsigned control )
{
    if( control & EC_CONTINUE ) {
        emitPrintf( depth, "continue;\n" );
    } else {
        emitPrintf( depth, "return( 0 );\n" );
    }
}

static void emitAcceptCode( CODESEQ *c, unsigned depth, unsigned control )
{
    char *e;
    OPTION *o;
    struct {
        unsigned close_value_if : 1;
    } flag;

    o = c->option;
    while( o->synonym ) {
        o = o->synonym;
    }
    if( o->is_prefix ) {
        emitPrintf( depth, "if( " FN_END "() ) {\n" );
        ++depth;
    }
    flag.close_value_if = 0;
    if( o->is_number ) {
        if( o->default_specified ) {
            emitPrintf( depth, "if( " FN_NUMBER_DEFAULT "( &(data->%s ), %u ) ) {\n", o->value_field_name, o->number_default );
        } else if( o->is_multiple ) {
            emitPrintf( depth, "if( " FN_NUMBER_MULTIPLE "( &(data->%s ) ) ) {\n", o->value_field_name );
        } else {
            emitPrintf( depth, "if( " FN_NUMBER "( &(data->%s) ) ) {\n", o->value_field_name );
        }
        ++depth;
        flag.close_value_if = 1;
    } else if( o->is_char ) {
        if( o->is_optional ) {
            emitPrintf( depth, "if( " FN_CHAR_OPT "( &(data->%s) ) ) {\n", o->value_field_name );
        } else {
            emitPrintf( depth, "if( " FN_CHAR "( &(data->%s) ) ) {\n", o->value_field_name );
        }
        ++depth;
        flag.close_value_if = 1;
    } else if( o->is_id ) {
        if( o->is_optional ) {
            emitPrintf( depth, "if( " FN_ID_OPT "( &(data->%s) ) ) {\n", o->value_field_name );
        } else {
            emitPrintf( depth, "if( " FN_ID "( &(data->%s) ) ) {\n", o->value_field_name );
        }
        ++depth;
        flag.close_value_if = 1;
    } else if( o->is_file ) {
        if( o->is_optional ) {
            emitPrintf( depth, "if( " FN_FILE_OPT "( &(data->%s) ) ) {\n", o->value_field_name );
        } else {
            emitPrintf( depth, "if( " FN_FILE "( &(data->%s) ) ) {\n", o->value_field_name );
        }
        ++depth;
        flag.close_value_if = 1;
    } else if( o->is_dir ) {
        if( o->is_optional ) {
            emitPrintf( depth, "if( " FN_DIR_OPT "( &(data->%s) ) ) {\n", o->value_field_name );
        } else {
            emitPrintf( depth, "if( " FN_DIR "( &(data->%s) ) ) {\n", o->value_field_name );
        }
        ++depth;
        flag.close_value_if = 1;
    } else if( o->is_path ) {
        if( o->is_optional ) {
            emitPrintf( depth, "if( " FN_PATH_OPT "( &(data->%s) ) ) {\n", o->value_field_name );
        } else {
            emitPrintf( depth, "if( " FN_PATH "( &(data->%s) ) ) {\n", o->value_field_name );
        }
        ++depth;
        flag.close_value_if = 1;
    } else if( o->is_special ) {
        emitPrintf( depth, "if( %s( &(data->%s) ) ) {\n", o->special, o->value_field_name );
        ++depth;
        flag.close_value_if = 1;
    }
    if( o->check != NULL ) {
        emitPrintf( depth, "%s( &(data->%s) );\n", o->check, o->value_field_name );
    }
    if( o->enumerate != NULL ) {
        e = addEnumerator( o->enumerate, o->field_name );
        if( o->is_timestamp ) {
            emitPrintf( depth, "data->%s_timestamp = ++(data->timestamp);\n", o->enumerate );
        }
        emitPrintf( depth, "data->%s = %s;\n", o->enumerate, e );
        if( o->is_immediate ) {
            emitPrintf( depth, "%s( data, 1 );\n", o->immediate );
        }
    } else {
        if( o->is_timestamp ) {
            emitPrintf( depth, "data->%s_timestamp = ++(data->timestamp);\n", o->field_name );
        }
        if( o->is_negate ) {
            emitPrintf( depth, "if( %s( '%c' ) ) {\n", FN_RECOG, '-' );
            emitPrintf( depth+1, "data->%s = 0;\n", o->field_name );
            if( o->is_immediate ) {
                emitPrintf( depth+1, "%s( data, 0 );\n", o->immediate );
            }
            emitPrintf( depth, "}else{\n" );
            emitPrintf( depth+1, "data->%s = 1;\n", o->field_name );
            if( o->is_immediate ) {
                emitPrintf( depth+1, "%s( data, 1 );\n", o->immediate );
            }
            emitPrintf( depth, "}\n" );
        } else {
            emitPrintf( depth, "data->%s = 1;\n", o->field_name );
            if( o->is_immediate ) {
                emitPrintf( depth, "%s( data, 1 );\n", o->immediate );
            }
        }
    }
    if( o->is_code ) {
        emitPrintf( depth, "%s;\n", o->code );
    }
    if( flag.close_value_if ) {
        --depth;
        emitPrintf( depth, "}\n" );
    }
    if(( control & EC_CONTINUE ) && o->nochain ) {
        emitSuccessCode( depth, control & ~ EC_CONTINUE );
    } else {
        emitSuccessCode( depth, control );
    }
    if( o->is_prefix ) {
        --depth;
        emitPrintf( depth, "}\n" );
        emitPrintf( depth, "break;\n" );
    }
}

static void emitCode( CODESEQ *h, unsigned depth, unsigned control );

static void emitIfCode( CODESEQ *c, unsigned depth, unsigned control )
{
    if( c->sensitive ) {
        emitPrintf( depth, "if( %s( '%c' ) ) {\n", FN_RECOG, c->c );
    } else {
        emitPrintf( depth, "if( %s( '%c' ) ) {\n", FN_RECOG_LOWER, tolower( c->c ) );
    }
    ++depth;
    if( c->children ) {
        if( c->chain ) {
            emitPrintf( depth, "do {\n" );
            ++depth;
            emitCode( c->children, depth, control | EC_CONTINUE );
            if( c->accept ) {
                emitAcceptCode( c, depth, control & ~ EC_CONTINUE );
            } else {
                emitPrintf( depth, "return( 1 );\n" );
            }
            --depth;
            emitPrintf( depth, "} while( ! " FN_END "() );\n" );
            emitSuccessCode( depth, control );
        } else {
            emitCode( c->children, depth, control );
            if( c->accept ) {
                emitAcceptCode( c, depth, control );
            } else {
                emitPrintf( depth, "return( 1 );\n" );
            }
        }
    } else {
        emitAcceptCode( c, depth, control );
    }
    --depth;
    emitPrintf( depth, "}\n" );
}

static void emitCode( CODESEQ *h, unsigned depth, unsigned control )
{
    int use_switch;
    CODESEQ *c;

    for( c = h; c != NULL; c = c->sibling ) {
        if( c->sensitive ) {
            emitIfCode( c, depth, control );
        } else {
            break;
        }
    }
    if( c == NULL ) {
        return;
    }
    use_switch = useSwitchStmt( c );
    if( use_switch ) {
        emitPrintf( depth, "switch( " FN_GET_LOWER "() ) {\n" );
        ++depth;
    }
    for( ; c != NULL; c = c->sibling ) {
        if( use_switch ) {
            emitPrintf( depth - 1, "case '%c':\n", tolower( c->c ));
            if( c->children ) {
                if( c->chain ) {
                    emitPrintf( depth, "do {\n" );
                    ++depth;
                    emitCode( c->children, depth, control | EC_CONTINUE );
                    if( c->accept ) {
                        emitAcceptCode( c, depth, control & ~ EC_CONTINUE );
                    } else {
                        emitPrintf( depth, "return( 1 );\n" );
                    }
                    --depth;
                    emitPrintf( depth, "} while( ! " FN_END "() );\n" );
                    emitSuccessCode( depth, control );
                } else {
                    emitCode( c->children, depth, control );
                    if( c->accept ) {
                        emitAcceptCode( c, depth, control );
                    } else {
                        emitPrintf( depth, "return( 1 );\n" );
                    }
                }
            } else {
                emitAcceptCode( c, depth, control );
            }
        } else {
            emitIfCode( c, depth, control );
        }
    }
    if( use_switch ) {
        --depth;
        emitPrintf( depth, "}\n" );
        emitPrintf( depth, FN_UNGET "();\n" );
    }
}

static void outputFN_PROCESS( void )
{
    unsigned depth = 0;
    CODESEQ *codeseq;

    emitPrintf( depth, "int " FN_PROCESS "( OPT_STORAGE *data )\n" );
    emitPrintf( depth, "{\n" );
    ++depth;
    codeseq = genCode( optionList );
    emitCode( codeseq, depth, EC_NULL );
    emitPrintf( depth, "return( 1 );\n" );
    --depth;
    emitPrintf( depth, "}\n" );
}

static void outputFN_INIT( void )
{
    OPTION *o;
    NAME *e;
    char *en;
    unsigned depth = 0;

    emitPrintf( depth, "void " FN_INIT "( OPT_STORAGE *data )\n" );
    emitPrintf( depth, "{\n" );
    ++depth;
    emitPrintf( depth, "memset( data, 0, sizeof( *data ) );\n" );
    for( o = optionList; o != NULL; o = o->next ) {
        if( o->synonym != NULL ) continue;
        if( o->is_number ) {
            if( o->default_specified ) {
                emitPrintf( depth, "data->%s = %u;\n", o->value_field_name, o->number_default );
            }
        }
    }
    for( e = enumList; e != NULL; e = e->next ) {
        en = addEnumerator( e->name, "default" );
        emitPrintf( depth, "data->%s = %s;\n", e->name, en );
    }
    --depth;
    emitPrintf( depth, "}\n" );
}

static void outputFN_FINI( void )
{
    OPTION *o;
    unsigned depth = 0;

    emitPrintf( depth, "void " FN_FINI "( OPT_STORAGE *data )\n" );
    emitPrintf( depth, "{\n" );
    ++depth;
    for( o = optionList; o != NULL; o = o->next ) {
        if( o->synonym != NULL ) continue;
        if( HAS_OPT_STRING( o ) ) {
            emitPrintf( depth, FN_CLEAN_STRING "( &(data->%s) );\n", o->value_field_name );
        } else if( HAS_OPT_NUMBER( o ) ) {
            emitPrintf( depth, FN_CLEAN_NUMBER "( &(data->%s) );\n", o->value_field_name );
        }
    }
    --depth;
    emitPrintf( depth, "}\n" );
}

static int usageCmp( const void *v1, const void *v2 )
{
    int     res;

    OPTION *o1 = *(OPTION **) v1;
    OPTION *o2 = *(OPTION **) v2;

    res = tolower( *(o1->field_name) ) - tolower( *(o2->field_name) );
    if( res == 0 ) {
        res = o1->nochain - o2->nochain;
        if( res == 0 ) {
            return( stricmp( o1->field_name, o2->field_name ) );
        }
    }
    if( res < 0 ) {
        return( -1 );
    } else {
        return( 1 );
    }
}

static void catArg( char *arg )
{
    char *p;
    unsigned len;

    len = strlen( tokbuff );
    p = &tokbuff[ len ];
    while( *arg ) {
        if( optFlag.no_equal ) {
            if( *arg != '=' ) {
                *p++ = *arg;
            }
        } else if( optFlag.alternate_equal ) {
            if( *arg != '=' ) {
                *p++ = *arg;
            } else {
                *p++ = alternateEqual;
            }
        } else {
            *p++ = *arg;
        }
        ++arg;
    }
    *p = '\0';
}

static size_t genOptionUsageStart( OPTION *o )
{
    size_t len;
    char *p;
    char *c;

    strcat( tokbuff, "-" );
    c = &tokbuff[1];
    for( p = o->name; *p; ++p ) {
        if( *p == '\\' ) continue;
        *c++ = *p;
    }
    *c = '\0';
    if( o->is_number ) {
        if( o->default_specified ) {
            catArg( "[=<num>]" );
        } else {
            catArg( "=<num>" );
        }
    } else if( o->is_char ) {
        if( o->is_optional ) {
            catArg( "[=<char>]" );
        } else {
            catArg( "=<char>" );
        }
    } else if( o->is_id ) {
        if( o->is_optional ) {
            catArg( "[=<id>]" );
        } else {
            catArg( "=<id>" );
        }
    } else if( o->is_file ) {
        if( o->is_optional ) {
            catArg( "[=<file>]" );
        } else {
            catArg( "=<file>" );
        }
    } else if( o->is_dir ) {
        if( o->is_optional ) {
            catArg( "[=<dir>]" );
        } else {
            catArg( "=<dir>" );
        }
    } else if( o->is_path ) {
        if( o->is_optional ) {
            catArg( "[=<path>]" );
        } else {
            catArg( "=<path>" );
        }
    } else if( o->is_negate ) {
        catArg( "[-]" );
    } else if( o->is_special ) {
        if( o->special_arg_usage != NULL ) {
            // we don't want special processing done
            strcat( tokbuff, o->special_arg_usage );
        }
    }
    if( chainOption[ o->name[0] ] & CHAIN_YES ) {
        if( !o->nochain ) {
            tokbuff[0] = ' ';
            tokbuff[1] = ' ';
        }
    }
    len = strlen( tokbuff );
    return( len );
}

static void fillOutSpaces( unsigned n )
{
    char *p;

    p = &tokbuff[ strlen( tokbuff ) ];
    while( n ) {
        *p++ = ' ';
        --n;
    }
    *p = '\0';
}

static int usageValid( OPTION *o, unsigned language )
{
    if( o->synonym != NULL ) return( 0 );
    if( o->lang_usage[language] == NULL ) return( 0 );
    if( o->lang_usage[language][0] == '\0' ) return( 0 );
    if( o->is_internal && ( targetMask & targetDbgMask ) == 0 ) {
        return( 0 );
    }
    return( 1 );
}

static void emitUsageH( void )
{
    unsigned len;
    char *q;
    char *s;

    len = strlen( tokbuff );
    if( len > maxUsageLen ) {
        maxUsageLen = len;
        strcpy( maxusgbuff, tokbuff );
    }
    if( mfp != NULL ) {
        fprintf( mfp, "%s\n", tokbuff );
    }
    fprintf( ufp, "\"" );
    s = tokbuff;
    while( q = strchr( s, '"' ) ) {
        // replace " with \"
        *q = '\0';
        fprintf( ufp, "%s\\\"", s );
        s = q + 1;
    }
    fprintf( ufp, "%s\",\n", s );
}

static void createChainHeader( OPTION **o, unsigned language )
{
    char c;
    char *usage;

    c = (*o)->name[0];
    hdrbuff[0] = '-';
    hdrbuff[1] = c;
    hdrbuff[2] = '{';
    hdrbuff[3] = '\0';
    for(;;) {
        if( (*o)->name[1] != '\0' ) {
            genOptionUsageStart( *o );
            strcat( hdrbuff, &tokbuff[2] );
            ++o;
            if(( *o == NULL ) || ( (*o)->name[0] != c ) || ( (*o)->nochain ))
                break;
            strcat( hdrbuff, "," );
        } else {
            ++o;
            if(( *o == NULL ) || ( (*o)->name[0] != c ) || ( (*o)->nochain )) {
                break;
            }
        }
    }
    strcat( hdrbuff, "} " );
    usage = chainUsage[ c ][ language ];
    if( usage == NULL || *usage == '\0' ) {
        usage = chainUsage[ c ][ LANG_English ];
    }
    strcat( hdrbuff, usage );
    strcpy( tokbuff, hdrbuff );
}

static void createUsageHeader( unsigned language, void (*process_line)( void ) )
{
    char *s;
    char *d;
    char *title;
    TITLE *t;

    for( t = titleList; t != NULL; t = t->next ) {
        if( t->ntarget & targetMask ) continue;
        if(( t->target & targetMask ) == 0 ) continue;
        title = t->lang_title[language];
        if( title == NULL || *title == '\0' ) {
            title = t->lang_title[LANG_English];
        }
        d = tokbuff;
        for( s = title; *s; ++s ) {
            if( s[0] == '\\' && s[1] == 't' ) {
                ++s;
                *d++ = ' ';
                *d++ = ' ';
                *d++ = ' ';
                *d++ = ' ';
                *d++ = ' ';
                *d++ = ' ';
                *d++ = ' ';
                *d++ = ' ';
            } else if( ! isprint( *s ) ) {
                // skip
            } else {
                *d++ = *s;
            }
        }
        *d = '\0';
        process_line();
    }
}

static void clearChainUsage( void ) {
    unsigned i;

    for( i = 0; i < 256; ++i ) {
        chainOption[i] &= ~CHAIN_USAGE;
    }
}

static void processUsage( unsigned language, void (*process_line)( void ) )
{
    unsigned count;
    unsigned i;
    size_t max;
    size_t len;
    OPTION *o;
    OPTION **t;
    OPTION **c;

    maxUsageLen = 0;
    max = 0;
    count = 0;
    for( o = optionList; o != NULL; o = o->next ) {
        if( ! usageValid( o, language ) ) continue;
        ++count;
        len = genOptionUsageStart( o );
        if( len > max ) {
            max = len;
        }
    }
    ++max;
    t = calloc( count + 1, sizeof( OPTION * ) );
    c = t;
    for( o = optionList; o != NULL; o = o->next ) {
        if( ! usageValid( o, language ) ) continue;
        *c = o;
        ++c;
    }
    *c = NULL;
    qsort( t, count, sizeof( OPTION * ), usageCmp );
    if( optFlag.international ) {
        char *page = pageUsage[ language ];
        if( page == NULL || *page == '\0' ) {
            page = pageUsage[ LANG_English ];
        }
        if( page != NULL && *page != '\0' ) {
            strcpy( tokbuff, page );
            process_line();
        }
    }
    createUsageHeader( language, process_line );
    clearChainUsage();
    for( i = 0; i < count; ++i ) {
        o = t[i];
        if( chainOption[ o->name[0] ] & CHAIN_YES ) {
            if(! ( chainOption[ o->name[0] ] & CHAIN_USAGE )) {
                if( !o->nochain ) {
                    chainOption[ o->name[0] ] |= CHAIN_USAGE;
                    createChainHeader( &t[i], language );
                    process_line();
                }
            }
        }
        tokbuff[0] = '\0';
        len = genOptionUsageStart( o );
        fillOutSpaces( max - len );
        if( chainOption[ o->name[0] ] & CHAIN_YES ) {
            if( !o->nochain ) {
                strcat( tokbuff, "-> " );
            }
        }
        strcat( tokbuff, o->lang_usage[language] );
        process_line();
    }
    if(( maxUsageLen / langMaxChar[language] ) > CONSOLE_WIDTH ) {
        fail( "usage message exceeds %u chars\n%s\n", CONSOLE_WIDTH, maxusgbuff );
    }
}

static void outputUsageH( void )
{
    processUsage( LANG_English, emitUsageH );
}

static void emitUsageB( void )
{
    unsigned len;

    len = strlen( tokbuff ) + 1;
    fwrite( tokbuff, len, 1, bfp );
    if( len > maxUsageLen ) {
        maxUsageLen = len;
        strcpy( maxusgbuff, tokbuff );
    }
}

static void dumpInternational( void ) {
    unsigned lang;
    auto char fname[16];
    auto LocaleUsage usage_header;

    for( lang = LANG_FIRST_INTERNATIONAL; lang < LANG_MAX; ++lang ) {
        sprintf( fname, "usage%02u." LOCALE_DATA_EXT, lang );
        bfp = fopen( fname, "wb" );
        if( bfp == NULL ) {
            fail( "cannot open international file for write\n" );
        }
        memset( &usage_header, 0, sizeof( usage_header ) );
        usage_header.header.code = LS_Usage;
        usage_header.header.signature = LS_Usage_SIG;
        fwrite( &usage_header, sizeof( usage_header ), 1, bfp );
        processUsage( lang, emitUsageB );
        fputc( 0, bfp );
        fclose( bfp );
        bfp = NULL;
    }
}

static void closeFiles( void )
{
    fclose( gfp );
    fclose( pfp );
    fclose( ufp );
}

int main( int argc, char **argv )
{
    int defs_ok = _LANG_DEFS_OK();

    if( ! defs_ok ) {
        fail( "language index mismatch\n" );
    }
    procCmdLine( argc, argv );
    readInputFile();
    checkForMissingUsages();
    stripUselessOptions();
    startParserH();
    outputFN_PROCESS();
    outputFN_INIT();
    outputFN_FINI();
    finishParserH();
    outputUsageH();
    if( optFlag.international ) {
        dumpInternational();
    }
    closeFiles();
    return( EXIT_SUCCESS );
}
