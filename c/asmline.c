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


#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "asmglob.h"
#include "asmins.h"
#include "asmdefs.h"

#ifdef _WASM_
#include "directiv.h"
#include "myassert.h"
#include "asmerr.h"
#include "asmalloc.h"
#include "condasm.h"
#include "expand.h"
#endif


extern int              AsmScan( char *);
extern void             AddFlist( char const *filename );

char *curr_src_line = NULL;

char *ScanLine( char *, int );

#ifdef _WASM_

struct input_queue;

typedef struct line_list {
    struct line_list    *next;
    char                *line;
} line_list;

typedef struct file_list {
    struct file_list    *next;
    union {
        FILE            *file;
        struct input_queue  *lines;
    };
    char                *name;  /* name of include file */
    unsigned long       line;   /* current line in parent file */
    char                is_a_file;
    bool                hidden;
} file_list;

/* NOTE: the line queue is now a STACK of line queues
 *       when a macro is being expanded, we push a new line queue on the stack
 *       thus there is 1 queue on the stack for every level of nesting in macros
 */
typedef struct input_queue {
    struct line_list    *head;
    struct line_list    *tail;
    struct input_queue  *next;
} input_queue;

extern void             heap( char * );
extern void             FlushCurrSeg( void );
extern void             AsmError( int );
extern void             OutSelect( bool );

extern char             write_to_file;
extern seg_list         *CurrSeg;
extern File_Info        AsmFiles;
extern uint_8           CheckSeg;
extern dir_node         *CurrProc;
extern int_8            DefineProc;             // TRUE if the definition of procedure
                                                // has not ended
extern unsigned long    PassTotal;
extern symbol_queue     Tables[];               // tables of definitions

uint_32                 BufSize;                // size of CodeBuffer

static input_queue      *line_queue;            // line queue
static file_list        *file_stack=NULL;       // top of included file stack

static char             *IncludePath = NULL;

#if defined(__UNIX__)
#define                 INCLUDE_PATH_DELIM  ":"
#define                 DIR_SEPARATOR       '/'
#define                 DIR_SEP_STRING      "/"
#else
#define                 INCLUDE_PATH_DELIM  ";"
#define                 DIR_SEPARATOR       '\\'
#define                 DIR_SEP_STRING      "\\"
#endif

#else
uint_32 Address;        // program counter
#endif

int     Token_Count;    // number of tokens on line

unsigned char   *CodeBuffer;            // code buffer for generated bytes

#ifdef _WASM_

static bool get_asmline( char *ptr, unsigned max, FILE *fp )
/***********************************************************/
{
    char        quote = 0;
    bool        skip;
    int         c;
    int         got_something;

    /* blow away any comments -- look for ;'s */
    /* note that ;'s are ok in quoted strings */

    skip = FALSE;
    got_something = FALSE;
    for( ;; ) {
        c = getc( fp );
        /* copy the line until we hit a NULL, newline, or ; not in a quote */
        switch( c ) {
        case '\'':
        case '"':
        case '`':
            if( quote == 0 ) {
                quote = c;
            } else if( c == quote ) {
                quote = 0;
            }
            break;
        case '<':
            if( quote == 0 ) {
                quote = '>';
            }
            break;
        case '>':
            if( c == quote ) {
                quote = 0;
            }
            break;
        case ';':
            if( quote != 0 ) {
                break;
            }
            skip = TRUE;
            break;
        case '\n':
            *ptr = '\0';
            // fall through
        case '\0':
            /* we have found the end of the line */
            return( TRUE );
        case EOF:
            *ptr = '\0';
            return( got_something );
        }
        if( !skip ) {
            *ptr++ = c;
            if( --max <= 1 ) skip = TRUE;
            got_something = TRUE;
        }
    }
}

