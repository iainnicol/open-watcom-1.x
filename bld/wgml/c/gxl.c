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
* Description:  WGML tags :OL, :SL, :UL :DL, :GL
*                         :eOL, :eSL, :eUL :eDL, :eGL
*                         :LI, :LP
*                         :DD, :DDHD, :DT, :DTHD
*                         :GD, :GT
*
* Note: :LIREF is not yet implemented; it might be better placed
*       with :FIGREF, :FNREF, and :HDREF than here, depending on how it works
*       This file was originally done very early; other features may not be
*       fully implemented as well
****************************************************************************/
#include    "wgml.h"
#include    "gvars.h"

static  uint8_t     dl_cur_level    = 1;    // current DL list level
static  uint8_t     gl_cur_level    = 1;    // current GL list level
static  uint8_t     ol_cur_level    = 1;    // current OL list level
static  uint8_t     sl_cur_level    = 1;    // current SL list level
static  uint8_t     ul_cur_level    = 1;    // current UL list level


/***************************************************************************/
/* end_lp  processing as if the non existant :eLP tag was seen             */
/***************************************************************************/
static void end_lp( void )
{
    tag_cb  *   wk;

    if( nest_cb->c_tag == t_LP ) {      // terminate current :LP
        wk = nest_cb;
        nest_cb = nest_cb->prev;
        add_tag_cb_to_pool( wk );
    }
}


/***************************************************************************/
/* :SL, ... common processing                                              */
/***************************************************************************/

static void gml_xl_lp_common( e_tags t )
{
    char        *   p;

    end_lp();                           // terminate :LP if active

    init_nest_cb();
    nest_cb->p_stack = copy_to_nest_stack();

    nest_cb->c_tag = t;

    scan_err = false;
    p = scan_start;
    while( *p == ' ' ) p++;                 // skip spaces
    if( *p == '.' ) p++;                    // skip tag end
    if( t != t_LP ) {                       // text only allowed for :LP
        if( t != t_DL && t != t_GL ) {      // DL/GL don't require LI/LP
            ProcFlags.need_li_lp = true;    // :LI or :LP  next
        }
        start_doc_sect();                   // if not already done
        if( g_line_indent == 0 ) {
            ProcFlags.para_starting = false;    // clear for this tag's first break
        }
        scr_process_break();
        if( *p ) {
            process_text( p, g_curr_font );
        }
    }

    return;
}


/**************************************************************************************************/
/* Format:  :DL [compact]                                                                         */
/*              [break]                                                                           */
/*              [headhi=head-highlight]                                                           */
/*              [termhi=term-highlight]                                                           */
/*              [tsize='hor-space-unit'].                                                         */
/*                                                                                                */
/* The definition list tag signals the start of a definition list. Each list item in a definition */
/* list has two parts. The first part is the definition term and is defined with the :dt tag.     */
/* The second part is the definition description and is defined with the :dd tag. A               */
/* corresponding :edl tag must be specified for each :dl tag.                                     */
/*                                                                                                */
/* The compact attribute indicates that the list items should be compacted. Blank lines           */
/* that are normally placed between the list items will be suppressed. The compact                */
/* attribute is one of the few WATCOM Script/GML attributes which does not have an                */
/* attribute value associated with it.                                                            */
/*                                                                                                */
/* The break attribute indicates that the definition description should be started on a new       */
/* output line if the size of the definition term exceeds the maximum horizontal space            */
/* normally allowed for it. If this attribute is not specified, the definition description will   */
/* be placed after the definition term. The break attribute is one of the few WATCOM              */
/* Script/GML attributes which does not have an attribute value associated with it.               */
/*                                                                                                */
/* The headhi attribute allows you to set the highlighting level of the definition list           */
/* headings. Non-negative integer numbers are valid highlighting values.                          */
/*                                                                                                */
/* The termhi attribute allows you to set the highlighting level of the definition term.          */
/* Non-negative integer numbers are valid highlighting values.                                    */
/*                                                                                                */
/* The tsize attribute allows you to set the minimum horizontal space taken by the                */
/* definition term. Any valid horizontal space unit may be specified. The attribute value         */
/* is linked to the font of the :DT tag if the termhi attribute is not specified (see "Font       */
/* Linkage" on page 77).                                                                          */
/**************************************************************************************************/

