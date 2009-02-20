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
* Description:  WGML implement multi letter function &'d2c( )
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
/*  script string function &'d2c(                                          */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/* &'d2c(number<,n>):  To  convert a  decimal 'number'  to its  character  */
/*    representation of length 'n'.  The 'number' can be negative only if  */
/*    the length 'n' is specified.                                         */
/*      "&'d2c(129)" ==> "a"          The examples are in EBCDIC           */
/*      "&'d2c(129,1)" ==> "a"                                             */
/*      "&'d2c(129,2)" ==> " a"                                            */
/*      "&'d2c(-127,1)" ==> "a"                                            */
/*      "&'d2c(-127,2)" ==> "�a"                                           */
/*      "&'d2c(12,0)" ==> ""                                               */
/*                                                                         */
/*  ! The optional second parm is NOT implemented                          */
/*                                                                         */
/***************************************************************************/


condcode    scr_d2c( parm parms[ MAX_FUN_PARMS ], size_t parmcount, char * * result )
{
    char            *   pval;
    char            *   pend;
    condcode            cc;
    int                 n;
    int                 len;
    getnum_block        gn;

    if( parmcount != 1 ) {
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

    n   = 0;
    gn.ignore_blanks = false;

    if( parms[ 1 ].e >= parms[ 1 ].a ) {
        gn.argstart = pval;
        gn.argstop  = pend;
        cc = getnum( &gn );
        if( (cc != pos) ) {
            if( input_cbs->fmflags & II_macro ) {
                out_msg( "ERR_FUNCTION parm 1 (number) invalid\n"
                         "\t\t\tLine %d of macro '%s'\n",
                         input_cbs->s.m->lineno,
                         input_cbs->s.m->mac->name );
            } else {
                out_msg( "ERR_FUNCTION parm 1 (number) invalid\n"
                         "\t\t\tLine %d of file '%s'\n",
                         input_cbs->s.f->lineno,
                         input_cbs->s.f->filename );
            }
            err_count++;
            show_include_stack();
            return( cc );
        }
        n = gn.result;
    }

    **result = gn.result;
    *result += 1;
    **result = '\0';

    return( pos );
}

