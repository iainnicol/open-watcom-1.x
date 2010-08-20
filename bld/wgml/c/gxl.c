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
* Description:  WGML tags :OL, :SL, :UL  :DL, :GL  and corresponding
*                         :eXX processing
*                         :LI and :LP processing
*
****************************************************************************/
#include    "wgml.h"
#include    "gvars.h"



/***************************************************************************/
/*  end_lp  processing as if the non existant :eLP tag was seen            */
/***************************************************************************/
static  void    end_lp( void )
{
    tag_cb  *   wk;

    if( nest_cb->c_tag == t_LP ) {      // terminate current :LP
        post_skip = &(((lp_lay_tag *)(nest_cb->lay_tag))->post_skip);
        wk = nest_cb;
        nest_cb = nest_cb->prev;
        add_tag_cb_to_pool( wk );
    }
}


/***************************************************************************/
/*  :SL, ... common processing                                             */
/***************************************************************************/

static void gml_xl_lp_common( const gmltag * entry, e_tags t )
{
    char        *   p;

    end_lp();                           // terminate :LP if active

    init_nest_cb();
    nest_cb->p_stack = copy_to_nest_stack();

    nest_cb->c_tag = t;

    scan_err = false;
    p = scan_start;
    if( *p == '.' ) p++;                // possible tag end
    if( t != t_LP ) {                   // text only allowed for :LP
        if( *p ) {                      // no text allowed
            g_err_tag_nest( str_tags[t_LI] );   // :LI expected
        }
        ProcFlags.need_li_lp = true;    // :LI or :LP  next
        scan_start = scan_stop + 1;
    }
    return;
}



/***************************************************************************/
/* Format:  :DL [compact]                                                  */
/*              [break]                                                    */
/*              [headhi=head-highlight]                                    */
/*              [termhi=term-highlight]                                    */
/*              [tsize='hor-space-unit'].                                  */
/*                                                                         */
/* The definition list tag signals the start of a definition list.  Each   */
/* list item in a definition list has two parts.  The first part is the    */
/* definition term and is defined with the :dt tag.  The second part is    */
/* the definition description and is defined with the :dd tag.  A          */
/* corresponding :edl tag must be specified for each :dl tag.  The compact */
/* corresponding :edl tag must be specified for each :dl tag.  The compact */
/* attribute indicates that the list items should be compacted.  Blank     */
/* lines that are normally placed between the list items will be           */
/* suppressed.  The compact attribute is one of the few WATCOM Script/GML  */
/* attributes which does not have an attribute value associated with it.   */
/* The break attribute indicates that the definition description should be */
/* started on a new output line if the size of the definition term exceeds */
/* the maximum horizontal space normally allowed for it.  If this          */
/* attribute is not specified, the definition description will be placed   */
/* after the definition term.  The break attribute is one of the few       */
/* WATCOM Script/GML attributes which does not have an attribute value     */
/* associated with it.  The headhi attribute allows you to set the         */
/* highlighting level of the definition list headings.  Non-negative       */
/* integer numbers are valid highlighting values.  The termhi attribute    */
/* allows you to set the highlighting level of the definition term.        */
/* Non-negative integer numbers are valid highlighting values.  The tsize  */
/* attribute allows you to set the minimum horizontal space taken by the   */
/* definition term.  Any valid horizontal space unit may be specified.     */
/* The attribute value is linked to the font of the :DT tag if the termhi  */
/* attribute is not specified.                                             */
/*                                                                         */
/***************************************************************************/

void    gml_dl( const gmltag * entry )  // not tested TBD
{
    char    *   p;
    bool        compact;

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    }
    gml_xl_lp_common( entry, t_DL );


    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/* Format:  :GL [compact] [termhi=term-highlight].                         */