void gml_dl( const gmltag * entry )
{
    bool                compact;
    char            *   p;

    if( !ProcFlags.start_section ) {
        start_doc_sect();
    }

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    scan_start = p;                     // over spaces
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    } else {
        compact = false;
    }
    gml_xl_lp_common( t_DL );

    nest_cb->dl_layout = layout_work.dl.first;
    while( (nest_cb->dl_layout != NULL) && (nest_cb->dl_layout->level < dl_cur_level) ) {
        nest_cb->dl_layout = nest_cb->dl_layout->next;
    }

    if( nest_cb->dl_layout == NULL ) {
        internal_err( __FILE__, __LINE__ );
    }

    if( dl_cur_level < layout_work.dl.max_level ) {
        dl_cur_level++;
    } else {
        dl_cur_level = 1;
    }

    nest_cb->compact = compact;
    nest_cb->font = g_curr_font;

    nest_cb->li_number = 0;
    nest_cb->align = conv_hor_unit( &nest_cb->dl_layout->align, g_curr_font );
    nest_cb->left_indent = conv_hor_unit( &nest_cb->dl_layout->left_indent, g_curr_font );
    nest_cb->right_indent = -1 * conv_hor_unit( &nest_cb->dl_layout->right_indent, g_curr_font );
    nest_cb->xl_pre_skip = conv_vert_unit( &nest_cb->dl_layout->pre_skip, spacing, g_curr_font );

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    spacing = (int8_t) nest_cb->dl_layout->spacing;

    scan_start = scan_stop + 1;
    return;
}


/***********************************************************************************************/
/* Format:  :GL [compact]                                                                      */
/*              [termhi=term-highlight].                                                       */
/*                                                                                             */
/* The glossary list tag signals the start of a glossary list, and is usually used in the back */
/* material section. Each list item in a glossary list has two parts. The first part is the    */
/* glossary term and is defined with the :gt tag. The second part is the glossary              */
/* description and is defined with the :gd tag. A corresponding :egl tag must be specified     */
/* for each :gl tag.                                                                           */
/*                                                                                             */
/* The compact attribute indicates that the list items should be compacted. Blank lines        */
/* that are normally placed between the list items will be suppressed. The compact             */
/* attribute is one of the few WATCOM Script/GML attributes which does not have an             */
/* attribute value associated with it.                                                         */
/*                                                                                             */
/* The termhi attribute allows you to set the highlighting level of the glossary term.         */
/* Non-negative integer numbers are valid highlighting values.                                 */
/***********************************************************************************************/

void gml_gl( const gmltag * entry )
{
    bool                compact;
    char            *   p;

    if( !ProcFlags.start_section ) {
        start_doc_sect();
    }

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    scan_start = p;                     // over spaces
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    } else {
        compact = false;
    }
    gml_xl_lp_common( t_GL );

    nest_cb->gl_layout = layout_work.gl.first;
    while( (nest_cb->gl_layout != NULL) && (nest_cb->gl_layout->level < gl_cur_level) ) {
        nest_cb->gl_layout = nest_cb->gl_layout->next;
    }

    if( nest_cb->gl_layout == NULL ) {
        internal_err( __FILE__, __LINE__ );
    }

    if( gl_cur_level < layout_work.gl.max_level ) {
        gl_cur_level++;
    } else {
        gl_cur_level = 1;
    }

    nest_cb->compact = compact;
    nest_cb->font = g_curr_font;

    nest_cb->li_number = 0;
    nest_cb->align = conv_hor_unit( &nest_cb->gl_layout->align, g_curr_font );
    nest_cb->left_indent = conv_hor_unit( &nest_cb->gl_layout->left_indent, g_curr_font );
    nest_cb->right_indent = -1 * conv_hor_unit( &nest_cb->gl_layout->right_indent, g_curr_font );
    nest_cb->xl_pre_skip = conv_vert_unit( &nest_cb->gl_layout->pre_skip, spacing, g_curr_font );

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    spacing = (int8_t) nest_cb->gl_layout->spacing;

    scan_start = scan_stop + 1;
    return;
}

/************************************************************************************************/
/* Format: :OL [compact].                                                                       */
/*                                                                                              */
/* This tag signals the start of an ordered list. Items in the list are specified using the :li */
/* tag. The list items are preceded by the number of the list item. The layout determines       */
/* the style of the number.                                                                     */
/*                                                                                              */
/* An ordered list may be used wherever a basic document element is permitted to appear.        */
/* A corresponding :eol tag must be specified for each :ol tag.                                 */
/*                                                                                              */
/* The compact attribute indicates that the list items should be compacted. Blank lines         */
/* that are normally placed between the list items will be suppressed. The compact              */
/* attribute is one of the few WATCOM Script/GML attributes which does not have an              */
/* attribute value associated with it.                                                          */
/************************************************************************************************/

