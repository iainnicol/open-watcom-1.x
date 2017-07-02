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
* Description:  tags FIG, eFIG, FIGCAP, FIGDESC, and FIGREF
*
* Note: FIGLIST is defined in gdocsect.c
*       FIGREF is defined in gxxref.c
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include "wgml.h"
#include "gvars.h"

static  bf_place        place;                  // FIG attribute used by eFIG
static  bool            concat_save;            // for ProcFlags.concat
static  bool            figcap_done;            // FIGCAP done for current FIG
static  bool            page_width;             // FIG flag used by eFIG
static  bool            splitting;              // FIG is being split   
static  bool            t_page_width    = false;// FIG will actually go into page_width section
static  char            id[ID_LEN];             // FIG attribute used by eFIG
static  def_frame       frame;                  // FIG attribute used by eFIG
static  group_type      sav_group_type;         // save prior group type
static  ju_enum         justify_save;           // for ProcFlags.justify
static  uint32_t        depth           = 0;    // FIG attribute used by eFIG
static  uint32_t        spacing_save;           // for spacing
static  uint32_t        width           = 0;    // FIG attribute used by eFIG

/***************************************************************************/
/* Add text_char instances containing one bin_device->box.vertical_line    */
/* character to the left and right of the parameter                        */
/* This is only used with character devices                                */
/***************************************************************************/

static void add_risers( text_line * in_line )
{
    text_chars  *   riser;

    riser = alloc_text_chars( &bin_device->box.vertical_line, 1, bin_device->box.font );
    riser->width = 1;
    riser->x_address = t_page.cur_left;
    if( in_line->first != NULL ) {
        in_line->first->prev = riser;
        riser->next = in_line->first;
    }
    in_line->first = riser;

    riser = alloc_text_chars( &bin_device->box.vertical_line, 1, bin_device->box.font );
    riser->x_address = t_page.max_width - 1;
    riser->width = 1;
    if( in_line->last == NULL ) {
        riser->prev = in_line->first;
        in_line->first->next = riser;
    } else {
        riser->prev = in_line->last;
        in_line->last->next = riser;
    }
    in_line->last = riser;

    return;
}

/***************************************************************************/
/* Create a doc_element containting a box line                             */
/* This is only used when drawing the box with characters, not with PS     */
/* The box line text is in line_buff.text                                  */
/***************************************************************************/

static doc_element * get_box_line_el( void )
{
    doc_element *   cur_doc_el;

    cur_doc_el = alloc_doc_el( el_text );
    cur_doc_el->element.text.first = alloc_text_line();
    cur_doc_el->element.text.first->first =
            alloc_text_chars( line_buff.text, line_buff.current, bin_device->box.font );

    /* This may need additional work */

    cur_doc_el->element.text.first->first->width = line_buff.current;
    cur_doc_el->element.text.first->first->x_address = t_page.cur_left;
    cur_doc_el->element.text.first->line_height = wgml_fonts[bin_device->box.font].line_height;
    cur_doc_el->depth = wgml_fonts[bin_device->box.font].line_height;

    return( cur_doc_el );
}

/***************************************************************************/
/* Draw a box around the current box or box segment                        */
/* This function will use DBOX if that block is defined, and the BOX       */
/* characters if it is not                                                 */
/* NOTE: wgml 4.0 does something a bit different if the DBOX block is not  */
/*       defined but the HLINE block is; should such a device be added,    */
/*       this function will need to be adjusted to accomodate it           */
/* NOTE: use of FONT0 does not, in fact, match wgml 4.0 -- but since all   */
/*       wgml 4.0 does is the first LINEPASS for these items and since the */
/*       first LINEPASS invariably simply outputs the text, the effect is  */
/*       the same for character devices                                    */
/***************************************************************************/