/*                                                                         */
/* The glossary list tag signals the start of a glossary list, and is      */
/* usually used in the back material section.  Each list item in a         */
/* glossary list has two parts.  The first part is the glossary term and   */
/* is defined with the :gt tag.  The second part is the glossary           */
/* description and is defined with the :gd tag.  A corresponding :egl tag  */
/* must be specified for each :gl tag.  The compact attribute indicates    */
/* that the list items should be compacted.  Blank lines that are normally */
/* placed between the list items will be suppressed.  The compact          */
/* attribute is one of the few WATCOM Script/GML attributes which does not */
/* have an attribute value associated with it.  The termhi attribute       */
/* allows you to set the highlighting level of the glossary term.          */
/* Non-negative integer numbers are valid highlighting values.             */
/*                                                                         */
/***************************************************************************/

void    gml_gl( const gmltag * entry )  // not tested TBD
{
    char    *   p;
    bool        compact;

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    }
    gml_xl_lp_common( entry, t_GL );


    scan_start = scan_stop + 1;
    return;
}

/***************************************************************************/
/*Format: :OL [compact].                                                   */
/*                                                                         */
/*This tag signals the start of an ordered list. Items in the list are     */
/*specified using the :li tag. The list items are preceded by the number   */
/*of the list item. The layout determines the style of the number. An      */
/*ordered list may be used wherever a basic document element is permitted  */
/*to appear. A corresponding :eol tag must be specified for each :ol tag.  */
/*                                                                         */
/*The compact attribute indicates that the list items should be compacted. */
/*Blank lines that are normally placed between the list items will be      */
/*suppressed. The compact attribute is one of the few WATCOM Script/GML    */
/*attributes which does not have an attribute value associated with it.    */
/***************************************************************************/

void    gml_ol( const gmltag * entry )
{
    char    *   p;
    bool        compact;

    p = scan_start + 1;
    while( *p == ' ' ) {
        p++;
    }
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    } else {
        compact = false;
    }
    gml_xl_lp_common( entry, t_OL );

    nest_cb->compact = compact;

    nest_cb->li_number    = 0;
    nest_cb->left_indent  = conv_hor_unit( &layout_work.ol.left_indent );
    nest_cb->right_indent = conv_hor_unit( &layout_work.ol.right_indent );
    nest_cb->lay_tag      = &layout_work.ol;

    nest_cb->lm = g_cur_left;
    nest_cb->rm = g_page_right;

    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/* Format:  :SL [compact].                                                 */
/*                                                                         */
/* This tag signals the start of a simple list.                            */
/* Items in the list are specified using the :li tag.  A simple list may   */
/* occur wherever a basic document element is permitted to appear.  A      */
/* corresponding :esl tag must be specified for each :sl tag.  The compact */
/* attribute indicates that the list items should be compacted.  Blank     */
/* lines that are normally placed between the list items will be           */
/* suppressed.  The compact attribute is one of the few WATCOM Script/GML  */
/* attributes which does not have an attribute value associated with it.   */
/*                                                                         */
/***************************************************************************/

void    gml_sl( const gmltag * entry )
{
    char    *   p;
    bool        compact;

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    }
    gml_xl_lp_common( entry, t_SL );

    nest_cb->compact = compact;

    nest_cb->li_number    = 0;
    nest_cb->left_indent  = conv_hor_unit( &layout_work.sl.left_indent );
    nest_cb->right_indent = conv_hor_unit( &layout_work.sl.right_indent );
    nest_cb->lay_tag      = &layout_work.sl;

    nest_cb->lm = g_cur_left;
    nest_cb->rm = g_page_right;

    scan_start = scan_stop + 1;
    return;
}