void gml_ol( const gmltag * entry )
{
    bool                compact;
    char            *   p;

    if( !ProcFlags.start_section ) {
        start_doc_sect();
    }

    p = scan_start + 1;
    while( *p == ' ' ) {
        p++;
    }
    scan_start = p;
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    } else {
        compact = false;
    }
    if( ProcFlags.need_li_lp ) {
        xx_nest_err( err_no_li_lp );
    }
    gml_xl_lp_common( t_OL );

    nest_cb->ol_layout = layout_work.ol.first;
    while( (nest_cb->ol_layout != NULL) && (nest_cb->ol_layout->level < ol_cur_level) ) {
        nest_cb->ol_layout = nest_cb->ol_layout->next;
    }

    if( nest_cb->ol_layout == NULL ) {
        internal_err( __FILE__, __LINE__ );
    }

    if( ol_cur_level < layout_work.ol.max_level ) {
        ol_cur_level++;
    } else {
        ol_cur_level = 1;
    }

    nest_cb->compact = compact;
    nest_cb->font = g_curr_font;
    g_curr_font = nest_cb->ol_layout->font;

    nest_cb->li_number = 0;
    nest_cb->left_indent = conv_hor_unit( &nest_cb->ol_layout->left_indent, g_curr_font );
    nest_cb->right_indent = -1 * conv_hor_unit( &nest_cb->ol_layout->right_indent, g_curr_font );
    nest_cb->xl_pre_skip = conv_vert_unit( &nest_cb->ol_layout->pre_skip, spacing, g_curr_font );

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    spacing = (int8_t) nest_cb->ol_layout->spacing;

    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************************************/
/* Format:  :SL [compact].                                                                         */
/*                                                                                                 */
/* This tag signals the start of a simple list. Items in the list are specified using the :li tag. */
/*                                                                                                 */
/* A simple list may occur wherever a basic document element is permitted to appear. A             */
/* corresponding :esl tag must be specified for each :sl tag.                                      */
/*                                                                                                 */
/* The compact attribute indicates that the list items should be compacted. Blank lines            */
/* that are normally placed between the list items will be suppressed. The compact                 */
/* attribute is one of the few WATCOM Script/GML attributes which does not have an                 */
/* attribute value associated with it.                                                             */
/***************************************************************************************************/

void gml_sl( const gmltag * entry )
{
    bool                compact;
    char            *   p;

    if( !ProcFlags.start_section ) {
        start_doc_sect();
    }

    p = scan_start + 1;
    while( *p == ' ' ) {
        p++;
    }
    scan_start = p;                     // over spaces
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    } else {
        compact = false;
    }
    if( ProcFlags.need_li_lp ) {
        xx_nest_err( err_no_li_lp );
    }
    gml_xl_lp_common( t_SL );

    nest_cb->sl_layout = layout_work.sl.first;
    while( (nest_cb->sl_layout != NULL) && (nest_cb->sl_layout->level < sl_cur_level) ) {
        nest_cb->sl_layout = nest_cb->sl_layout->next;
    }

    if( nest_cb->sl_layout == NULL ) {
        internal_err( __FILE__, __LINE__ );
    }

    if( sl_cur_level < layout_work.sl.max_level ) {
        sl_cur_level++;
    } else {
        sl_cur_level = 1;
    }

    nest_cb->compact = compact;
    nest_cb->font = g_curr_font;
    g_curr_font = nest_cb->sl_layout->font;

    nest_cb->li_number = 0;
    nest_cb->left_indent = conv_hor_unit( &nest_cb->sl_layout->left_indent, g_curr_font );
    nest_cb->right_indent = -1 * conv_hor_unit( &nest_cb->sl_layout->right_indent, g_curr_font );
    nest_cb->xl_pre_skip = conv_vert_unit( &nest_cb->sl_layout->pre_skip, spacing, g_curr_font );

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    spacing = (int8_t) nest_cb->sl_layout->spacing;

    scan_start = scan_stop + 1;
    return;
}

/**************************************************************************************************/
/* Format:  :UL [compact].                                                                        */
/*                                                                                                */
/* This tag signals the start of an unordered list. Items in the list are specified using the :li */
/* tag. The list items are preceded by a symbol such as an asterisk or a bullet.                  */
/*                                                                                                */
/* This tag may be used wherever a basic document element is permitted to appear. A               */
/* corresponding :eul tag must be specified for each :ul tag.                                     */
/*                                                                                                */
/* The compact attribute indicates that the list items should be compacted. Blank lines           */
/* that are normally placed between the list items will be suppressed. The compact                */
/* attribute is one of the few WATCOM Script/GML attributes which does not have an                */
/* attribute value associated with it.                                                            */
/**************************************************************************************************/

