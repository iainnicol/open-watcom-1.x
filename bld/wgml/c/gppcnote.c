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
* Description:  WGML tags :P, :PC and :NOTE processing
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include    "wgml.h"
#include    "gvars.h"

/***************************************************************************/
/*  :P.perhaps paragraph elements                                          */
/***************************************************************************/
void    proc_p_pc( p_lay_tag * p_pc )
{
    char        *   p;

    scan_err = false;
    p = scan_start;

    ProcFlags.keep_left_margin = true;  //    special Note indent
    start_doc_sect();                   // if not already done

    scr_process_break();
    if( nest_cb->c_tag == t_NONE ) {
        g_cur_left = g_page_left + g_indent;// left start    TBD
    } else {
        g_cur_left = g_cur_left;
    }
                                        // possibly indent first line
    g_cur_h_start = g_cur_left + conv_hor_unit( &(p_pc->line_indent) );

    g_cur_threshold = layout_work.widow.threshold; // standard threshold

    if( *p == '.' ) p++;                // over '.'

    set_skip_vars( &(p_pc->pre_skip), NULL, &(p_pc->post_skip), spacing,
                    g_curr_font_num );

    post_space = 0;

    process_text( p, g_curr_font_num );

    scan_start = scan_stop + 1;
    return;
}

/***************************************************************************/
/*  :P.perhaps paragraph elements                                          */
/***************************************************************************/
extern  void    gml_p( const gmltag * entry )
{
    proc_p_pc( &layout_work.p );
    ProcFlags.empty_doc_el = true;  // for next break, not this tag's break
}

/***************************************************************************/
/*  :PC.perhaps paragraph elements                                         */
/***************************************************************************/
extern  void    gml_pc( const gmltag * entry )
{
    proc_p_pc( &layout_work.pc );
}

/***************************************************************************/
/*  :NOTE.perhaps paragraph elements                                       */
/***************************************************************************/
extern  void    gml_note( const gmltag * entry )
{
    char        *   p;
    int8_t          font_save;

    scan_err = false;
    p = scan_start;

    start_doc_sect();                   // if not already done

    scr_process_break();

    font_save = g_curr_font_num;
    g_curr_font_num = layout_work.note.font;
    set_skip_vars( &layout_work.note.pre_skip, NULL, &layout_work.note.post_skip,
                    spacing, g_curr_font_num );
    post_space = 0;

    if( nest_cb->c_tag == t_NONE ) {
        g_cur_left = g_page_left + conv_hor_unit( &layout_work.note.left_indent );
    } else {
        g_cur_left += conv_hor_unit( &layout_work.note.left_indent );
    }
    g_cur_h_start = g_cur_left;
    ProcFlags.keep_left_margin = true;  // keep special Note indent

    start_line_with_string( layout_work.note.string, layout_work.note.font, false );

    if( (t_line != NULL)  && (t_line->last != NULL) ) {
        g_cur_left += t_line->last->width + post_space;
    }
    post_space = 0;
    g_cur_h_start = g_cur_left;
    ju_x_start = g_cur_h_start;

    spacing = layout_work.note.spacing;
    g_curr_font_num = layout_work.defaults.font;

    set_skip_vars( NULL, NULL, NULL,
                    spacing, g_curr_font_num );
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial space
    if( *p ) {
        process_text( p, g_curr_font_num ); // if text follows
    }
    g_curr_font_num = font_save;
    scan_start = scan_stop + 1;
    return;
}

