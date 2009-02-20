/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2009 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  WGML implement multi letter function &'left( )
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"

/***************************************************************************/
/*  script string function &'left(                                         */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* &'left(string,length<,pad>):   To  generate  a   character  string  of  */
/*    'length' characters  with 'string' in  its start.   If  'length' is  */
/*    longer than 'string' then 'pad' the result.                          */
/*      &'left('ABC D',8) ==> "ABC D   "                                   */
/*      &'left('ABC D',8,'.') ==> "ABC D..."                               */
/*      &'left('ABC  DEF',7) ==> "ABC  DE"                                 */
/*                                                                         */
/* ! optional parm PAD is NOT implemented                                  */
/*                                                                         */
/***************************************************************************/

condcode    scr_left( parm parms[ MAX_FUN_PARMS ], size_t parmcount, char * * result )
{
    char            *   pval;
    char            *   pend;
    condcode            cc;
    int                 k;
    int                 len;
    getnum_block        gn;

    if( parmcount != 2 ) {
        cc = neg;
        return( cc );
    }

    pval = parms[ 0 ].a;
    pend = parms[ 0 ].e;

    unquote_if_quoted( &pval, &pend );

    len = pend - pval + 1;              // default length

    if( len <= 0 ) {                    // null string nothing to do
        **result = '\0';
        return( pos );
    }

    if( parms[ 1 ].e >= parms[ 1 ].a ) {// length specified
        gn.argstart = parms[ 1 ].a;
        gn.argstop  = parms[ 1 ].e;
        cc = getnum( &gn );
        if( cc != pos ) {
            if( input_cbs->fmflags & II_macro ) {
                out_msg( "ERR_FUNCTION parm 2 (length) invalid\n"
                         "\t\t\tLine %d of macro '%s'\n",
                         input_cbs->s.m->lineno,
                         input_cbs->s.m->mac->name );
            } else {
                out_msg( "ERR_FUNCTION parm 2 (length) invalid\n"
                         "\t\t\tLine %d of file '%s'\n",
                         input_cbs->s.f->lineno,
                         input_cbs->s.f->filename );
            }
            err_count++;
            show_include_stack();
            return( cc );
        }
        len = gn.result;
    }

    k = 0;
    while( (k < len) && (pval <= pend) ) {  // copy from start
        **result = *pval++;
        *result += 1;
        k++;
    }

    while( k < len  ) {                 // pad to length
        **result = ' ';
        *result += 1;
        k++;
    }

    **result = '\0';

    return( pos );
}