void gml_ul( const gmltag * entry )
{
    bool                compact;
    char            *   p;

    if( !ProcFlags.start_section ) {
        start_doc_sect();
    }

    p = scan_start + 1;
    while( *p == ' ' ) {
        p++;
    }
    scan_start = p;                     // over spaces
    if( !strnicmp( "compact", p, 7 ) ) {
        compact = true;
        scan_start = p + 7;
    } else {
        compact = false;
    }
    if( ProcFlags.need_li_lp ) {
        xx_nest_err( err_no_li_lp );
    }
    gml_xl_lp_common( t_UL );

    nest_cb->ul_layout = layout_work.ul.first;
    while( (nest_cb->ul_layout != NULL) && (nest_cb->ul_layout->level < ul_cur_level) ) {
        nest_cb->ul_layout = nest_cb->ul_layout->next;
    }

    if( nest_cb->ul_layout == NULL ) {
        internal_err( __FILE__, __LINE__ );
    }

    if( ul_cur_level < layout_work.ul.max_level ) {
        ul_cur_level++;
    } else {
        ul_cur_level = 1;
    }

    nest_cb->compact = compact;
    nest_cb->font = g_curr_font;
    g_curr_font = nest_cb->ul_layout->font;

    nest_cb->li_number = 0;
    nest_cb->left_indent = conv_hor_unit( &nest_cb->ul_layout->left_indent, g_curr_font );
    nest_cb->right_indent = -1 * conv_hor_unit( &nest_cb->ul_layout->right_indent, g_curr_font );
    nest_cb->xl_pre_skip = conv_vert_unit( &nest_cb->ul_layout->pre_skip, spacing, g_curr_font );

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    spacing = (int8_t) nest_cb->ul_layout->spacing;

    scan_start = scan_stop + 1;
    return;
}

/***************************************************************************/
/* common :eXXX processing                                                 */
/***************************************************************************/

void    gml_exl_common( const gmltag * entry )
{
    char    *   p;
    tag_cb  *   wk;

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
        gml_pc( NULL );
    } else {
        ProcFlags.skips_valid = false;  // force use of post_skip with following text element
    }

    ProcFlags.need_li_lp = false;       // :LI or :LP no longer needed
    scan_start = scan_stop + 1;
}


/*********************************************************************************************/
/* Format:  :eDL.                                                                            */
/*                                                                                           */
/* This tag signals the end of a definition list. A corresponding :dl tag must be previously */
/* specified for each :edl tag.                                                              */
/*                                                                                           */
/*                                                                                           */
/* Format:  :eGL.                                                                            */
/*                                                                                           */
/* This tag signals the end of a glossary list. A corresponding :gl tag must be previously   */
/* specified for each :egl tag.                                                              */
/*                                                                                           */
/*                                                                                           */
/* Format:  :eOL.                                                                            */
/*                                                                                           */
/* This tag signals the end of an ordered list. A corresponding :ol tag must be previously   */
/* specified for each :eol tag.                                                              */
/*                                                                                           */
/*                                                                                           */
/* Format:  :eSL.                                                                            */
/*                                                                                           */
/* This tag signals the end of a simple list. A corresponding :sl tag must be previously     */
/* specified for each :esl tag.                                                              */
/*                                                                                           */
/*                                                                                           */
/* Format:  :eUL.                                                                            */
/*                                                                                           */
/* This tag signals the end of an unordered list. A corresponding :ul tag must be            */
/* previously specified for each :eul tag.                                                   */
/*********************************************************************************************/

void    gml_edl( const gmltag * entry ) // not tested TBD
{
    if( g_line_indent == 0 ) {
        ProcFlags.para_starting = false;    // clear for this tag's break
    }
    scr_process_break();
    if( nest_cb->c_tag == t_LP ) {      // terminate :LP if active
        end_lp();
    }

    if( nest_cb->c_tag != t_DL ) {      // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t_DL + 1] );// no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        set_skip_vars( NULL, NULL, &nest_cb->dl_layout->post_skip, 1, g_curr_font );
        gml_exl_common( entry );
        if( dl_cur_level == 1 ) {
            dl_cur_level = layout_work.dl.max_level;
        } else {
            dl_cur_level--;
        }
    }
}

