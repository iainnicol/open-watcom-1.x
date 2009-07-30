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
* Description: WGML implement :TITLE  tag for LAYOUT processing
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <errno.h>
#include <stdarg.h>

#include "wgml.h"
#include "gvars.h"

/***************************************************************************/
/*   :TITLE    attributes                                                  */
/***************************************************************************/
const   lay_att     title_att[7] =
    { e_left_adjust, e_right_adjust, e_page_position, e_font, e_pre_top_skip,
      e_skip, e_dummy_zero };


/***************************************************************************/
/*  lay_title                                                              */
/***************************************************************************/

void    lay_title( const gmltag * entry )
{
    char            *   p;
    condcode            cc;
    int                 k;
    lay_att             curr;
    att_args            l_args;
    bool                cvterr;

    p = scan_start;
    cvterr = false;

    if( !GlobalFlags.firstpass ) {
        scan_start = scan_stop + 1;
        eat_lay_sub_tag();
        return;                         // process during first pass only
    }
    if( ProcFlags.lay_xxx != el_title ) {
        ProcFlags.lay_xxx = el_title;
        out_msg( ":%s nearly dummy\n", entry->tagname );
    }
    cc = get_lay_sub_and_value( &l_args );  // get att with value
    while( cc == pos ) {
        cvterr = true;
        for( k = 0, curr = title_att[k]; curr > 0; k++, curr = title_att[k] ) {

            if( !strnicmp( att_names[curr], l_args.start[0], l_args.len[0] ) ) {
                p = l_args.start[1];

                switch( curr ) {
                case   e_left_adjust:
                    cvterr = i_space_unit( p, curr,
                                           &layout_work.title.left_adjust );
                    break;
                case   e_right_adjust:
                    cvterr = i_space_unit( p, curr,
                                           &layout_work.title.right_adjust );
                    break;
                case   e_page_position:
                    cvterr = i_page_position( p, curr,
                                         &layout_work.title.page_position );
                    break;
                case   e_font:
                    cvterr = i_int8( p, curr, &layout_work.title.font );
                    break;
                case   e_pre_top_skip:
                    cvterr = i_space_unit( p, curr,
                                           &layout_work.title.pre_top_skip );
                    break;
                case   e_skip:
                    cvterr = i_space_unit( p, curr,
                                           &layout_work.title.skip );
                    break;
                default:
                    out_msg( "WGML logic error.\n");
                    cvterr = true;
                    break;
                }
                if( cvterr ) {          // there was an error
                    err_count++;
                    g_err( err_att_val_inv );
                    file_mac_info();
                }
                break;                  // break out of for loop
            }
        }
        cc = get_lay_sub_and_value( &l_args );  // get att with value
    }
    scan_start = scan_stop + 1;
    return;
}