input_queue *PushLineQueue( void )
/********************************/
{
    input_queue *new;

    DebugMsg(( "PUSHLINEQUEUE\n" ));

    new = AsmAlloc( sizeof( input_queue ) );
    new->next = line_queue;
    new->head = new->tail = NULL;
    line_queue = new;
    return( new );
}

bool PopLineQueue()
/*****************/
/* remove a line queue from the top of the stack & throw it away */
{
    input_queue *tmp;

    /* pop the line_queue stack */
    tmp = line_queue;
    if( tmp == NULL ) return( FALSE );
    line_queue = line_queue->next;
    AsmFree( tmp );
    return( TRUE );
}

bool GetQueueMacroHidden( void )
{
    if(( file_stack != NULL ) && !file_stack->is_a_file ) {
        return( file_stack->hidden );
    } else {
        return( FALSE );
    }
}

static line_list *enqueue( void )
/*******************************/
{
    line_list   *new;

    new = AsmAlloc( sizeof( line_list ) );
    new->next = NULL;

    if( line_queue == NULL ) {
        line_queue = AsmAlloc( sizeof( input_queue ) );
        line_queue->next = NULL;
        line_queue->tail = NULL;
        line_queue->head = NULL;
    }

    if( line_queue->tail == NULL ) {
        line_queue->head = new;
        line_queue->tail = new;
    } else {
        /* insert at the tail */
        line_queue->tail->next = new;
        line_queue->tail = new;
    }
    return( new );
}

static file_list *push_flist( char *name, bool is_a_file )
/********************************************************/
{
    file_list   *new;

    new = AsmAlloc( sizeof( file_list ) );
    new->next = file_stack;
    new->line = LineNumber;
    file_stack = new;
    new->is_a_file = is_a_file;
    if( !is_a_file ) {
        dir_node *dir;

        dir = (dir_node *)AsmGetSymbol( name );
        LineNumber = dir->e.macroinfo->start_line;
        new->name = AsmAlloc( strlen( dir->e.macroinfo->filename ) + 1 );
        strcpy( new->name, dir->e.macroinfo->filename );
    } else {
        AddFlist( name );
        new->name = AsmAlloc( strlen( name ) + 1 );
        strcpy( new->name, name );
        LineNumber = 0;
    }
    return( new );
}

char *get_curr_filename( void )
/*****************************/
{
    return( file_stack == NULL ? AsmFiles.fname[ASM] : file_stack->name );
}

void print_include_file_nesting_structure( void )
/***********************************************/
{
    file_list       *tmp;
    unsigned        tab = 1;

    tmp = file_stack;
    if( tmp == NULL ) return;

    for( ; tmp != NULL ; ) {
        if( tmp->next == NULL ) break;
        if( !tmp->hidden ) {
            if( tmp->is_a_file ) {
                AsmNote( NOTE_INCLUDED_BY, tmp->next->name, tmp->line );
            } else {
                AsmNote( NOTE_MACRO_CALLED_FROM, tmp->next->name, tmp->line );
            }
        }
        tmp = tmp->next;
        tab++;
    }

    if( !tmp->hidden ) {
        if( tmp->is_a_file ) {
            AsmNote( NOTE_INCLUDED_BY, AsmFiles.fname[ASM], tmp->line );
        } else {
            AsmNote( NOTE_MACRO_CALLED_FROM, AsmFiles.fname[ASM], tmp->line );
        }
    }

    return;
}

void InputQueueLine( char *line )
/*******************************/
{
    line_list   *new;

    DebugMsg(( "QUEUELINE: %s  ( line %d ) \n", line, LineNumber ));
    new = enqueue();
    new->line = AsmAlloc( strlen( line ) + 1 );
    strcpy( new->line, line );
}

#if 0
static void StripQuotes( char *fname )
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
#endif