void    gml_egl( const gmltag * entry ) // not tested TBD
{
    if( g_line_indent == 0 ) {
        ProcFlags.para_starting = false;    // clear for this tag's break
    }
    scr_process_break();
    if( nest_cb->c_tag == t_LP ) {      // terminate :LP if active
        end_lp();
    }

    if( nest_cb->c_tag != t_GL ) {      // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t_GL + 1] );// no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        set_skip_vars( NULL, NULL, &nest_cb->gl_layout->post_skip, 1, g_curr_font );
        gml_exl_common( entry );
        if( gl_cur_level == 1 ) {
            gl_cur_level = layout_work.gl.max_level;
        } else {
            gl_cur_level--;
        }
    }
}

void    gml_eol( const gmltag * entry )
{
    if( g_line_indent == 0 ) {
        ProcFlags.para_starting = false;    // clear for this tag's break
    }
    scr_process_break();
    if( nest_cb->c_tag == t_LP ) {      // terminate :LP if active
        end_lp();
        g_curr_font = nest_cb->font;    // restore font
    }

    if( nest_cb->c_tag != t_OL ) {      // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t_OL + 1] );// no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        set_skip_vars( NULL, NULL, &nest_cb->ol_layout->post_skip, 1, g_curr_font );
        gml_exl_common( entry );
        if( ol_cur_level == 1 ) {
            ol_cur_level = layout_work.ol.max_level;
        } else {
            ol_cur_level--;
        }
    }
}

void    gml_esl( const gmltag * entry )
{
    if( g_line_indent == 0 ) {
        ProcFlags.para_starting = false;    // clear for this tag's break
    }
    scr_process_break();
    if( nest_cb->c_tag == t_LP ) {      // terminate :LP if active
        end_lp();
        g_curr_font = nest_cb->font;    // restore font
    }

    if( nest_cb->c_tag != t_SL ) {      // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t_SL + 1] );// no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        set_skip_vars( NULL, NULL, &nest_cb->sl_layout->post_skip, 1, g_curr_font );
        gml_exl_common( entry );
        if( sl_cur_level == 1 ) {
            sl_cur_level = layout_work.sl.max_level;
        } else {
            sl_cur_level--;
        }
    }
}

void    gml_eul( const gmltag * entry )
{
    if( g_line_indent == 0 ) {
        ProcFlags.para_starting = false;    // clear for this tag's break
    }
    scr_process_break();
    if( nest_cb->c_tag == t_LP ) {      // terminate :LP if active
        end_lp();
        g_curr_font = nest_cb->font;    // restore font
    }

    if( nest_cb->c_tag != t_UL ) {      // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t_UL + 1] );// no exxx expected, no tag active
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        set_skip_vars( NULL, NULL, &nest_cb->ul_layout->post_skip, 1, g_curr_font );
        gml_exl_common( entry );
        if( ul_cur_level == 1 ) {
            ul_cur_level = layout_work.ul.max_level;
        } else {
            ul_cur_level--;
        }
    }
}


/***************************************************************************/
/* :LI within :OL tag                                                      */
/***************************************************************************/