/***************************************************************************/
/* Format:  :UL [compact].                                                 */
/*                                                                         */
/* This tag signals the start of an unordered                              */
/* list.  Items in the list are specified using the :li tag.  The list     */
/* items are preceded by a symbol such as an asterisk or a bullet.  This   */
/* tag may be used wherever a basic document element is permitted to       */
/* appear.  A corresponding :eul tag must be specified for each :ul tag.   */
/*                                                                         */
/* The compact attribute indicates that the list items should be           */
/* compacted.  Blank lines that are normally placed between the list items */
/* will be suppressed.  The compact attribute is one of the few WATCOM     */
/* Script/GML attributes which does not have an attribute value associated */
/* with it.                                                                */
/*                                                                         */
/***************************************************************************/

void    gml_ul( const gmltag * entry )
{
    char    *   p;
    bool        compact;

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    }
    gml_xl_lp_common( entry, t_UL );

    nest_cb->compact = compact;

    nest_cb->li_number    = 0;
    nest_cb->left_indent  = conv_hor_unit( &layout_work.ul.left_indent );
    nest_cb->right_indent = conv_hor_unit( &layout_work.ul.right_indent );
    nest_cb->lay_tag      = &layout_work.ul;

    nest_cb->lm = g_cur_left;
    nest_cb->rm = g_page_right;

    scan_start = scan_stop + 1;
    return;
}

/***************************************************************************/
/*  common :eXXX processing                                                */
/***************************************************************************/

void    gml_exl_common( const gmltag * entry, e_tags t )
{
    char    *   p;
    tag_cb  *   wk;

    if( ProcFlags.test_widow ) {
        out_buf_lines( &buf_lines, false );
        buf_lines_cnt = 0;
        ProcFlags.test_widow = 0;
    }
    process_line_full( &t_line, false );

    if( nest_cb->c_tag != t ) {         // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t + 1] );// no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        g_cur_left = nest_cb->lm;
        g_page_right = nest_cb->rm;
        wk = nest_cb;
        nest_cb = nest_cb->prev;
        add_tag_cb_to_pool( wk );
        g_curr_font_num = nest_cb->font;
        scan_err = false;
        p = scan_start;
        if( *p == '.' ) p++;            // over '.'
        if( *p ) {
            process_text( p, g_curr_font_num );
        }
    }
    scan_start = scan_stop + 1;
}


/***************************************************************************/
/* Format:  :eDL.                                                          */
/*                                                                         */
/* This tag signals the end of a definition list.  A                       */
/* corresponding :DL tag must be previously specified for each :eDL tag.   */
/*                                                                         */
/*                                                                         */
/* Format:  :eGL.                                                          */
/*                                                                         */
/* This tag signals the end of a glossary list.  A                         */
/* corresponding :GL tag must be previously specified for each :eGL tag.   */
/*                                                                         */
/*                                                                         */
/* Format:  :eOL.                                                          */
/*                                                                         */
/* This tag signals the end of an ordered list.  A                         */
/* corresponding :OL tag must be previously specified for each :eOL tag.   */
/*                                                                         */
/*                                                                         */
/* Format:  :eSL.                                                          */
/*                                                                         */
/* This tag signals the end of a simple list.  A                           */
/* corresponding :SL tag must be previously specified for each :eSL tag.   */
/*                                                                         */
/*                                                                         */
/* Format:  :eUL.                                                          */
/*                                                                         */
/* This tag signals the end of a unordered list.  A                        */
/* corresponding :UL tag must be previously specified for each :eUL tag.   */
/*                                                                         */
/***************************************************************************/

void    gml_edl( const gmltag * entry ) // not tested TBD
{
    gml_exl_common( entry, t_DL );
}

void    gml_egl( const gmltag * entry ) // not tested TBD
{
    gml_exl_common( entry, t_GL );
}

void    gml_eol( const gmltag * entry )
{
    end_lp();
    if( nest_cb->c_tag == t_OL ) {
        post_skip = &(((ol_lay_tag *)(nest_cb->lay_tag))->post_skip);
    }
    gml_exl_common( entry, t_OL );
}