static FILE *open_file_in_include_path( char *name, char *fullpath )
/******************************************************************/
{
    char            *inc_path_list;
    char            *next_path;
    char            buffer[MAX_LINE_LEN];
    FILE            *file = NULL;

    while( isspace( *name ) ) name++;

    inc_path_list = AsmTmpAlloc( strlen( IncludePath ) + 1 );
    strcpy( inc_path_list, IncludePath );
    next_path = strtok( inc_path_list, INCLUDE_PATH_DELIM ";");

    while( ( file == NULL ) && ( next_path != NULL ) ) {
        strcpy( buffer, next_path );
//NYI: this is no good for DOS - have to check '/', '\\', and ':'
        if( buffer[ strlen( buffer ) - 1] != DIR_SEPARATOR ) {
            strcat( buffer, DIR_SEP_STRING );
        }
        strcat( buffer, name );

        file = fopen( buffer, "r" );
        if( file ) break;
        next_path = strtok( NULL, INCLUDE_PATH_DELIM ";");
    }
    strcpy( fullpath, buffer );
    return( file );
}

int InputQueueFile( char *path )
/******************************/
{
    FILE        *file;
    file_list   *new;
    char        fullpath[ _MAX_PATH ];
    char        *drive, *dir, *fname, *ext;
    char        buffer[ _MAX_PATH2 ];
    char        *tmp;

    _splitpath2( path, buffer, &drive, &dir, &fname, &ext );
    _makepath( fullpath, drive, dir, fname, ext );
    file = fopen( fullpath, "r" );
    tmp = path;
    if( file == NULL && IncludePath != NULL ) {
        tmp = buffer;
        file = open_file_in_include_path( path, tmp );
    }

    if( file == NULL ) {
        AsmErr( CANNOT_OPEN_INCLUDE_FILE, fullpath );
        return( ERROR );
    } else {
        new = push_flist( tmp, TRUE );
        new->file = file;
        return( NOT_ERROR );
    }
}

static char *input_get( char *string )
/************************************/
{
    line_list   *inputline;
    file_list   *inputfile;

    /* Check the line_queue first; then the file_stack */

    Globals.expand_count = 0;
    while( line_queue != NULL ) {
        if( line_queue->head != NULL ) {
            inputline = line_queue->head;
            strcpy( string, inputline->line );
            line_queue->head = inputline->next;
            if( line_queue->head == NULL ) line_queue->tail = NULL;
            AsmFree( inputline->line );
            AsmFree( inputline );
            return( string );
        }
        PopLineQueue();
    }

    while( file_stack != NULL ) {
        inputfile = file_stack;
        if( inputfile->is_a_file ) {
            if( get_asmline( string, MAX_LINE_LEN, inputfile->file ) ) {
                LineNumber++;
                return( string );
            }
            /* EOF is reached */
            file_stack = inputfile->next;
            fclose( inputfile->file );
            AsmFree( inputfile->name );
            LineNumber = inputfile->line;
            AsmFree( inputfile );
        } else {
            /* this "file" is just a line queue for a macro */
            inputline = inputfile->lines->head;
            LineNumber++;
            if( inputline != NULL ) {
                strcpy( string, inputline->line );
                inputfile->lines->head = inputline->next;
                AsmFree( inputline->line );
                AsmFree( inputline );
                return( string );
            }
            MacroEnd( FALSE );

            file_stack = inputfile->next;
            AsmFree( inputfile->name );
            AsmFree( inputfile->lines );
            LineNumber = inputfile->line;
            AsmFree( inputfile );
        }
    }
    return( NULL );
}

char *ReadTextLine( char *string )
/********************************/
{
    /* get a new line, first checking the line queue & the file stack,
     * then looking in the assembly file itself
     * put it into string and return a pointer to the front
     */

    char *line;

    string[0] = '\0';
    line = input_get( string );
    if( line != NULL ) return( line );
    if( !get_asmline( string, MAX_LINE_LEN, AsmFiles.file[ASM] ) ) {
        return( NULL );
    }
    LineNumber++;
    return( string );
}