static  void    gml_li_ol( const gmltag * entry )
{
    char            charnumber[MAX_L_AS_STR];
    char        *   p;
    char        *   pn;
    int32_t         t_align         = 0;
    int32_t         t_left_indent_1 = 0;
    int32_t         t_left_indent_2 = 0;
    int32_t         t_right_indent  = 0;
    uint32_t        num_len;

    scan_err = false;
    p = scan_start;

    if( nest_cb == NULL ) {
        xx_nest_err( err_li_lp_no_list );   // tag must be in a list
        scan_start = scan_stop + 1;
        return;
    }

    t_align = conv_hor_unit( &nest_cb->ol_layout->align, g_curr_font );
    nest_cb->li_number++;
    pn = format_num( nest_cb->li_number, charnumber, MAX_L_AS_STR,
                     nest_cb->ol_layout->number_style );
    if( pn != NULL ) {
        num_len = strlen( pn );
        *(pn + num_len) = ' ';          // trailing space like wgml4 does
        *(pn + num_len + 1) = '\0';
        num_len++;
    } else {
        pn = charnumber;
        *pn = '?';
        *(pn + 1) = 0;
        num_len = 1;
    }

    scr_process_break();

    g_curr_font = nest_cb->ol_layout->number_font;

    if( ProcFlags.need_li_lp ) {        // first :li for this list
        set_skip_vars( &nest_cb->ol_layout->pre_skip, NULL, NULL, spacing, g_curr_font );
    } else if( !nest_cb->compact ) {
        set_skip_vars( &nest_cb->ol_layout->skip, NULL, NULL, spacing, g_curr_font );
    } else {                            // compact
        set_skip_vars( NULL, NULL, NULL, 1, g_curr_font );
    }

    post_space = 0;

    /* Use original indents, not values possibly modified by IN */

    if( g_indent > 0 ) {
        t_left_indent_1 = conv_hor_unit( &nest_cb->ol_layout->left_indent, g_curr_font )
                            + nest_cb->prev->left_indent + nest_cb->prev->align;
    } else {
        t_left_indent_1 = conv_hor_unit( &nest_cb->ol_layout->left_indent, g_curr_font )
                            + nest_cb->prev->left_indent;
    }
    t_left_indent_2 = conv_hor_unit( &nest_cb->ol_layout->left_indent, g_curr_font );
    t_right_indent = -1 * conv_hor_unit( &nest_cb->ol_layout->right_indent, g_curr_font )
                            + nest_cb->prev->right_indent;
    t_page.cur_left = nest_cb->lm + t_left_indent_2;
    t_page.max_width = nest_cb->rm + t_right_indent;

    t_page.cur_width = t_page.cur_left;
    ProcFlags.keep_left_margin = true;  // keep special Note indent
    start_line_with_string( charnumber, g_curr_font, true );

    t_page.cur_width = t_page.cur_left + t_align;

    if( t_line != NULL ) {
        if( t_line->last != NULL ) {
            t_page.cur_left += t_line->last->width + post_space;
        }
    }
    post_space = 0;
    if( t_page.cur_width > t_page.cur_left ) {
        t_page.cur_left = t_page.cur_width;
    }
    t_page.cur_width = t_page.cur_left;
    ju_x_start = t_page.cur_width;

    g_curr_font = nest_cb->ol_layout->font;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    ProcFlags.need_li_lp = false;       // 1. item in list processed
    if( *p ) {
        process_text( p, g_curr_font ); // if text follows
    }

    nest_cb->align = t_align;

    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/* :LI within :SL tag                                                      */
/***************************************************************************/

static  void    gml_li_sl( const gmltag * entry )
{
    char        *   p;
    int32_t         t_left_indent_1 = 0;
    int32_t         t_left_indent_2 = 0;
    int32_t         t_right_indent  = 0;

    scan_err = false;
    p = scan_start;

    if( nest_cb == NULL ) {
        xx_nest_err( err_li_lp_no_list );   // tag must be in a list
        scan_start = scan_stop + 1;
        return;
    }

    scr_process_break();

    if( ProcFlags.need_li_lp ) {        // first :li for this list
        set_skip_vars( &nest_cb->sl_layout->pre_skip, NULL, NULL, spacing, g_curr_font );
    } else if( !nest_cb->compact ) {
        set_skip_vars( &nest_cb->sl_layout->skip, NULL, NULL, spacing, g_curr_font );
    } else {                            // compact
        set_skip_vars( NULL, NULL, NULL, 1, g_curr_font );
    }

    ProcFlags.keep_left_margin = true;  // keep special Note indent

    /* Use original indents, not values possibly modified by IN */

    t_left_indent_1 = conv_hor_unit( &nest_cb->sl_layout->left_indent, g_curr_font )
                            + nest_cb->prev->left_indent + nest_cb->prev->align;
    t_left_indent_2 = conv_hor_unit( &nest_cb->sl_layout->left_indent, g_curr_font );
    t_right_indent = -1 * conv_hor_unit( &nest_cb->sl_layout->right_indent, g_curr_font )
                            + nest_cb->prev->right_indent;
    t_page.cur_left = nest_cb->lm + t_left_indent_2;
    t_page.max_width = nest_cb->rm + t_right_indent;

    t_page.cur_width = t_page.cur_left;
    post_space = 0;
    ju_x_start = t_page.cur_width;

    g_curr_font = nest_cb->sl_layout->font;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    ProcFlags.need_li_lp = false;
    if( *p ) {
        process_text( p, g_curr_font ); // if text follows
    }

    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/* :LI within :UL tag                                                      */
/***************************************************************************/

static  void    gml_li_ul( const gmltag * entry )
{
    char        *   p;
    char            bullet[3];
    int32_t         t_align         = 0;
    int32_t         t_left_indent_1 = 0;
    int32_t         t_left_indent_2 = 0;
    int32_t         t_right_indent  = 0;

    scan_err = false;
    p = scan_start;

    if( nest_cb == NULL ) {
        xx_nest_err( err_li_lp_no_list );   // tag must be in a list
        scan_start = scan_stop + 1;
        return;
    }

    if( nest_cb->ul_layout->bullet_translate ) {
        bullet[0] = cop_in_trans( nest_cb->ul_layout->bullet, nest_cb->ul_layout->bullet_font );
    } else {
        bullet[0] = nest_cb->ul_layout->bullet;
    }
    bullet[1] = ' ';                    // 1 trailing space as wgml4 does
    bullet[2] = 0;

    scr_process_break();

    if( ProcFlags.need_li_lp ) {        // first :li for this list
        set_skip_vars( &nest_cb->ul_layout->pre_skip, NULL, NULL, spacing, g_curr_font );
    } else if( !nest_cb->compact ) {
        set_skip_vars( &nest_cb->ul_layout->skip, NULL, NULL, spacing, g_curr_font );
    } else {                            // compact
        set_skip_vars( NULL, NULL, NULL, 1, g_curr_font );
    }

    g_curr_font = nest_cb->ul_layout->bullet_font;
    post_space = 0;

    /* Use original indents, not values possibly modified by IN */

    if( g_indent > 0 ) {
        t_left_indent_1  = conv_hor_unit( &nest_cb->ul_layout->left_indent, g_curr_font )
                            + nest_cb->prev->left_indent + nest_cb->prev->align;
    } else {
        t_left_indent_1  = conv_hor_unit( &nest_cb->ul_layout->left_indent, g_curr_font )
                            + nest_cb->prev->left_indent;
    }
    t_left_indent_2  = conv_hor_unit( &nest_cb->ul_layout->left_indent, g_curr_font );
    t_right_indent = -1 * conv_hor_unit( &nest_cb->ul_layout->right_indent, g_curr_font )
                            + nest_cb->prev->right_indent;
    t_page.cur_left = nest_cb->lm + t_left_indent_2;
    t_page.max_width = nest_cb->rm + t_right_indent;

    t_page.cur_width = t_page.cur_left;
    ProcFlags.keep_left_margin = true;  // keep special Note indent
    start_line_with_string( bullet, g_curr_font, true );

    t_align = conv_hor_unit( &nest_cb->ul_layout->align, g_curr_font );
    t_page.cur_width = t_page.cur_left + t_align;

    if( t_line != NULL ) {
        if( t_line->last != NULL ) {
            t_page.cur_left += t_line->last->width + post_space;
        }
    }
    post_space = 0;
    if( t_page.cur_width > t_page.cur_left ) {
        t_page.cur_left = t_page.cur_width;
    }
    t_page.cur_width = t_page.cur_left;
    ju_x_start = t_page.cur_width;

    g_curr_font = nest_cb->ul_layout->font;
    if( *p == '.' ) p++;                // over '.'
    while( *p == ' ' ) p++;             // skip initial spaces
    ProcFlags.need_li_lp = false;
    if( *p ) {
        process_text( p, g_curr_font ); // if text fullows
    }
    nest_cb->align = t_align;

    t_page.cur_left = nest_cb->lm + t_left_indent_2 + nest_cb->align;

    scan_start = scan_stop + 1;
    return;
}


/*******************************************************************************************/
/* Format: :LI [id='id-name'].<paragraph elements>                                         */
/*                            <basic document elements>                                    */
/*                                                                                         */
/* This tag signals the start of an item in a simple, ordered, or unordered list. The      */
/* unordered list items are preceded by an annotation symbol, such as an asterisk. The     */
/* ordered list items are annotated by an ordered sequence.                                */
/*                                                                                         */
/* The id attribute associates an identifier name with the list item, and may only be used */
/* when the list item is in an ordered list. The identifier name is used when processing a */
/* list item reference, and must be unique within the document.                            */
/*                                                                                         */
/* NOTE: wgml 4.0 produces an error if LI occurs inside a DL or GL                         */
/*******************************************************************************************/

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
    case t_DL :
    case t_GL :
        g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // end tag expected
        break;
    default:
        break;
    }
    return;
}