static void draw_box( doc_el_group * in_group )
{
    doc_element *   cur_doc_el;
    doc_element *   sav_doc_el;
    int             i;
    text_line   *   cur_line;
    text_line   *   sav_line;

    if( bin_driver->dbox.text == NULL ) {           // DBOX not available
        line_buff.current = width;
        while( line_buff.current > line_buff.length ) {
            line_buff.length *= 2;
            line_buff.text = mem_realloc( line_buff.text, line_buff.length + 1 );
        }
        memset( line_buff.text, bin_device->box.horizontal_line, line_buff.current );
        line_buff.text[line_buff.current] = '\0';

        /* Finalize and insert the top box line */

        sav_doc_el = in_group->first;           // save original first element

        line_buff.text[0] = bin_device->box.top_left;
        line_buff.text[line_buff.current - 1] = bin_device->box.top_right;
        cur_doc_el = get_box_line_el();
        cur_doc_el->subs_skip = in_group->first->subs_skip;
        in_group->first->subs_skip = 0;
        cur_doc_el->top_skip = in_group->first->top_skip;
        in_group->first->top_skip = 0;

        cur_doc_el->next = in_group->first;
        in_group->first = cur_doc_el;
        in_group->depth += cur_doc_el->depth;

        /* Process lines inside figure */

        cur_doc_el = sav_doc_el;
        while( cur_doc_el != NULL ) {
            switch( cur_doc_el->type ) {
            // add code for other element types as appropriate
            case el_binc :
            case el_dbox :
            case el_graph :
            case el_hline :
            case el_vline :
                break;
            case el_text :

                /********************************************************/
                /* In reality, the box will have all text elements      */
                /* If the box has a non-zero depth, the first text      */
                /* element will have the depth in blank_lines and a     */
                /* blank text_line. Following elements will have        */
                /* text_lines which actually contain text               */
                /* If the box has zero depth, all text elements will    */
                /* have text_lines which actually contain text          */
                /********************************************************/

                if( cur_doc_el->blank_lines > 0 ) {
                    cur_line = cur_doc_el->element.text.first;
                    cur_line->line_height = wgml_fonts[bin_device->box.font].line_height;
                    add_risers( cur_line );
                    for( i = 1; i < cur_doc_el->blank_lines; i++ ) {
                        cur_line->next = alloc_text_line();
                        cur_line->next->line_height = wgml_fonts[bin_device->box.font].line_height;
                        add_risers( cur_line->next );
                        cur_line = cur_line->next;
                    }                
                    cur_doc_el->blank_lines = 0;
                } else {
                    if( cur_doc_el->subs_skip > 0 ) {
                        sav_line = cur_doc_el->element.text.first;
                        for( i = 0; i < cur_doc_el->subs_skip; i++ ) {
                            cur_line = alloc_text_line();
                            cur_line->line_height = wgml_fonts[bin_device->box.font].line_height;
                            add_risers( cur_line );
                            cur_line->next = cur_doc_el->element.text.first;
                            cur_doc_el->element.text.first = cur_line;
                        }
                        cur_doc_el->subs_skip = 0;
                        cur_line = sav_line;
                    } else {
                        cur_line = cur_doc_el->element.text.first;
                    }
                    while( cur_line != NULL ) {
                        add_risers( cur_line);
                        cur_line = cur_line->next;
                    }
                }
                break;
            default :
                internal_err( __FILE__, __LINE__ );
            }
            cur_doc_el = cur_doc_el->next;
        }

        /* Finalize and insert the bottom box line */

        line_buff.text[0] = bin_device->box.bottom_left;
        line_buff.text[line_buff.current - 1] = bin_device->box.bottom_right;
        cur_doc_el = get_box_line_el();
        in_group->last->next = cur_doc_el;
        in_group->last = in_group->last->next;
        in_group->depth += cur_doc_el->depth;
    } else {                                        // use DBOX
        cur_doc_el = alloc_doc_el( el_dbox );
        if( place == inline_place ) {
            if( !splitting ) {
                cur_doc_el->subs_skip += wgml_fonts[layout_work.fig.font].line_height;
            } else {
                cur_doc_el->subs_skip += wgml_fonts[FONT0].line_height;
            }
        } else {
            cur_doc_el->subs_skip = wgml_fonts[layout_work.fig.font].line_height;
        }
        cur_doc_el->element.dbox.h_start = t_page.cur_left;
        cur_doc_el->element.dbox.h_len = width;
        cur_doc_el->element.dbox.v_len = in_group->depth;
        if( (place == inline_place) ) {

            /****************************************************************/
            /* It appears that the initial blank line must be FONT0 for the */
            /* initial text line but must be the FIG's font for v_len       */
            /* But only if the figure is not being split                    */
            /* This, of course, makes no sense, but does match wgml 4.0     */
            /****************************************************************/

            if( !splitting ) {
                cur_doc_el->element.dbox.v_len -= wgml_fonts[FONT0].line_height;
                cur_doc_el->element.dbox.v_len += wgml_fonts[layout_work.fig.font].line_height;
            }
        } else {
            cur_doc_el->element.dbox.v_len += wgml_fonts[layout_work.fig.font].line_height;
        }
        if( place != inline_place ) {
            in_group->depth += (wgml_fonts[layout_work.fig.font].line_height +
                                wgml_fonts[FONT0].line_height);
        } else {
            in_group->depth += wgml_fonts[layout_work.fig.font].line_height;
        }
        in_group->last->next = cur_doc_el;
        in_group->last = in_group->last->next;
    }
    return;
}
/***************************************************************************/
/* Insert a rule or char line into the current doc_el_group                */
/* This function must check whether a rule or char line is needed and what */
/* its length should be                                                    */
/* It is only called when appropriate: so position need not be checked,    */
/* nor need frame be checked to avoid "none" or "box"                      */
/***************************************************************************/

