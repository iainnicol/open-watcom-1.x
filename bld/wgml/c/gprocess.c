/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2008 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  WGML input line processing functions
*               not yet functional
*   some logic / ideas adopted from Watcom Script 3.2 IBM S/360 Assembler
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"


/*  split_input
 *  The second part will be processed by the next read
 *
 */

void        split_input( char * buf, char * split_pos )
{
    inp_line    *   wk;
    size_t          len;

    len = strlen( split_pos );          // length of second part
    if( len > 0 ) {
        wk = mem_alloc( len + sizeof( inp_line ) );
        wk->next = NULL;
        strcpy(wk->value, split_pos );  // save second part

        if( input_cbs->hidden_tail != NULL ) {
            input_cbs->hidden_tail->next = wk;
        }
        input_cbs->hidden_tail = wk;

        if( input_cbs->hidden_head == NULL ) {
            input_cbs->hidden_head = wk;
        }
        *split_pos = '\0';              // terminate first part
    }
    return;
}

/*  split_input_var
 *  The second part is constructed from 2 parts
 *  used if a substituted variable starts with CW_sep_char
 */

static  void    split_input_var( char * buf, char * split_pos, char * part2 )
{
    inp_line    *   wk;
    size_t          len;

    len = strlen( split_pos ) + strlen( part2 );// length of second part
    if( len > 0 ) {
        wk = mem_alloc( len + sizeof( inp_line ) );
        wk->next = NULL;

        strcpy(wk->value, part2 );      // second part
        strcat(wk->value, split_pos );  // second part

        if( input_cbs->hidden_tail != NULL ) {
            input_cbs->hidden_tail->next = wk;
        }
        input_cbs->hidden_tail = wk;

        if( input_cbs->hidden_head == NULL ) {
            input_cbs->hidden_head = wk;
        }
    }
    return;
}


/***************************************************************************/
/*  take the contents of the input line in buff2 and try to make the best  */
/*  of it                                                                  */
/*  Processing as specified in wgmlref.pdf chapter 8.1 processing rules    */
/*   incomplete                                                            */
/*                                                                         */
/***************************************************************************/

void        process_line( void )
{
    static const char   ampchar = '&';
    char            *   workbuf;
    char            *   pw;
    char            *   pwend;
    char            *   p2;
    char            *   pchar;
    char            *   varstart;
    int                 varunresolved;
    sub_index           var_ind;
    symvar              symvar_entry;
    symsub          *   symsubval;
    int                 rc;

    //  look for GML tag start character and split line if found

    pchar = strchr( buff2, GML_char );  // look for GML tag start
    if( (pchar != NULL) && (buff2 < pchar) ) {
        split_input( buff2, pchar );    // if found at pos > 1 split
        buff2_lg = strlen( buff2 );     // new length of first part
    }
    // if macro define start ( .dm xxx ... ) supress variable substitution
    // for the sake of single line macro definition
    // .dm xxx /&*1/&*2/&*0/&*/
    if( !strnicmp( buff2 + 1, "dm ", 3 ) ) {
        return;
    }

    workbuf = mem_alloc( buf_size );

    // look for symbolic variable start
    varunresolved = 0;
    do {
        strcpy( workbuf, buff2 );
        pw = workbuf;
        pwend = workbuf + buff2_lg;
        p2 = buff2;
        varstart = NULL;
        pchar = strchr( workbuf, ampchar ); // look for & in buffer
        while( pchar != NULL ) {        // & found
            if( workbuf < pchar ) {
                while( pw < pchar ) {   // copy all data preceding &
                    *p2++ = *pw++;
                }
            }
            varstart = pw;              // remember start of var
            pw++;                       // over &

            pchar = scan_sym( pw, &symvar_entry, &var_ind );// isolate symbolic var

            if( symvar_entry.flags & local_var ) {  // lookup var in dict
                rc = find_symvar( &input_cbs->local_dict, symvar_entry.name,
                                  var_ind, &symsubval );
            } else {
                rc = find_symvar( &global_dict, symvar_entry.name, var_ind,
                                  &symsubval );
            }
            if( rc == 2 ) {             // variable found
                if( symsubval->value[ 0 ] == CW_sep_char ) {// starting with seperator
                    if( *pchar == '.' ) {
                        pchar++;        // skip optional terminating dot
                    }
                    *(varstart - workbuf + buff2) = '\0';
                    split_input_var( buff2, pchar - workbuf + buff2, &symsubval->value[ 1 ] );
                    pw = pwend + 1;     // stop substituion for this record
                    varstart = NULL;
                    break;
                } else {
                    strcpy( p2, symsubval->value ); // copy value
                    p2 += strlen( symsubval->value );
                    if( *pchar == '.' ) {
                        pchar++;        // skip optional terminating dot
                    }
                    pw = pchar;
                }
            } else {
                if( symvar_entry.flags & local_var ) { // local var not found
                                                       // replace by nullstring

                    if( *pchar == '.' ) {
                        pchar++;        // skip optional terminating dot
                    }
                    pw = pchar;
                } else {                // global var not found

                /***********************************************************/
                /*  keep trying for constructs such as                     */
                /*                                                         */
                /* .se prodgml = "Open Watcom GML"                         */
                /* .se name = "GML"                                        */
                /*                                                         */
                /* My name is &prod&name..!                                */
                /*                                                         */
                /*  to become                                              */
                /*                                                         */
                /* My name is Open Watcom GML!                             */
                /*                                                         */
                /* This does not work for local variables, as these are    */
                /* replaced by nullstring if not found                     */
                /* My name is &*prod&*name..!                              */
                /*  will become                                            */
                /* My name is !                                            */
                /***********************************************************/

                    varunresolved++;

                    if( varunresolved > 10 ) {  // max 10 iterations
                        varunresolved = 0;
                    }
                    pw = varstart;
                    if( *pchar == '.' ) {
                        pchar++;        // copy terminating dot, too
                    }
                    while( pw < pchar ) {   // treat var name as text
                        *p2++ = *pw++;
                    }
                }
            }
            *p2 = '\0';
            pchar = strchr( pw, ampchar );  // look for next & in buffer
        }
        while( pw <= pwend) {           // copy remaining input
             *p2++ = *pw++;
        }
    } while( (varunresolved > 0) && (varstart != NULL) );

    buff2_lg = strnlen_s( buff2, buf_size );

    if( GlobalFlags.research && GlobalFlags.firstpass ) {
        printf( "> >%s\n", buff2 ); // show line with possible substitution(s)
    }
    mem_free( workbuf );

    arg_start = buff2;
    arg_stop  = buff2 + buff2_lg;
    return;
}
