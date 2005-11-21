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

// different classes of tokens recognized 
typedef enum {
    TO_OPR,             // operator 
    TO_NAM,             // name
    TO_LIT,             // literal      
    TO_LGL,             // logical  
    TO_INT,             // numeric integer constant       
    TO_REA,             // numeric real constant
    TO_DBL,             // numeric double real constant
    TO_EXT,             // numeric extended real constant
    TO_OCT,             // octal constant   
    TO_HEX,             // hex constant 
    TO_FMT              // Format statement
} token_class;


// token type specification
typedef enum {
    TK_EOL      =   0x01,   // end of line
    TK_LAST     =   0x02,   // last token in statement  
    TK_LENSPEC  =   0x04,   // length specifier
    TK_INCLUDE  =   0x08    // include directive
} tokenType;


// structure of raw element (token)  
typedef struct token_s {
    char        *start; // start of lexem
    char        *stop;  // end of lexem
    int         line;   // continuation line counter
    token_class class;  // class of token
    tokenType   flags;  // token type
    byte        log;    // flag for logical operators
    byte        col;    // column counter
} token_t;