/************************************************************************************************/
/* Format: :LP.<paragraph elements>                                                             */
/*                                                                                              */
/* The list part tag is used to insert an explanation into the middle of a list. It may be used */
/* in simple, ordered, unordered, definition and glossary lists.                                */
/************************************************************************************************/

void    gml_lp( const gmltag * entry )
{
    char        *   p;

    scan_err = false;
    p = scan_start;

    if( nest_cb == NULL ) {
        xx_nest_err( err_li_lp_no_list );   // tag must be in a list
        scan_start = scan_stop + 1;
        return;
    }

    if( nest_cb->c_tag == t_LP ) {          // restore margins saved by prior LP
        t_page.cur_left = nest_cb->lm;
        t_page.max_width = nest_cb->rm;
    } else {
        t_page.cur_left = nest_cb->lm;
        t_page.max_width = nest_cb->rm;
    }

    nest_cb->font = g_curr_font;
    g_curr_font = layout_work.defaults.font;    // matches wgml 4.0

    gml_xl_lp_common( t_LP );

    if( g_line_indent == 0 ) {
        ProcFlags.para_starting = false;    // clear for this tag's first break
    }
    scr_process_break();

    nest_cb->compact = false;
    nest_cb->font = g_curr_font;
    g_curr_font = layout_work.defaults.font;    // matches wgml 4.0

    nest_cb->li_number    = 0;
    nest_cb->left_indent  = conv_hor_unit( &layout_work.lp.left_indent, g_curr_font );
    nest_cb->right_indent = -1 * conv_hor_unit( &layout_work.lp.right_indent, g_curr_font );

    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;

    spacing = (int8_t) layout_work.lp.spacing;

    ProcFlags.keep_left_margin = true;  // keep indent
    post_space = 0;

    set_skip_vars( &layout_work.lp.pre_skip, NULL, &layout_work.lp.post_skip, spacing, g_curr_font );
    if( ProcFlags.need_li_lp ) {        // :LP first tag in list
        if( nest_cb->prev->xl_pre_skip > g_subs_skip ) {
            g_subs_skip = nest_cb->prev->xl_pre_skip;
        }
    }

    nest_cb->left_indent += nest_cb->prev->left_indent;
    nest_cb->right_indent += nest_cb->prev->right_indent;

    t_page.cur_left = nest_cb->lm + nest_cb->left_indent;   // left start
                                        // possibly indent first line
    g_line_indent = conv_hor_unit( &(layout_work.lp.line_indent), g_curr_font );
    t_page.cur_width = t_page.cur_left + g_line_indent;

    t_page.max_width = nest_cb->rm + nest_cb->right_indent;

    ju_x_start = t_page.cur_width;

    ProcFlags.need_li_lp = false;       // :LI or :LP seen
    ProcFlags.para_starting = true;     // for next break, not this tag's break

    if( *p == '.' ) p++;                // possible tag end
    while( *p == ' ' ) p++;             // skip initial spaces
    if( *p ) {
        process_text( p, g_curr_font ); // if text follows
    }

    scan_start = scan_stop + 1;
    return;
}