static void insert_frame_line( void )
{
    doc_element *   h_line_el;
    int             i;
    size_t          cur_count;
    size_t          str_count;
    uint32_t        cur_limit;  // number of whole copies of frame.string that will fit into line.buff
    uint32_t        cur_width;
    uint32_t        str_width;

    if( bin_driver->hline.text == NULL ) {              // character device
        line_buff.current = width;
        while( line_buff.current > line_buff.length ) {
            line_buff.length *= 2;
            line_buff.text = mem_realloc( line_buff.text, line_buff.length + 1 );
        }
        if( frame.type == rule_frame ) {
            memset( line_buff.text, bin_device->box.horizontal_line, line_buff.current );
            line_buff.text[line_buff.current] = '\0';
        } else {                    // char_frame Note: wgml 4.0 uses font 0 regardless of the default font for the section
            line_buff.text[0] = '\0';
            str_count = strlen( frame.string );
            cur_limit = line_buff.current / str_count;  // number of complete strings that will fit
            cur_width = 0;
            for( i = 0; i < cur_limit; i++  ) {         // fill text with full string
                strcat_s( line_buff.text, line_buff.current + 1, frame.string );
                cur_width += strlen( frame.string );
            }
            if( cur_width < line_buff.current ) {       // text not full yet
                memcpy_s( &line_buff.text[cur_width], line_buff.current - cur_width,
                    frame.string, line_buff.current - cur_width );
            }
            line_buff.text[line_buff.current] = '\0';
        }
        process_text( line_buff.text, FONT0 );  // matches wgml 4.0
        scr_process_break();        // commit line
    } else {                                        // page-oriented device
        if( frame.type == rule_frame ) {

        /*******************************************************************/
        /* This uses code written originally for use with control word BX  */
        /* That control word uses depth to indicate the amount by which at */
        /* the vertical position is to be adjusted after the hline is      */
        /* emitted, as it appears in the middle of the normal line depth   */
        /* Here, the line appears at the bottom of the line depth, but the */
        /* depth used must be 0 to prevent the next element from being     */
        /* placed one line too far down on the page                        */
        /*******************************************************************/

            h_line_el = init_doc_el( el_hline, 0 );
            h_line_el->element.hline.ban_adjust = false;   // TBD, may not apply to FIG
            h_line_el->element.hline.h_start = t_page.cur_width;
            h_line_el->element.hline.h_len = width;
            insert_col_main( h_line_el );
        } else {                    // char_frame Note: wgml 4.0 uses font 0 regardless of the default font for the section
            str_count = strlen( frame.string );
            str_width = 0;
            for( i = 0; i < strlen( frame.string ); i++ ) {
                str_width += wgml_fonts[FONT0].width_table[(unsigned char)frame.string[i]];
            }
            cur_limit = width / str_width;
            cur_count = 0;
            cur_width = 0;
            line_buff.current = cur_limit;
            if( width % str_width > 0 ) {                   // partial copy will be needed
                line_buff.current++;
            }
            line_buff.current *= str_count;                 // length in characters
            while( line_buff.current > line_buff.length ) {
                line_buff.length *= 2;
                line_buff.text = mem_realloc( line_buff.text, line_buff.length + 1 );
            }
            line_buff.text[0] = '\0';
            for( i = 0; i < cur_limit; i++ ) {              // fill text with copies of full string
                strcat_s( line_buff.text, line_buff.current + 1, frame.string );
                cur_width += str_width;
                cur_count += str_count;
            }
            if( cur_width < width ) {       // text not full yet
                for( i = 0; i < strlen( frame.string ); i++ ) {
                    cur_width += wgml_fonts[FONT0].width_table[(unsigned char)frame.string[i]];
                    if( cur_width >= width ) {  // check what width would be if character were copied
                        break;
                    }
                    line_buff.text[cur_count] = frame.string[i];
                    cur_count++;
                }
            }
            line_buff.current = cur_count;
            line_buff.text[line_buff.current] = '\0';
            process_text( line_buff.text, FONT0 );  // matches wgml 4.0
            scr_process_break();        // commit line
        }
    }    
    return;
}


/***************************************************************************/
/*      :FIG [depth=�vert-space-unit�]                                     */
/*           [frame=box                                                    */
/*                  rule                                                   */
/*                  none                                                   */
/*                  �character string�]                                    */
/*           [id=�id-name�]                                                */
/*           [place=top                                                    */
/*                  bottom                                                 */
/*                  inline]                                                */
/*           [width=page                                                   */
/*                  column                                                 */
/*                  �hor-space-unit�].                                     */
/*           <paragraph elements>                                          */
/*           <basic document elements>                                     */
/* This tag signals the start of a figure. Each line of source text        */
/* following the figure tag is placed in the output document without       */
/* normal text processing. Spacing between words is preserved, and the     */
/* input text is not right justified. Input source lines which do not fit  */
/* on a line in the output document are split into two lines on a          */
/* character, rather than a word basis. A figure may be used where a basic */
/* document element is permitted, except within a figure, footnote, or     */
/* example. If the figure does not fit on the current page or column, it   */
/* is forced to the next one. If the current column is empty, the figure   */
/* will be split into two parts.                                           */
/***************************************************************************/

