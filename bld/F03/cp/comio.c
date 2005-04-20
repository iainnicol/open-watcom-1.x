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
// COMIO     : compile time source input, listing output
//

#include "ftnstd.h"
#include "progsw.h"
#include "extnsw.h"
#include "errcod.h"
#include "cpopt.h"
#include "global.h"
#include "intcnv.h"
#include "extnsw.h"
#include "csetinfo.h"
#include "ferror.h"
#include "inout.h"
#include "comio.h"
#include "scan.h"

#include <string.h>
#include <stdlib.h>

extern  char            *SkipBlanks(char *);
extern  void            SrcOption(void);
extern  bool            CompileDebugStmts(void);

extern  character_set   CharSetInfo;

/*
* Process comments in source file
* detect labels
* and position cursor to first character in statement field
*/

void    ComRead(void)
{
    char        *cursor;
    uint        column;
    char        ch;
    byte        chtype;
    uint        stmt_type;
    unsigned_32 stmt_no;
    bool        stno_found;
    byte        cont_type;
    bool        done_scan;
    ftnoption   save_options;

    // Comment processor sets "Options" so that
    //          c$warn
    //          c$notime=5
    // is diagnosed if /nowarn is specified
    // "Options" must be saved so that we don't get an unreferenced warning
    // message in the following case.
    //          c$noreference
    //                  integer*4 sam
    //          c$reference
    //                  end
    save_options = Options;
    stmt_type    = STMT_COMMENT;
    cont_type    = 0;
    cursor       = 0;
    done_scan    = FALSE;
    
    // read record by record from source file
    for(;;) {
        // read record from file
        ReadSrc();
        // EOF or file conclusion pending
        if( ProgSw & PS_SOURCE_EOF ) break;
        if( CurrFile->flags & CONC_PENDING ) break;
        
        // column starts off before current column
        column = FIRST_COL - 1;
        // init cursor position for src
        cursor = SrcBuff;
        ch     = *cursor;
        
        // not a comment indicator in first column
        if( ( ch != 'C' ) && ( ch != 'c' ) && ( ch != '*' ) ) {
            if( ProgSw & PS_SKIP_SOURCE ) continue;
            // a debug line
            if( ( ch == 'D' ) || ( ch == 'd' ) ) {
                if( !(ExtnSw & XS_D_IN_COLUMN_1) ) {
                    Extension( CC_D_IN_COLUMN_1 );
                    ExtnSw |= XS_D_IN_COLUMN_1;
                }
                // Debug not enabled. Skip.
                if( !CompileDebugStmts() ) continue;
                // Debug is enabled. replace 'D' by ' ' and thus make statement visible 
                ch = ' ';
            }
            // not a comment (but it might be a blank line)
            // try for a statement number
            stmt_no    = 0;
            stno_found = FALSE;
            // scan through src record/line
            for(;;) {
                // get character class for cursor target
                chtype = CharSetInfo.character_set[ ch ];
                
                // It is EOL. Exit 
                if( chtype == C_EL ) break;
                
                // It is End of line comment ('!')
                if( ( chtype == C_CM ) && ( column != CONT_COL - 1 ) ) {
                    // mark as WATCOM extension
                    if( ( ExtnSw & XS_EOL_COMMENT ) == 0 ) {
                        Extension( CC_EOL_COMMENT );
                        ExtnSw |= XS_EOL_COMMENT;
                    }
                    // exit loop (skip rest of line)
                    break;
                }
                
                // it is a blank
                if( chtype == C_SP ) {
                    ++column;
                // it is a tabulator    
                } else if( chtype == C_TC ) {
                    column += 8 - column % 8;
                // it is a double byte blank     
                } else if( CharSetInfo.is_double_byte_blank( cursor ) ) {
                    cursor++;
                    column += 2;
                // it is alphanumeric
                } else {
                     ++column;
                     // a digit not in the control column
                    if( ( chtype == C_DI ) && ( column != CONT_COL ) ) {
                        stmt_type = STMT_START;
                        // past label field and outside of control column
                        if( column > CONT_COL ) {
                            done_scan = TRUE;
                            break;
                        }
                        // it is a label number
                        // calculate label value
                        stmt_no    = 10 * stmt_no + ch - '0';
                        stno_found = TRUE;
                    // an alphanumeric character    
                    } else {
                        stmt_type = STMT_START;
                        // outside of continuation column
                        if( column != CONT_COL ) {
                            done_scan = TRUE;
                            break;
                        }
                        // its in the continuation column
                        // a genuine continuation line
                        if( ch != '0' ) {
                            // save the type for later diagnosis
                            cont_type = chtype;
                            stmt_type = STMT_CONT;
                            // position to column 7
                            ++column;
                            ++cursor;
                            done_scan = TRUE;
                            break;
                        }
                    }
                }
                // get next character
                ++cursor;
                ch = *cursor;
                // past last valid column
                if( column >= LastColumn ) {
                    // Consider:                             Column 73
                    //     1                                     |
                    //     0123                                  2001
                    // terminate line and quit
                    *cursor = NULLCHAR;
                    break;
                }
            }
            // found interesting content
            if( done_scan ) break;
            
            // continue reading if it was comment line
            if( stmt_type != STMT_COMMENT ) break;
        }
        
        // process the comment. It could contain a compile option
        Comment();
        // quit if the comment simulates EOF 
        if( ProgSw & PS_SOURCE_EOF ) break;
        // quit if c$include encountered
        if( CurrFile->flags & INC_PENDING ) break;
    }
    
    // save result globally
    // Cursor to first 'interesting' character
    Cursor      = cursor;
    Column      = column - 1;
    // statement label if there was one
    NextStmtNo  = stmt_no;
    StmtNoFound = stno_found;
    // class of statement found
    StmtType    = stmt_type;
    ContType    = cont_type;
    // 
    Options     = save_options;
}


