/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2010 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  WGML tags :LQ :eLQ processing
*
****************************************************************************/
#include    "wgml.h"
#include    "gvars.h"

/********************************************************************************************/
/* Format: :LQ.<basic document elements>                                                    */
/*                                                                                          */
/* This tag starts a long quotation. WATCOM Script/GML does not surround a long             */
/* quotation with quotes. The long quote is made distinct from the rest of the text by the  */
/* way in which it is formatted. The :elq tag terminates a long quotation.                  */
/*                                                                                          */
/********************************************************************************************/

void gml_lq( const gmltag * entry )
{
    char        *   p;

    start_doc_sect();                   // if not already done
    scr_process_break();

    if( is_ip_tag( nest_cb->c_tag ) ) {                 // inline phrase not closed
        g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // end tag expected
    }

    init_nest_cb();
    nest_cb->p_stack = copy_to_nest_stack();

    nest_cb->c_tag = t_LQ;

    nest_cb->left_indent = conv_hor_unit( &layout_work.lq.left_indent, g_curr_font )
                            + nest_cb->prev->left_indent + nest_cb->prev->align;
    nest_cb->right_indent = -1 * conv_hor_unit( &layout_work.lq.right_indent, g_curr_font )
                            + nest_cb->prev->right_indent;

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    nest_cb->font = g_curr_font;
    g_curr_font = layout_work.lq.font;
    spacing = (int8_t) layout_work.lq.spacing;

    set_skip_vars( &layout_work.lq.pre_skip, NULL, NULL, 1, g_curr_font );

    t_page.cur_left = nest_cb->lm + nest_cb->left_indent;
    t_page.max_width = nest_cb->rm + nest_cb->right_indent;

    t_page.cur_width = t_page.cur_left;
    ProcFlags.keep_left_margin = true;  // keep special LQ indent

    t_page.cur_width = t_page.cur_left;

    if( t_page.cur_width > t_page.cur_left ) {
        t_page.cur_left = t_page.cur_width;
    }
    t_page.cur_width = t_page.cur_left;
    ju_x_start = t_page.cur_width;

    p = scan_start;
    while( *p == ' ' ) p++;                 // skip spaces
    if( *p == '.' ) p++;                    // skip tag end
    if( *p ) {
        process_text( p, g_curr_font );
    }

    scan_start = scan_stop + 1;
}


/****************************************************************************************/
/* Format: :eLQ.                                                                        */
/*                                                                                      */
/* This tag signals the end of a long quote. A corresponding :lq tag must be previously */
/* specified for each :elq tag.                                                         */
/*                                                                                      */
/****************************************************************************************/

void gml_elq( const gmltag * entry )
{
    char    *   p;
    tag_cb  *   wk;

    scr_process_break();

    if( nest_cb->c_tag != t_LQ ) {                          // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t_LQ + 1] );             // no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    }

    set_skip_vars( NULL, NULL, &layout_work.lq.post_skip, 1, g_curr_font );

    t_page.cur_left = nest_cb->lm;
    t_page.max_width = nest_cb->rm;

    wk = nest_cb;
    nest_cb = nest_cb->prev;
    add_tag_cb_to_pool( wk );
    g_curr_font = nest_cb->font;

    t_page.cur_width = t_page.cur_left;
    scan_err = false;
    p = scan_start;
    if( *p == '.' ) p++;            // over '.'
    if( *p ) {
        ProcFlags.skips_valid = false;
        process_text( p, g_curr_font);  // if text follows
    }

    scan_start = scan_stop + 1;
}