static char *join_multiline_cmds( char *line, int len )
/*****************************************************/
{
    char        *ptr;
    int         linelen;

    linelen = strlen( line );

    if( linelen == 0 ) return( line );

    /* if the last non-whitespace character is a comma, join the next line on */

    for( ptr = line + linelen - 1 ; isspace( *ptr ); ptr-- );

    /* ptr now points at the last non-whitespace char */

    if( *ptr != ',' ) {
        return( line );
    }
    ptr++;

    ptr = ScanLine( line + linelen, len - linelen );
    return( line );
}

char *ScanLine( char *string, int len )
/*************************************/
{
    char        *line;
    char        buffer[MAX_LINE_LEN];

    line = ( len < MAX_LINE_LEN ? buffer : string );
    line = ReadTextLine( line );
    if( line != NULL ) {

        prep_line_for_conditional_assembly( line );
        if( line != string ) {          /* comparing the pointers */
            if( strlen( line ) <= len ) {
                strcpy( string, line );
            } else {
                AsmError( ASM_CODE_TOO_LONG );
                return( NULL );
            }
        }
        join_multiline_cmds( string, len );
    }
    return( line );
}

void AsmCodeByte( unsigned char byte )
/************************************/
{
    if( Options.output_data_in_code_records && Globals.data_in_code == TRUE ) {
        OutSelect( FALSE );
    }
    AsmByte( byte );
}

void AsmDataByte( unsigned char byte )
/************************************/
{
    if( Options.output_data_in_code_records &&
        Globals.code_seg &&
        Globals.data_in_code == FALSE ) {
        OutSelect( TRUE );
    }
    AsmByte( byte );
}
#endif

#ifdef _WASM_
bool CheckHaveSeg()
{
    if( CurrSeg != NULL ) return( TRUE );
    if( CheckSeg ) {
        AsmError( DATA_EMITTED_WITH_NO_SEGMENT );
        write_to_file = FALSE;
        CheckSeg = FALSE;
    }
    return( FALSE );
}
#endif

void AsmByte( unsigned char byte )
/********************************/
/* Write a byte to the object file */
{
#ifdef _WASM_

    if( CurrSeg != NULL ) {
//      (CurrSeg->seg->e.seginfo->segrec->d.segdef.seg_length)++;
        (CurrSeg->seg->e.seginfo->current_loc)++;
        if( CurrSeg->seg->e.seginfo->current_loc >=
            CurrSeg->seg->e.seginfo->segrec->d.segdef.seg_length ) {
            CurrSeg->seg->e.seginfo->segrec->d.segdef.seg_length = CurrSeg->seg->e.seginfo->current_loc;
        }
    }
    if( CheckHaveSeg() ) {
        if( Parse_Pass != PASS_1 && write_to_file ) {
            CodeBuffer[BufSize] = byte;
            ++BufSize;
            if( BufSize >= MAX_LEDATA_THRESHOLD ) {
                FlushCurrSeg();
            }
        }
    }

    PassTotal++;

#else
    CodeBuffer[Address] = byte;
    ++Address;
#endif
}