/*
* Read comments in free soure format
*
*/
void    ComReadFree(void)
{

char            *cursor;            // reference to current character in source buffer
char            ch;                 // current character under investigation
charClassType   chtype;             // the class of the tested character
uint            column = 0;         // current column in src line
bool            doneScan = FALSE;   // Indicator scan for non comment finished


    // read record by record from source file
    for( ;; ) {
        // read record from file
        ReadSrc(); // incorrect ::TODO: ??
        // EOF or file conclusion pending
        if( ProgSw & PS_SOURCE_EOF ) break;
        if( CurrFile->flags & CONC_PENDING ) break;
        
        // init cursor position for src
        cursor = SrcBuff;
        ch     = *cursor; 
        
        // scan through src record/line
        for( ;; ) {
            // get character class under cursor 
            chtype = CharSetInfo.character_set[ ch ];
            
            // not a comment line or comment 
            if( C_CM != chtype ){
                if( ProgSw & PS_SKIP_SOURCE ) break;
                               
                if( C_SP == chtype ) { // it is a blank
                    column++;    
                } else if ( C_EL == chtype ) { // it is EOL
                    break;
                } else if ( C_TC == chtype ) { //  it is a TAB : TODO mark as extension
                    column += 8 - column % 8;  // TODO: rplace 8 by tablength variable
                } else if ( CharSetInfo.is_double_byte_blank( cursor) ) {
                    column +=2;
                    cursor++;
                } else {
                    column++;
                    doneScan = TRUE;
                    break;
                }
                
                cursor++; // next character              
                
            // it is a comment    
            } else {
                // process for possible options
                Comment();
                // quit if comment simulates EOF (TODO:When does this happen ?)
                if ( ProgSw & PS_SOURCE_EOF ) {
                    doneScan = TRUE;
                    break;
                }
                // quit if $include encountered
                if ( CurrFile->flags & INC_PENDING ) {
                    doneScan = TRUE;
                    break;
                }
            }        
        } // for
        if ( doneScan ) break;
    } // for

    // save data globaly
    Cursor = cursor;
    Column = column;
}


void    ProcInclude() {
//=====================

    int old_srcrecnum;

    ComPrint();
    if( strlen( SrcBuff ) > LastColumn ) {
        SrcBuff[ LastColumn ] = NULLCHAR;
    }
    old_srcrecnum = SrcRecNum;
    SrcRecNum = CurrFile->rec; // in case we get an error processing INCLUDE
    Include( SkipBlanks( &SrcBuff[ 10 ] ) );
    SrcRecNum = old_srcrecnum;
}


/*
* Print a source line to listing file  with line information
*/
void    LinePrint()
{
    char        buffer[8]; // Linenumber buffer
    
    // increment internal statement number ISN 
    ISNNumber++;
    
    // skip if nothing to generate
    if( ( ProgSw & PS_DONT_GENERATE ) == 0 ) return;
    
    //format line number and print into listing file 
    FmtInteger( buffer, CurrFile->rec, 7 );
    PrintLineInfo( buffer );
}


/*
* print a source comment line with line information
*/
void    ComPrint() {

    char    buffer[8]; // buffer for line number

    // skip if nothing to generate
    if( ( ProgSw & PS_DONT_GENERATE ) == 0 ) return;
    
    // create number string for line number
    FmtInteger( buffer, CurrFile->rec, 7 );
    
    // print comment line with line number prepended
    PrintLineInfo( buffer );
}


/*
*
*/
static  void    PrintLineInfo( char *buffer )
{
    // print buffer (=line number) contents to listing file 
    PrtLst( buffer );
    
    // not nested in file
    if( CurrFile->link == NULL ) {
        // insert 
        PrtLst( " " );
    } else {
        // nested in include file
        // insert
        PrtLst( "+" );
    }
    // print source line with new line
    PrtLstNL( SrcBuff );
}


/*
*  Format integer to field of width right-adjusted in buffer
*/
void    FmtInteger( char *buff, int num, int width )
{
    char    nbuf[MAX_INT_SIZE]; // buffer for number string

    // translate integer into string
    ltoa( num, nbuf, 10 );
    // and put right adjusted into buffer
    memset( buff, ' ', width );
    strcpy( &buff[ width - strlen( nbuf ) ], nbuf );
}


/*
* Process a comment for possible compiler directives.
*/ 
static  void    Comment(void)
{
    int old_srcrecnum;
    
    // check for compiler source option indicator
    if( ( SrcBuff[ 0 ] != NULLCHAR ) && ( SrcBuff[ 1 ] == '$' ) ) {
        // save record/line number
        old_srcrecnum = SrcRecNum;
        SrcRecNum = CurrFile->rec; // in case we get an error processing comment
        
        // process src option
        SrcOption();
        
        // restore record/line number
        SrcRecNum = old_srcrecnum;
    } else {
        // print comment line to listing file 
        ComPrint();
    }
}