void gml_fig( const gmltag * entry )
{
    bool            id_seen = false;
    char        *   p;
    char        *   pa;
    ref_entry   *   cur_ref = NULL;
    su              cur_su;
    uint32_t        left_inset;
    uint32_t        right_inset;

    start_doc_sect();
    scr_process_break();
    scan_err = false;

    g_keep_nest( "Figure" );            // catch nesting errors

    figcap_done = false;                // reset for this FIG
    id[0] = '\0';
    page_width = false;
    p = scan_start;
    depth = 0;                          // default value; depth is space reserved for some other item
    frame.type = layout_work.fig.default_frame.type;
    if( frame.type == char_frame ) {
        strcpy_s( frame.string, str_size, layout_work.fig.default_frame.string );
    }
    width = t_page.last_pane->col_width;// default value regardless of number of columns
    g_curr_font = layout_work.fig.font;
    spacing_save = spacing;
    spacing = layout_work.fig.spacing;

    if( *p == '.' ) {
        /* already at tag end */
    } else {
        for( ;; ) {
            pa = get_att_start( p );
            p = att_start;
            if( ProcFlags.reprocess_line ) {
                break;
            }
            if( !strnicmp( "depth", p, 5 ) ) {
                p += 5;
                p = get_att_value( p );
                if( val_start == NULL ) {
                    break;
                }
                if( att_val_to_su( &cur_su, true ) ) {
                    break;
                }
                depth = conv_vert_unit( &cur_su, spacing, g_curr_font );
                if( ProcFlags.tag_end_found ) {
                    break;
                }
            } else if( !strnicmp( "frame", p, 5 ) ) {
                p += 5;
                p = get_att_value( p );
                if( val_start == NULL ) {
                    break;
                }
                if( !strnicmp( "none", val_start, 4 ) ) {
                    frame.type = none;
                } else if( !strnicmp( "box", val_start, 3 ) ) {
                    frame.type = box_frame;
                } else if( !strnicmp( "rule", val_start, 4 ) ) {
                    frame.type = rule_frame;
                } else {
                    frame.type = char_frame;
                }
                if( frame.type == char_frame ) {
                    memcpy_s( frame.string, str_size, val_start, val_len );
                    if( val_len < str_size ) {
                        frame.string[val_len] = '\0';
                    } else {
                        frame.string[str_size - 1] = '\0';
                    }
                    if( strnlen_s( frame.string, str_size ) == 0 ) {
                        frame.type = none;      // treat null string as "none"
                    }
                } else {                        // blank any existing frame.string value
                    frame.string[0] = '\0';
                }
                if( ProcFlags.tag_end_found ) {
                    break;
                }
            } else if( !strnicmp( "id", p, 2 ) ) {
                p += 2;
                p = get_refid_value( p, id );
                if( val_start == NULL ) {
                    break;
                }
                id_seen = true;             // valid id attribute found
                if( ProcFlags.tag_end_found ) {
                    break;
                }
            } else if( !strnicmp( "place", p, 5 ) ) {
                p += 5;
                p = get_att_value( p );
                if( val_start == NULL ) {
                    break;
                }
                if( !strnicmp( "bottom", val_start, 5 ) ) {
                    place = bottom_place;
                } else if( !strnicmp( "inline", val_start, 6 ) ) {
                    place = inline_place;
                } else if( !strnicmp( "top", val_start, 3 ) ) {
                    place = top_place;
                } else {
                    xx_line_err( err_inv_att_val, val_start );
                }
                if( ProcFlags.tag_end_found ) {
                    break;
                }
            } else if( !strnicmp( "width", p, 5 ) ) {
                p += 5;
                p = get_att_value( p );
                if( val_start == NULL ) {
                    break;
                }
                if( !strnicmp( "page", val_start, 4 ) ) {
                    // this will be used to set t_page_width and width below 
                    page_width = true;
                } else if( !strnicmp( "column", val_start, 6 ) ) {
                    // default value is the correct value to use
                } else {    // value actually specifies the width
                    pa = val_start;
                    if( att_val_to_su( &cur_su, true ) ) {
                        break;
                    }
                    width = conv_hor_unit( &cur_su, g_curr_font );
                    if( width == 0 ) {
                        xx_line_err( err_inv_width_fig_1, val_start );
                    }
                }
                if( ProcFlags.tag_end_found ) {
                    break;
                }
            } else {    // no match = end-of-tag in wgml 4.0
                p = pa; // restore spaces before text
                break;
            }
        }
    }

    set_skip_vars( &layout_work.fig.pre_skip, NULL, NULL, spacing, g_curr_font );

    /* Only page-width top figs on multi-column pages actually go into the page_width section */

    t_page_width = (place == top_place) && (page_width) && (t_page.last_pane->col_count > 1);

    /* For an inline dbox, the actual skip must be done before the box itself */

    if( place == inline_place ) {
        if( (frame.type == box_frame) && (bin_driver->dbox.text != NULL) ) {
            g_blank_lines += g_subs_skip;
            g_subs_skip = 0;
            scr_process_break();
        }
    }

    init_nest_cb();
    nest_cb->p_stack = copy_to_nest_stack();
    nest_cb->left_indent = conv_hor_unit( &layout_work.fig.left_adjust, g_curr_font );
    nest_cb->right_indent = conv_hor_unit( &layout_work.fig.right_adjust, g_curr_font );
    nest_cb->lm = t_page.cur_left;
    nest_cb->rm = t_page.max_width;
    nest_cb->font = g_curr_font;
    nest_cb->c_tag = t_FIG;

    sav_group_type = cur_group_type;
    cur_group_type = gt_fig;
    cur_doc_el_group = alloc_doc_el_group( gt_fig );
    cur_doc_el_group->next = t_doc_el_group;
    t_doc_el_group = cur_doc_el_group;
    cur_doc_el_group = NULL;

    concat_save = ProcFlags.concat;
    ProcFlags.concat = false;
    justify_save = ProcFlags.justify;
    ProcFlags.justify = ju_off;

    /* Only create the entry on the first pass */

    if( pass == 1 ) {                   // add this FIG to fig_list
        fig_entry = init_ffh_entry( fig_list );
        fig_entry->flags = ffh_fig;     // mark as FIG
        if( fig_list == NULL ) {        // first entry
            fig_list = fig_entry;
        }
        if( id_seen ) {                 // add this entry to fig_ref_dict
            cur_ref = find_refid( fig_ref_dict, id );
            if( cur_ref == NULL ) {             // new entry
                cur_ref = (ref_entry *) mem_alloc( sizeof( ref_entry ) ) ;
                init_ref_entry( cur_ref, id );
                cur_ref->flags = rf_ffh;
                cur_ref->entry = fig_entry;
                add_ref_entry( &fig_ref_dict, cur_ref );
            } else {                // duplicate id
                dup_id_err( cur_ref->id, "figure" );
            }
        }
    }

    left_inset = 0;
    right_inset = 0;
    if( frame.type == none ) {
        width -= nest_cb->right_indent;
        right_inset = nest_cb->right_indent;
        if( ProcFlags.has_aa_block ) {      // matches wgml 4.0
            width -= tab_col;
        }
    } else {
        width -= (nest_cb->left_indent + nest_cb->right_indent);
        if( ProcFlags.has_aa_block ) {      // matches wgml 4.0
            left_inset = wgml_fonts[FONT0].line_height + 1;
            right_inset = wgml_fonts[FONT0].line_height + 1 + tab_col;
        } else {
            left_inset = 2 * tab_col;
            right_inset = 2 * tab_col;
        }
    }

    /* This sets text processing up for page width text */

    if( t_page_width ) {
        t_page.max_width = t_page.page_width;
        width = t_page.page_width;
    }

    /* This is for the overall figure, including any frame */

    t_page.cur_left += nest_cb->left_indent;
    t_page.cur_width = t_page.cur_left;

    if( width > t_page.last_pane->col_width ) {
        if( (t_page.last_pane->col_count > 1) && (place != top_place) ) {
            xx_line_err( err_inv_width_fig_2, val_start );
        } else if( t_page.last_pane->col_count == 1 ) {
            xx_line_err( err_inv_width_fig_3, val_start );
        }
    }

    if( (t_page.cur_left >= t_page.max_width) || (t_page.cur_left >= g_page_right_org) ) {
        if( frame.type == none ) {
            xx_line_err( err_inv_margins_1, val_start );
        } else {
            xx_line_err( err_inv_margins_2, val_start );
        }
    }

    t_page.cur_width = t_page.cur_left;
    ProcFlags.keep_left_margin = true;  // keep special indent

    if( (place != top_place) &&
            ((frame.type == rule_frame) || (frame.type == char_frame)) ) {
        if( (frame.type == rule_frame) && (bin_driver->hline.text != NULL)
                && (place == inline_place) ) {
            g_subs_skip += wgml_fonts[FONT0].line_height;   // this is actually the depth used by the HLINE
            g_top_skip += wgml_fonts[FONT0].line_height;    // for use if fig moved to top of next page
        }
        insert_frame_line();
    }

    if( (frame.type == none) && (place != bottom_place) ) {
        if( depth > g_subs_skip ) {
            g_blank_lines = depth;
            g_subs_skip = 0;
            scr_process_break();
        }
    } else {
        g_blank_lines = depth;      
        scr_process_break();
    }

    /* Now set up margins for any text inside the figure */  

    t_page.cur_left += left_inset;

    if( t_page.max_width < right_inset ) {
        t_page.max_width = 0;               // negative right margin not allowed
        if( frame.type == none ) {
            xx_line_err( err_inv_margins_1, val_start );
        } else {
            xx_line_err( err_inv_margins_2, val_start );
        }
    } else {
        t_page.max_width -= right_inset;
    }

    t_page.cur_width = t_page.cur_left;
    ProcFlags.keep_left_margin = true;  // keep special indent

    if( !ProcFlags.reprocess_line && *p ) {
        if( *p == '.' ) p++;                // possible tag end
        if( *p ) {
            process_text( p, g_curr_font); // if text follows
        }
    }
    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/*      :eFIG.                                                             */
/* This tag signals the end of a figure. A corresponding :fig tag must be  */
/* previously specified for each :efig tag.                                */
/***************************************************************************/

void gml_efig( const gmltag * entry )
{
    bool                splittable;
    bool                split_done;
    char            *   p;
    doc_el_group    *   cur_group;              // current group from n_page, not cur_doc_el_group
    doc_el_group    *   new_group;              // new group for use in splitting cur_doc_el_group
    doc_element     *   cur_el;
    doc_element     *   next_el;
    tag_cb          *   wk;
    uint32_t            bias;
    uint32_t            cur_depth;
    uint32_t            page_pred;
    uint32_t            raw_p_skip;

    scr_process_break();
    rs_loc = 0;

    /* Done here because needed for the minimum post_skip */
    
    p = scan_start;
    if( *p == '.' ) p++;                    // possible tag end

    if( cur_group_type != gt_fig ) {       // no preceding :FIG tag
        g_err_tag_prec( "FIG" );
    }

    t_page.cur_left = nest_cb->left_indent; // reset various values
    t_page.max_width = width;
    t_page.cur_width = 0;
    ProcFlags.concat = false;

    set_skip_vars( NULL, NULL, &layout_work.fig.post_skip, spacing, layout_work.fig.font );

    raw_p_skip = g_post_skip;           // save for future use

    /*******************************************************************/
    /* t_doc_el_group->post_skip set here will only be used on the     */
    /* current page because, for other top figures, it is reset below  */
    /* Note: a post_skip of 1 is treated the same as a post_skip of 0  */
    /*       but the test for "1" must be the font line height         */
    /*******************************************************************/

    if( (g_post_skip == 0) ||
            (g_post_skip == wgml_fonts[layout_work.fig.font].line_height) ) {
        if( *p ) {
            g_post_skip = wgml_fonts[FONT0].line_height;
        }
        if( place == top_place ) {                      // top fig only
            t_doc_el_group->post_skip = wgml_fonts[FONT0].line_height;
        }
    } else {
        t_doc_el_group->post_skip = g_post_skip;
    }

    if( (place != bottom_place) &&
            ((frame.type == rule_frame) || (frame.type == char_frame)) ) {
        if( (frame.type == rule_frame) && (bin_driver->hline.text != NULL) ) {
            g_subs_skip += wgml_fonts[layout_work.fig.font].line_height; // this is actually the depth used by the HLINE
        }
        insert_frame_line();
    }

    if( (place == inline_place) &&
            (frame.type == box_frame) && (bin_driver->dbox.text != NULL) ) {
        t_doc_el_group->first->subs_skip += wgml_fonts[FONT0].line_height;
        t_doc_el_group->depth += wgml_fonts[FONT0].line_height;
    }

    ProcFlags.skips_valid = false;      // activate post_skip for next element

    if( (strlen( id ) > 0) && !figcap_done ) {  // FIG id requires FIGCAP
        xx_err( err_fig_id_cap );
    }

    /* Place the accumulated lines on the proper page */

    cur_group_type = sav_group_type;
    if( t_doc_el_group != NULL) {
        page_pred = page + 1;                   // initialize to current page 
        cur_doc_el_group = t_doc_el_group;      // detach current element group
        t_doc_el_group = t_doc_el_group->next;  // processed doc_elements go to next group, if any
        cur_doc_el_group->next = NULL;

        if( place == inline_place ) {       // inline
            split_done = false;
            while( (cur_doc_el_group != NULL) && (cur_doc_el_group->first != NULL) ) {
                splitting = false;
                if( frame.type == box_frame ) {
                    if( bin_driver->dbox.text != NULL ) {   // DBOX available
                        bias = wgml_fonts[FONT0].line_height;
                        cur_doc_el_group->first->top_skip = wgml_fonts[FONT0].line_height; // this is actually the depth used by the HLINE
                    } else {
                        bias = wgml_fonts[layout_work.fig.font].line_height +
                                                        wgml_fonts[FONT0].line_height;
                    }
                } else {
                    bias = 0;
                }
                if( (cur_doc_el_group->depth + t_page.cur_depth + bias)
                        > t_page.max_depth ) {

                    /* the block won't fit on this page */

                    last_page_out();
                    reset_t_page();
                    page_pred++;        // update to page FIG ends on

                    if( (cur_doc_el_group->depth + bias) <= t_page.max_depth ) {

                        /* the block will be on the next page */

                        if( frame.type == box_frame ) {

                            /* Last part of split box */

                            if( split_done ) {
                                cur_doc_el_group->depth += wgml_fonts[FONT0].line_height;
                                split_done = false;
                            }
                            draw_box(cur_doc_el_group);
                        }
                        while( cur_doc_el_group->first != NULL ) {
                            cur_el = cur_doc_el_group->first;
                            cur_doc_el_group->first = cur_doc_el_group->first->next;
                            cur_el->next = NULL;
                            insert_col_main( cur_el );
                        }
                    } else {

                        /* the block won't fit on any page */
                    
                        /* first split the block */

                        splitting = true;
                        split_done = true;
                        cur_depth = 0;
                        new_group = alloc_doc_el_group( gt_fig );
                        while( cur_doc_el_group->first != NULL ) {
                            cur_el = cur_doc_el_group->first;
                            cur_doc_el_group->first = cur_doc_el_group->first->next;
                            cur_el->next = NULL;
                            cur_depth = cur_el->blank_lines + cur_el->subs_skip + cur_el->depth;
                            if( cur_depth <= (t_page.max_depth - (new_group->depth + bias)) ) { 

                                /* the element will fit on this page */

                                if( new_group->first == NULL ) {
                                    new_group->first = cur_el;
                                } else {
                                    new_group->last->next = cur_el;
                                }
                                new_group->last = cur_el;
                                new_group->depth += cur_depth;
                                cur_doc_el_group->depth -= cur_depth;
                            } else {
                            
                                /* the element must be split */

                                splittable = split_element( cur_el, t_page.max_depth -
                                                    (new_group->depth + bias) );
                                next_el = cur_el->next;
                                cur_el->next = NULL;
                                if( splittable && (next_el != NULL) ) {     // cur_el was split
                                    if( new_group->first == NULL ) {
                                        new_group->first = cur_el;
                                    } else {
                                        new_group->last->next = cur_el;
                                    }
                                    new_group->last = cur_el;
                                    next_el->next = cur_doc_el_group->first;
                                    cur_doc_el_group->first = next_el;
                                    cur_doc_el_group->last = next_el;
                                    while( cur_doc_el_group->last->next != NULL ) {
                                        cur_doc_el_group->last = cur_doc_el_group->last->next;
                                    }
                                    new_group->depth += cur_el->depth;
                                    cur_doc_el_group->depth -= cur_el->depth;
                                } else {    // cur_el must go on next page
                                    cur_el->next = cur_doc_el_group->first;
                                    cur_doc_el_group->first = cur_el;
                                }
                                break;
                            }
                        }
                        if( new_group != NULL ) {
                            new_group->next = cur_doc_el_group;
                            cur_doc_el_group = new_group;
                            new_group = NULL;
                        }

                        /* then output the part that fits */

                        if( frame.type == box_frame ) {
                            draw_box(cur_doc_el_group);
                        }
                        while( cur_doc_el_group->first != NULL ) {
                            cur_el = cur_doc_el_group->first;
                            cur_doc_el_group->first = cur_doc_el_group->first->next;
                            cur_el->next = NULL;
                            insert_col_main( cur_el );
                        }
                        cur_group = cur_doc_el_group;
                        cur_doc_el_group = cur_doc_el_group->next;
                        cur_group->next = NULL;
                        add_doc_el_group_to_pool( cur_group );
                        cur_group = NULL;
                    }
                } else {
                    if( frame.type == box_frame ) {
                        draw_box(cur_doc_el_group);
                    }
                    while( cur_doc_el_group->first != NULL ) {
                        cur_el = cur_doc_el_group->first;
                        cur_doc_el_group->first = cur_doc_el_group->first->next;
                        cur_el->next = NULL;
                        insert_col_main( cur_el );
                    }
                }
            }
            add_doc_el_group_to_pool( cur_doc_el_group );
            cur_doc_el_group = NULL;
        } else {

            /*************************************************************/
            /* blank_lines and the skips of the first doc_element are    */
            /*   used with the next doc_element (if frame is not "none") */
            /* the skips of the first doc_element are used with the next */
            /*   doc_element                                             */
            /* the doc_el_group depth was computed with these values,    */
            /*   and so must be reduced by them as well                  */
            /*************************************************************/

            if( frame.type != none ) {
                g_blank_lines = cur_doc_el_group->first->blank_lines;
                cur_doc_el_group->first->blank_lines = 0;
                cur_doc_el_group->depth -= g_blank_lines;
            }
            g_subs_skip = cur_doc_el_group->first->subs_skip;
            cur_doc_el_group->first->subs_skip = 0;
            cur_doc_el_group->depth -= g_subs_skip;
            if( raw_p_skip > 0 ) {         // reset to default post_skip
                g_post_skip = wgml_fonts[FONT0].line_height;
                if( raw_p_skip == wgml_fonts[FONT0].line_height ) {
                    raw_p_skip = wgml_fonts[layout_work.fig.font].line_height;
                }
            }

            /* box drawn by dbox requires special handling */

            if( (frame.type == box_frame)
                    && (bin_driver->dbox.text != NULL) ) {
                cur_doc_el_group->first->blank_lines = wgml_fonts[FONT0].line_height; // this is actually the depth used by the HLINE
            }

            /* top rule in a bottom fig requires special handling */

            if( (place == bottom_place) && (frame.type == rule_frame) ) {
                cur_doc_el_group->first->subs_skip = wgml_fonts[FONT0].line_height; // this is actually the depth used by the HLINE
                cur_doc_el_group->depth += wgml_fonts[FONT0].line_height; // this is actually the depth used by the HLINE
            }
            g_top_skip = cur_doc_el_group->first->top_skip;
            cur_doc_el_group->first->top_skip = 0;

            if( frame.type == box_frame ) {
                draw_box(cur_doc_el_group);
            }

            cur_group = NULL;
            if( place == bottom_place ) {       // bottom
                insert_col_bot( cur_doc_el_group );
                cur_group = n_page.col_bot;
            } else {
                if( t_page_width ) {
                    insert_page_width( cur_doc_el_group );
                    cur_group = n_page.page_width;
                } else {          // width was "column" at most and page is multi-column
                    insert_col_width( cur_doc_el_group );
                    cur_group = n_page.col_width;
                }
            }

            /************************************************************/
            /* 1. The destinations (t_page.page_width, t_page.cols->    */
            /*    col_width, t_page.cols->col_bot) take one item only   */
            /* 2. If the destination was empty, then the figure just    */
            /*    submitted went into it and is on the current page     */
            /* 3. If the destination was full, then the figure just     */
            /*    submitted went into n_page->page_width, or n_page->   */
            /*    col_width, or n_page->col_bot and is the last item    */
            /* 4. Each item in the n_page sections will go onto a new   */
            /*    page whose number can be computed from the number     */
            /*    of items in the list plus the current page number     */
            /* NOTE: no attempt is made at this time to divide these    */
            /*    FIG/eFIG blocks, as that may force some or all of     */
            /*    figure processing into docpage.c (the insert_x()      */
            /*    functions and update_t_page()).                       */
            /************************************************************/

            while( cur_group != NULL ) {
                page_pred++;            // set to future page of top FIG
                cur_group = cur_group->next;
            }

            /************************************************************/
            /* This value is used after figs at the top of subsequent   */
            /* pages only: cur_doc_el_group has already been submitted  */
            /* and, if on the current page, its post_skip already       */
            /* copied                                                   */
            /************************************************************/

            if( (page_pred > (page + 1)) && (place == top_place) ) {
                cur_doc_el_group->post_skip = raw_p_skip;
            }
        }
        if( pass == 1 ) {
            fig_entry->pageno = page_pred;
        } else {
            if( page_pred != fig_entry->pageno ) {  // page number changed
                fig_entry->pageno = page_pred;
                if( GlobalFlags.lastpass ) {        // last pass only
                    if( strlen( id ) > 0 ) {     // FIG id exists
                        fig_fwd_refs = init_fwd_ref( fig_fwd_refs, id );
                    }
                    ProcFlags.new_pagenr = true;
                }
            }
        }
    }

    ProcFlags.concat = concat_save;
    ProcFlags.justify = justify_save;
    t_page.cur_left = nest_cb->lm;
    t_page.max_width = nest_cb->rm;

    wk = nest_cb;
    nest_cb = nest_cb->prev;
    add_tag_cb_to_pool( wk );

    g_curr_font = nest_cb->font;

    t_page.cur_width = t_page.cur_left;

    scan_err = false;
    if( *p ) {
        process_text( p, g_curr_font);  // if text follows
    }
    if( place == t_page_width ) {
        t_page.max_width = t_page.last_pane->col_width;
    }
    if( pass > 1 ) {                    // not on first pass
        fig_entry = fig_entry->next;    // get to next FIG
    }
    spacing = spacing_save;
    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/*      :FIGCAP.<text line>                                                */
/* The figure caption tag is used within a figure to specify the caption   */
/* for the figure. The figure caption tag must be specified if the figure  */
/* has an identifier name associated with it. Layout defined text followed */
/* by the figure number and a delimiter is inserted before the caption     */
/* text (the default text and delimiter is "Figure" and a period). The     */
/* figure caption follows the main text of the figure.                     */
/***************************************************************************/

void gml_figcap( const gmltag * entry )
{
    char            buffer[11];
    char        *   prefix;
    char        *   p;
    size_t          count;
    size_t          current;

    start_doc_sect();
    scr_process_break();
    rs_loc = figcap_tag;

    scan_err = false;
    p = scan_start;

    g_curr_font = layout_work.figcap.string_font;
    set_skip_vars( &layout_work.figcap.pre_lines, NULL, NULL, spacing, g_curr_font );

    input_cbs->fmflags &= ~II_eol;      // prefix is never EOL
    if( pass == 1 ) {                   // only on the first pass

        /* Only FIGs with captions are numbered */

        fig_count++;
        fig_entry->number = fig_count;

        /* Now build, save, and output the prefix */

        count = strlen(&layout_work.figcap.string);
        ultoa( fig_entry->number, &buffer, 10 );
        count += strlen(&buffer);
        count ++;                       // for the delimiter character
        prefix = (char *) mem_alloc( count + 1);
        strcpy_s( prefix, count, &layout_work.figcap.string);
        current = strlen( prefix );
        strcat_s( &prefix[current], count - current, &buffer);
        current = strlen( prefix );
        prefix[current] = layout_work.figcap.delim;
        prefix[current + 1] = '\0';
        fig_entry->prefix = prefix;
        process_text( prefix, g_curr_font );
        prefix = NULL;
    } else {                            // use existing prefix
        process_text( fig_entry->prefix, g_curr_font );
    }

    /* Output the caption text, if any */

    t_page.cur_left += (t_line->last->width + wgml_fonts[g_curr_font].spc_width );
    if( ProcFlags.has_aa_block ) {          // matches wgml 4.0
        t_page.max_width += tab_col;
    }
    t_page.cur_width = t_page.cur_left;
    g_curr_font = layout_work.figcap.font;
    if( *p ) {
        if( *p == '.' ) p++;                // possible tag end
        while( *p == ' ' ) p++;             // skip preceding spaces
        ProcFlags.concat = true;            // even if was false on entry
        post_space = 0;                     // g_curr_left should be enough
        input_cbs->fmflags &= ~II_sol;      // prefix was SOL, so this is not
        if( pass == 1 ) {                   // only on first pass
            current = strlen( p );
            fig_entry->text = (char *) mem_alloc( current + 1);
            strcpy_s(fig_entry->text, current + 1, p );
        }
        process_text( p, g_curr_font );     // if text follows
    }
    fig_entry->flags |= ffh_figcap;         // mark as FIGCAP present, with or without text
    figcap_done = true;

    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/*      :FIGDESC.<paragraph elements>                                      */
/*               <basic document elements>                                 */
/* This tag signals the start of the description for a figure. The tag is  */
/* placed after the optional :figcap tag within a figure. The GML          */
/* processor automatically adds a colon(:) following the caption when a    */
/* figure description is present.                                          */
/***************************************************************************/

void gml_figdesc( const gmltag * entry )
{
    char    *   p;

    start_doc_sect();
    rs_loc = 0;

    scan_err = false;
    p = scan_start;

    if( figcap_done ) {                         // FIGCAP was present
        post_space = 0;
        ProcFlags.ct = true;                    // emulate CT
        input_cbs->fmflags &= ~II_eol;          // ":" is never EOL
        process_text( ":", g_curr_font);        // uses FIGCAP font
        g_curr_font = layout_work.figdesc.font; // change to FIGDESC font
    } else {                                    // FIGCAP not present
        scr_process_break();                    
        if( ProcFlags.has_aa_block ) {          // matches wgml 4.0
            t_page.max_width += tab_col;
        }
        g_curr_font = layout_work.figdesc.font;
        set_skip_vars( &layout_work.figdesc.pre_lines, NULL, NULL, spacing, g_curr_font );
    }

    nest_cb->font = g_curr_font;        // support font changes inside description

    if( *p == '.' ) p++;                // possible tag end
    if( *p ) {
        ProcFlags.concat = true;        // even if was false on entry
        process_text( p, g_curr_font);  // if text follows
    } else {
        if( !figcap_done ) {            // if no FIGCAP was present
            g_blank_lines += g_subs_skip;
            g_subs_skip = 0;
            scr_process_break();
        }
    }
    scan_start = scan_stop + 1;
    return;
}