void    gml_esl( const gmltag * entry )
{
    end_lp();
    if( nest_cb->c_tag == t_SL ) {
        post_skip = &(((sl_lay_tag *)(nest_cb->lay_tag))->post_skip);
    }
    gml_exl_common( entry, t_SL );
}

void    gml_eul( const gmltag * entry )
{
    end_lp();
    if( nest_cb->c_tag == t_UL ) {
        post_skip = &(((ul_lay_tag *)(nest_cb->lay_tag))->post_skip);
    }
    gml_exl_common( entry, t_UL );
}


/***************************************************************************/
/* :LI within :OL tag                                                      */
/***************************************************************************/

static  void    gml_li_ol( const gmltag * entry )
{
    char        *   p;
    char        *   pn;
    int32_t         skippre;
    int32_t         skippost;
    int32_t         skipsk;
    uint32_t        num_len;
    char            charnumber[MAX_L_AS_STR];

    scan_err = false;
    p = scan_start;

    nest_cb->li_number++;
    pn = format_num( nest_cb->li_number, charnumber, MAX_L_AS_STR,
                     ((ol_lay_tag *)(nest_cb->lay_tag))->number_style );
    if( pn != NULL ) {
        num_len = strlen( pn );
    } else {
        pn = charnumber;
        *pn = '?';
        *(pn + 1) = 0;
        num_len = 1;
    }

    prepare_doc_sect( ProcFlags.doc_sect ); // if not already done

    scr_process_break();

    if( ProcFlags.test_widow ) {
        out_buf_lines( &buf_lines, false );  // lines are no widows
        buf_lines_cnt = 0;
    }

    spacing = ((ol_lay_tag *)(nest_cb->lay_tag))->spacing;
    if( post_skip != NULL ) {
        skippost = conv_vert_unit( post_skip, spacing );
    } else {
        skippost = 0;
    }
    skipsk = calc_skip_value();   // pending .sk value?
    g_curr_font_num = ((ol_lay_tag *)(nest_cb->lay_tag))->number_font;
    if( ProcFlags.page_started ) {
        if( ProcFlags.need_li_lp ) {    // first :li for this list
            skippre = conv_vert_unit(
                      &(((ol_lay_tag *)(nest_cb->lay_tag))->pre_skip), spacing );
        } else if( !nest_cb->compact ) {
            skippre = conv_vert_unit(
                      &(((ol_lay_tag *)(nest_cb->lay_tag))->skip), spacing );
        } else {
            skippre = 0;
        }
        if( skippost > skippre ) {
            skippre = skippost;         // take maximum skip amount
        }
        if( skipsk > skippre ) {
            skippre = skipsk;           // take maximum skip amount
        }
        if( bin_driver->y_positive == 0x00 ) {
            if( skippre < g_cur_v_start ) {
                g_cur_v_start -= skippre;
            } else {
                g_cur_v_start = g_page_bottom - 1;  // force new page
            }
        } else {
            g_cur_v_start += skippre;
        }
    } else {
        if( bin_driver->y_positive == 0x00 ) {
            if( skippost > 0 ) {
                g_cur_v_start -= skippost;
            }
        } else {
            if( skippost > 0 ) {
                g_cur_v_start += skippost;
            }
        }
    }
    post_skip = NULL;

    ProcFlags.test_widow = true;        // prevent possible widows
    post_space = 0;

    g_cur_left = nest_cb->lm + nest_cb->left_indent;
    g_cur_h_start = g_cur_left;
    g_page_right = nest_cb->rm - nest_cb->right_indent;

    ProcFlags.keep_left_margin = true;  // keep special Note indent

    start_line_with_string( charnumber, g_curr_font_num );
    g_cur_h_start = g_cur_left +
        conv_hor_unit( &(((ol_lay_tag *)(nest_cb->lay_tag))->align) );

    if( t_line.last != NULL ) {
        g_cur_left += t_line.last->width + post_space;
    }
    post_space = 0;
    if( g_cur_h_start > g_cur_left ) {
        g_cur_left = g_cur_h_start;
    }
    g_cur_h_start = g_cur_left;
    ju_x_start = g_cur_h_start;

    spacing = ((ol_lay_tag *)(nest_cb->lay_tag))->spacing;
    g_curr_font_num = ((ol_lay_tag *)(nest_cb->lay_tag))->font;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    if( *p ) {
        process_text( p, g_curr_font_num ); // if text follows
    }

    ProcFlags.need_li_lp = false;       // 1. item in list processed
    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/* :LI within :SL tag                                                      */
/***************************************************************************/

static  void    gml_li_sl( const gmltag * entry )
{
    char        *   p;
    int32_t         skippre;
    int32_t         skippost;
    int32_t         skipsk;

    scan_err = false;
    p = scan_start;

    prepare_doc_sect( ProcFlags.doc_sect ); // if not already done

    scr_process_break();

    if( ProcFlags.test_widow ) {
        out_buf_lines( &buf_lines, false );  // lines are no widows
        buf_lines_cnt = 0;
    }

    spacing = ((sl_lay_tag *)(nest_cb->lay_tag))->spacing;
    if( post_skip != NULL ) {
        skippost = conv_vert_unit( post_skip, spacing );
    } else {
        skippost = 0;
    }
    skipsk = calc_skip_value();   // pending .sk value?
    if( ProcFlags.page_started ) {
        if( ProcFlags.need_li_lp ) {    // first :li for this list
            skippre = conv_vert_unit(
                      &(((sl_lay_tag *)(nest_cb->lay_tag))->pre_skip), spacing );
        } else if( !nest_cb->compact ) {
            skippre = conv_vert_unit(
                      &(((sl_lay_tag *)(nest_cb->lay_tag))->skip), spacing );
        } else {
            skippre = 0;
        }
        if( skippost > skippre ) {
            skippre = skippost;         // take maximum skip amount
        }
        if( skipsk > skippre ) {
            skippre = skipsk;           // take maximum skip amount
        }
        if( bin_driver->y_positive == 0x00 ) {
            if( skippre < g_cur_v_start ) {
                g_cur_v_start -= skippre;
            } else {
                g_cur_v_start = g_page_bottom - 1;  // force new page
            }
        } else {
            g_cur_v_start += skippre;
        }
    } else {
        if( bin_driver->y_positive == 0x00 ) {
            if( skippost > 0 ) {
                g_cur_v_start -= skippost;
            }
        } else {
            if( skippost > 0 ) {
                g_cur_v_start += skippost;
            }
        }
    }
    post_skip = NULL;

    ProcFlags.keep_left_margin = true;  // keep special Note indent
    ProcFlags.test_widow = true;        // prevent possible widows
    post_space = 0;

    g_cur_left = nest_cb->lm + nest_cb->left_indent;
    g_cur_h_start = g_cur_left;
    g_page_right = nest_cb->rm - nest_cb->right_indent;

    post_space = 0;
    g_cur_h_start = g_cur_left;
    ju_x_start = g_cur_h_start;

    spacing = ((sl_lay_tag *)(nest_cb->lay_tag))->spacing;
    g_curr_font_num = ((sl_lay_tag *)(nest_cb->lay_tag))->font;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    if( *p ) {
        process_text( p, g_curr_font_num ); // if text follows
    }

    ProcFlags.need_li_lp = false;
    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/* :LI within :UL tag                                                      */
/***************************************************************************/

static  void    gml_li_ul( const gmltag * entry )
{
    char        *   p;
    int32_t         skippre;
    int32_t         skippost;
    int32_t         skipsk;
    char            bullet[2];

    scan_err = false;
    p = scan_start;

    if( ((ul_lay_tag *)(nest_cb->lay_tag))->bullet_translate ) {
        bullet[0] = cop_in_trans( ((ul_lay_tag *)(nest_cb->lay_tag))->bullet,
                            ((ul_lay_tag *)(nest_cb->lay_tag))->bullet_font );
    } else {
        bullet[0] = ((ul_lay_tag *)(nest_cb->lay_tag))->bullet;
    }
    bullet[1] = 0;

    prepare_doc_sect( ProcFlags.doc_sect ); // if not already done

    scr_process_break();

    if( ProcFlags.test_widow ) {
        out_buf_lines( &buf_lines, false );  // lines are no widows
        buf_lines_cnt = 0;
    }

    spacing = ((ul_lay_tag *)(nest_cb->lay_tag))->spacing;
    if( post_skip != NULL ) {
        skippost = conv_vert_unit( post_skip, spacing );
    } else {
        skippost = 0;
    }
    skipsk = calc_skip_value();   // pending .sk value?
    g_curr_font_num = ((ul_lay_tag *)(nest_cb->lay_tag))->bullet_font;
    if( ProcFlags.page_started ) {
        if( ProcFlags.need_li_lp ) {    // first :li for this list
            skippre = conv_vert_unit(
                      &(((ul_lay_tag *)(nest_cb->lay_tag))->pre_skip), spacing );
        } else if( !nest_cb->compact ) {
            skippre = conv_vert_unit(
                      &(((ul_lay_tag *)(nest_cb->lay_tag))->skip), spacing );
        } else {
            skippre = 0;
        }
        if( skippost > skippre ) {
            skippre = skippost;         // take maximum skip amount
        }
        if( skipsk > skippre ) {
            skippre = skipsk;           // take maximum skip amount
        }
        if( bin_driver->y_positive == 0x00 ) {
            if( skippre < g_cur_v_start ) {
                g_cur_v_start -= skippre;
            } else {
                g_cur_v_start = g_page_bottom - 1;  // force new page
            }
        } else {
            g_cur_v_start += skippre;
        }
    } else {
        if( bin_driver->y_positive == 0x00 ) {
            if( skippost > 0 ) {
                g_cur_v_start -= skippost;
            }
        } else {
            if( skippost > 0 ) {
                g_cur_v_start += skippost;
            }
        }
    }
    post_skip = NULL;

    ProcFlags.test_widow = true;        // prevent possible widows
    post_space = 0;

    g_cur_left = nest_cb->lm + nest_cb->left_indent;
    g_cur_h_start = g_cur_left;
    g_page_right = nest_cb->rm - nest_cb->right_indent;

    ProcFlags.keep_left_margin = true;  // keep special Note indent

    start_line_with_string( bullet, g_curr_font_num );
    g_cur_h_start = g_cur_left +
        conv_hor_unit( &(((ul_lay_tag *)(nest_cb->lay_tag))->align) );

    if( t_line.last != NULL ) {
        g_cur_left += t_line.last->width + post_space;
    }
    post_space = 0;
    if( g_cur_h_start > g_cur_left ) {
        g_cur_left = g_cur_h_start;
    }
    g_cur_h_start = g_cur_left;
    ju_x_start = g_cur_h_start;

    spacing = ((ul_lay_tag *)(nest_cb->lay_tag))->spacing;
    g_curr_font_num = ((ul_lay_tag *)(nest_cb->lay_tag))->font;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    if( *p ) {
        process_text( p, g_curr_font_num ); // if text fullows
    }

    ProcFlags.need_li_lp = false;
    scan_start = scan_stop + 1;
    return;
}



/****************************************************************************/
/*Format: :LI [id='id-name'].<paragraph elements>                           */
/*                           <basic document elements>                      */
/*                                                                          */
/*This tag signals the start of an item in a simple, ordered, or unordered  */
/*list. The unordered list items are preceded by an annotation symbol, such */
/*as an asterisk. The ordered list items are annotated by an ordered        */
/*sequence. The id attribute associates an identifier name with the list    */
/*item, and may only be used when the list item is in an ordered list. The  */
/*identifier name is used when processing a list item reference, and must   */
/*be unique within the document.                                            */
/****************************************************************************/

void    gml_li( const gmltag * entry )
{
    if( nest_cb->c_tag == t_LP ) {      // terminate :LP if active
        end_lp();
    }

    switch( nest_cb->c_tag ) {
    case t_OL :
        gml_li_ol( entry );
        break;
    case t_SL :
        gml_li_sl( entry );
        break;
    case t_UL :
        gml_li_ul( entry );
        break;
#if 0
    case t_DL :
        gml_li_dl( entry );             // TBD
        break;
    case t_GL :
        gml_li_gl( entry );
        break;
#endif
    default:
        break;
    }
    return;
}


/***************************************************************************/
/* :LP                                                                     */
/***************************************************************************/
void    gml_lp( const gmltag * entry )
{
    char        *   p;
    int32_t         skippre;
    int32_t         skippost;
    int32_t         skipsk;

    scan_err = false;
    p = scan_start;

    gml_xl_lp_common( entry, t_LP );

    nest_cb->compact = false;

    nest_cb->li_number    = 0;
    nest_cb->left_indent  = conv_hor_unit( &layout_work.lp.left_indent );
    nest_cb->right_indent = conv_hor_unit( &layout_work.lp.right_indent );
    nest_cb->lay_tag      = &layout_work.lp;

    nest_cb->lm = nest_cb->prev->lm + nest_cb->prev->left_indent;
    nest_cb->rm = nest_cb->prev->rm - nest_cb->prev->right_indent;

    prepare_doc_sect( ProcFlags.doc_sect ); // if not already done

    scr_process_break();

    if( ProcFlags.test_widow ) {
        out_buf_lines( &buf_lines, false );  // lines are no widows
        buf_lines_cnt = 0;
    }

    spacing = ((lp_lay_tag *)(nest_cb->lay_tag))->spacing;
    if( post_skip != NULL ) {
        skippost = conv_vert_unit( post_skip, spacing );
    } else {
        skippost = 0;
    }
    skipsk = calc_skip_value();         // pending .sk value?
    if( ProcFlags.page_started ) {
        skippre = conv_vert_unit(
                    &(((lp_lay_tag *)(nest_cb->lay_tag))->pre_skip), spacing );
        if( skippost > skippre ) {
            skippre = skippost;         // take maximum skip amount
        }
        if( skipsk > skippre ) {
            skippre = skipsk;           // take maximum skip amount
        }
        if( bin_driver->y_positive == 0x00 ) {
            if( skippre < g_cur_v_start ) {
                g_cur_v_start -= skippre;
            } else {
                g_cur_v_start = g_page_bottom - 1;  // force new page
            }
        } else {
            g_cur_v_start += skippre;
        }
    } else {
        if( bin_driver->y_positive == 0x00 ) {
            if( skippost > 0 ) {
                g_cur_v_start -= skippost;
            }
        } else {
            if( skippost > 0 ) {
                g_cur_v_start += skippost;
            }
        }
    }
    post_skip = NULL;

    ProcFlags.keep_left_margin = true;  // keep special Note indent
    ProcFlags.test_widow = true;        // prevent possible widows
    post_space = 0;

    g_cur_left = nest_cb->lm + nest_cb->left_indent;// left start
                                        // possibly indent first line
    g_cur_h_start = g_cur_left + conv_hor_unit( &(layout_work.lp.line_indent) );

    g_page_right = nest_cb->rm - nest_cb->right_indent;

    ju_x_start = g_cur_h_start;

    spacing = ((lp_lay_tag *)(nest_cb->lay_tag))->spacing;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    if( *p ) {
        process_text( p, g_curr_font_num ); // if text follows
    }

    ProcFlags.need_li_lp = false;       // :LI or :LP seen
    scan_start = scan_stop + 1;
    return;
}