#ifdef _WASM_
#ifdef DEBUG_OUT
static void output( void )
/************************/
/* For debugging use only; print out a simplied version of the source line
   after it is parsed and the expression is evaluated */
{
    if( Options.debug ) {
        int             i;

        DebugMsg(("Line: %d ", LineNumber ));
        DebugMsg(("Output :"));
        for( i = 0; i < Token_Count; i++ ) {
            switch( AsmBuffer[i]->token ) {
                case T_NUM:
                    DebugMsg(( " %d ", AsmBuffer[i]->value ));
                    break;
                case T_STRING:
                    DebugMsg(( " '%s' ", AsmBuffer[i]->string_ptr));
                    break;
                case T_OP_SQ_BRACKET:
                    DebugMsg(( " %s ", "[" ));
                    break;
                case T_CL_SQ_BRACKET:
                    DebugMsg(( " %s ", "]" ));
                    break;
                case T_COLON:
                    DebugMsg(( " %s ", ":" ));
                    break;
                case T_RES_ID:
                    switch( AsmBuffer[i]->value ) {
                    case T_PTR:
                        DebugMsg(( " %s ", "Ptr" ));
                        break;
                    case T_NEAR:
                        DebugMsg(( " %s ", "Near" ));
                        break;
                    case T_FAR:
                        DebugMsg(( " %s ", "Far" ));
                        break;
                    case T_PROC:
                        DebugMsg(( " %s ", "Proc" ));
                        break;
                    case T_BYTE:
                    case T_SBYTE:
                        DebugMsg(( " %s ", "Byte" ));
                        break;
                    case T_WORD:
                    case T_SWORD:
                        DebugMsg(( " %s ", "Word" ));
                        break;
                    case T_DWORD:
                    case T_SDWORD:
                        DebugMsg(( " %s ", "DWord" ));
                        break;
                    case T_PWORD:
                    case T_FWORD:
                        DebugMsg(( " %s ", "FWord" ));
                        break;
                    case T_QWORD:
                        DebugMsg(( " %s ", "QWord" ));
                        break;
                    case T_TBYTE:
                        DebugMsg(( " %s ", "TByte" ));
                        break;
                    case T_ABS:
                        DebugMsg(( " %s ", "Abs" ));
                        break;
                    default:
                        DebugMsg((" %s ", AsmBuffer[i]->string_ptr ));
                        break;
                    }
                    break;
                default:
                    DebugMsg((" %s ", AsmBuffer[i]->string_ptr ));
                    break;
            }
        }
        DebugMsg(("\n"));
    } /* if Options.debug */
    return;
}
#endif
#endif

void AsmLine( char *string )
/**************************/
{
    #ifdef _WASM_
        int             count;
    #endif

    curr_src_line = string;
    // Token_Count is the number of tokens scanned
    Token_Count = AsmScan( string );
#ifdef _WASM_
    Token_Count = ExpandMacro( Token_Count );

    if( ExpandTheWorld( 1, TRUE, TRUE ) == ERROR ) {
        write_to_file = FALSE;
        return;
    }

    if( CurrProc != NULL && !DefineProc ) {
        for( count = 0; count < Token_Count; count++ ) {
            switch( ExpandProcString( count ) ) {
            case ERROR:
                write_to_file = FALSE; /* fall through */
            case STRING_EXPANDED:
                return;
            }
        }
    }

    if( Token_Count > 0 ) {
        if( AsmParse() == ERROR ) {
            write_to_file = FALSE;
        }
    } else if( Token_Count < 0 ) {
        // syntax error
        write_to_file = FALSE;
    }
    #ifdef DEBUG_OUT
        output();               // for debuggin only
    #endif

#else

    if( Token_Count > 0 ) {
        AsmParse();
    }

#endif
}

#ifdef _WASM_
void AddStringToIncludePath( char *string )
/*****************************************/
{
    char *tmp;

    while( isspace( *string ) ) string++;
    if( IncludePath == NULL ) {
        IncludePath = AsmAlloc( strlen( string ) + 1 );
        strcpy( IncludePath, string );
    } else {
        tmp = IncludePath;
        IncludePath = AsmAlloc( strlen( tmp ) + strlen( INCLUDE_PATH_DELIM ) +
                                strlen( string ) + 1 );
        strcpy( IncludePath, tmp );
        strcat( IncludePath, INCLUDE_PATH_DELIM );
        strcat( IncludePath, string );
        AsmFree( tmp );
    }
    return;
}

void FreeIncludePath( void )
/**************************/
{
    AsmFree( IncludePath );
}

void PushMacro( char *name, bool hidden )
/***************************************/
{
    file_list *new;

    DebugMsg(( "PUSH_MACRO\n" ));
    new = push_flist( name, FALSE );
    new->lines = line_queue;
    new->hidden = hidden;
    line_queue = line_queue->next;
}
#endif