/********************************************************************************************/
/* Format: :DD.<paragraph elements>                                                         */
/*             <basic document elements>                                                    */
/*                                                                                          */
/* This tag signals the start of the text for an item description in a definition list. The */
/* definition description tag must be preceded by a corresponding :dt tag, and may only     */
/* appear in a definition list.                                                             */
/********************************************************************************************/

void gml_dd( const gmltag * entry )
{
    return;
}


/*******************************************************************************************/
/* Format: :DDHD.<text line>                                                               */
/*                                                                                         */
/* The definition description heading tag is used to specify a heading for the definition  */
/* description of a definition list. It must be preceded by a corresponding :dthd tag, and */
/* may only appear in a definition list. The heading tag may be used more than once        */
/* within a single definition list.                                                        */
/*******************************************************************************************/

void gml_ddhd( const gmltag * entry )
{
    return;
}


/************************************************************************************************/
/* Format: :DT.<text line>                                                                      */
/*                                                                                              */
/* This tag is used to specify the term which is defined for each item in a definition list. It */
/* is always followed by a :dd tag, which specifies the start of the text to define the term,   */
/* and may only appear in a definition list.                                                    */
/************************************************************************************************/

void gml_dt( const gmltag * entry )
{
    return;
}


/**********************************************************************************************/
/* Format: :DTHD.<text line>                                                                  */
/*                                                                                            */
/* The definition term heading tag is used to specify a heading for the definition terms of a */
/* definition list. It is always followed by a :ddhd tag, and may only appear in a            */
/* definition list. The heading tag may be used more than once within a single definition     */
/* list.                                                                                      */
/**********************************************************************************************/

void gml_dthd( const gmltag * entry )
{
    return;
}


/**********************************************************************************************/
/* Format: :GD.<paragraph elements>                                                           */
/*             <basic document elements>                                                      */
/*                                                                                            */
/* The glossary description tag signals the start of the text for an item in a glossary list. */
/* The glossary description tag must be preceded by a corresponding :gt tag, and may only     */
/* appear in a glossary list.                                                                 */
/**********************************************************************************************/

void gml_gd( const gmltag * entry )
{
    return;
}


/**********************************************************************************************/
/* Format: :GT.<text line>                                                                    */
/*                                                                                            */
/* This tag is used to specify the term which is defined for each item in a glossary list. It */
/* is always followed by a :gd tag, which specifies the start of the text to define the term, */
/* and may only appear in a glossary list.                                                    */
/**********************************************************************************************/

void gml_gt( const gmltag * entry )
{
    return;
}

