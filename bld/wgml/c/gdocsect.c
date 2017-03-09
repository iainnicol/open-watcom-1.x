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
* Description:  WGML tags and routines for document section changes
*                    :GDOC, :FRONTM, :BODY, ...
*               and special for :INDEX tag
****************************************************************************/
#include    "wgml.h"
#include    "gvars.h"

static  bool        concat_save;                // for ProcFlags.concat
static  int32_t     save_indent     =0;         // used with TITLEP/eTITLEP
static  int32_t     save_indentr    =0;         // used with TITLEP/eTITLEP
static  ju_enum     justify_save;               // for ProcFlags.justify
static  line_number titlep_lineno   =0;         // TITLEP tag line number

/***************************************************************************/
/*  error routine for wrong sequence of doc section tags                   */
/***************************************************************************/

static void g_err_doc_sect( doc_section  ds )
{
    static  char const  sect[14][9] =
        {                               // same sequence as doc_section enum
            "NONE",
            "GDOC",
            "FRONTM",
            "TITLEP",
            "eTITLEP",
            "ABSTRACT",
            "PREFACE",
            "TOC",
            "FIGLIST",
            "BODY",
            "APPENDIX",
            "BACKM",
            "INDEX",
            "eGDOC"
        };

    err_count++;
    scan_err = true;
    g_err( err_doc_sect, sect[ds] );
    file_mac_info();
}

/***************************************************************************/
/*  set banner pointers for specified doc section                          */
/***************************************************************************/

void set_section_banners( doc_section ds )
{
    banner_lay_tag  * ban;

    /***********************************************************************/
    /*  transform doc_section enum into ban_doc_sect enum                  */
    /***********************************************************************/

    static const ban_docsect sect_2_bansect[doc_sect_egdoc + 1] = {

        no_ban,                         // doc_sect_none,
        no_ban,                         // doc_sect_gdoc,
        no_ban,                         // doc_sect_frontm,
        no_ban,                         // doc_sect_titlep,
        no_ban,                         // doc_sect_etitlep,
        abstract_ban,                   // doc_sect_abstract,
        preface_ban,                    // doc_sect_preface,
        toc_ban,                        // doc_sect_toc,
        figlist_ban,                    // doc_sect_figlist,
        body_ban,                       // doc_sect_body,
        appendix_ban,                   // doc_sect_appendix,
        backm_ban,                      // doc_sect_backm,
        index_ban,                      // doc_sect_index,
        no_ban                          // doc_sect_egdoc
    };

/* not yet coded banner place values               TBD
               not all are document section related
    head0_ban,
    head1_ban,
    head2_ban,
    head3_ban,
    head4_ban,
    head5_ban,
    head6_ban,
    letfirst_ban,
    letlast_ban,
    letter_ban,
    max_ban
} ban_docsect;
****************/

    sect_ban_top[0] = sect_ban_top[1] = NULL;
    sect_ban_bot[0] = sect_ban_bot[1] = NULL;

    if( no_ban != sect_2_bansect[ds]  ) {

        for( ban = layout_work.banner; ban != NULL; ban = ban->next ) {
            if( ban->docsect == sect_2_bansect[ds] ) {  // if our doc section
                switch( ban->place ) {
                case   top_place :
                    sect_ban_top[0] = ban;
                    sect_ban_top[1] = ban;
                    break;
                case   bottom_place :
                    sect_ban_bot[0] = ban;
                    sect_ban_bot[1] = ban;
                    break;

                case   topodd_place :
                    sect_ban_top[1] = ban;
                    break;
                case   topeven_place :
                    sect_ban_top[0] = ban;
                    break;

                case   botodd_place :
                    sect_ban_bot[1] = ban;
                    break;
                case   boteven_place :
                    sect_ban_bot[0] = ban;
                    break;
                default:
                    break;
                }
            }
        }
    }
}

/***************************************************************************/
/*  this function sets up tabbing for the fill-string and page number in   */
/*  the PAGELIST or TOC.                                                   */
/*  Since TB only supports fill chars, only the first character of fill    */
/*  will actually be used                                                  */
/***************************************************************************/

static void figlist_toc_tabs( char * fill, uint32_t size )
{

    /* Set tab char to "$" */

    tab_char = '$';
    add_to_sysdir( "$tb", tab_char );
    add_to_sysdir( "$tab", tab_char );

    /********************************************************/
    /* Set the tab stops                                    */
    /* the one-column shift is normal                       */
    /* g_page_left is added back in when tabbing is done    */
    /********************************************************/

    user_tabs.current = 2;
    user_tabs.tabs[0].column = g_page_right - tab_col - g_page_left - size;
    user_tabs.tabs[0].fill_char = fill[0];
    user_tabs.tabs[0].alignment = al_right;

    user_tabs.tabs[1].column = g_page_right - tab_col - g_page_left;
    user_tabs.tabs[1].fill_char = ' ';
    user_tabs.tabs[1].alignment = al_right;

    return;    
}

/***************************************************************************/
/*  output FIGLIST                                                         */
/***************************************************************************/

static void gen_figlist( void )
{
    char            buffer[11];
    char            postfix[12];
    ffh_entry   *   curr;
    uint32_t        size;

    if( fig_list == NULL ) return;  // no fig_list, no FIGLIST

    /* Insert FIGLIST into current section */

    last_page_out();                // ensure are on new page
    g_skip = 0;                     // ignore remaining skip value
    set_section_banners( doc_sect_figlist );
    reset_t_page();

    /* Set FIGLIST margins and other values */

    g_page_left = g_page_left_org + 2 *
                  conv_hor_unit( &layout_work.figlist.left_adjust, g_curr_font );    // matches wgml 4.0
    g_page_right = g_page_right_org -
                   conv_hor_unit( &layout_work.figlist.right_adjust, g_curr_font );
    size = conv_hor_unit( &layout_work.flpgnum.size, g_curr_font );  // space from fill to right edge
    figlist_toc_tabs( layout_work.figlist.fill_string, size );

    /* Output FIGLIST */

    concat_save = ProcFlags.concat;
    ProcFlags.concat = true;
    justify_save = ProcFlags.justify;
    ProcFlags.justify = ju_off;
    ProcFlags.keep_left_margin = true;  // keep all indents while outputting text
    curr = fig_list;
    while( curr != NULL ) {
        if( curr->flags & ffh_figcap ) {    // no FIGCAP used, no FIGLIST output
            g_curr_font = FONT0;            // wgml 4.0 uses font 0
            if( ProcFlags.page_started ) {  // not on first entry
                spacing = layout_work.figlist.spacing;
                set_skip_vars( NULL, NULL, NULL, spacing, g_curr_font );
            }
            g_cur_left = g_page_left;
            g_cur_h_start = g_cur_left;
            process_text( curr->prefix, g_curr_font );  // caption prefix

            if( curr->text != NULL ) {
                g_cur_left = t_line->last->x_address + t_line->last->width +
                             wgml_fonts[g_curr_font].spc_width;
                g_cur_h_start = g_cur_left;
                ProcFlags.ct = true;                // emulate CT
                ProcFlags.stop_xspc = true;         // suppress 2nd space after stops
                post_space = 0;
                g_page_right -= size;
                if( ProcFlags.has_aa_block ) {      // matches wgml 4.0
                    g_page_right -= tab_col;
                } else {
                    g_page_right -= 3 * tab_col;
                }
                if( !ProcFlags.page_started ) {     // first entry wrapping
                    spacing = layout_work.figlist.spacing;
                }
                set_skip_vars( &layout_work.figlist.skip, NULL, NULL,
                               spacing, g_curr_font );
                process_text( curr->text, g_curr_font );// caption text
                if( ProcFlags.has_aa_block ) {       // matches wgml 4.0
                    g_page_right += tab_col;
                } else {
                    g_page_right += 3 * tab_col;
                }
                g_page_right += size;
            }
            ProcFlags.ct = true;                    // emulate CT
            g_curr_font = FONT0;
            process_text( "$", g_curr_font );
            format_num( curr->pageno, &buffer, sizeof( buffer ), curr->style );
            strcpy_s( postfix, 12, "$" );           // insert tab characters
            strcat_s( postfix, 12, buffer );        // append page number
            g_curr_font = layout_work.flpgnum.font;
            process_text( postfix, g_curr_font );
        }
        scr_process_break();                // ensure line break
        curr = curr->next;
    }

    ProcFlags.concat = concat_save;
    ProcFlags.justify = justify_save;

    /* Re-establish current section */

    last_page_out();                // ensure all pages output
    set_section_banners( ProcFlags.doc_sect );
    reset_t_page();

    return;
}

/***************************************************************************/
/*  output INDEX                                                           */
/***************************************************************************/

static void gen_index( void )
{
    char            buffer[11];
    char            letter[2];
    ix_h_blk    *   ixh1;
    ix_h_blk    *   ixh2;
    ix_h_blk    *   ixh3;
    ix_e_blk    *   ref;
    symsub      *   ixrefval;       // &sysixref value

    if( index_dict == NULL ) return;    // no index_dict, no INDEX

    scr_process_break();                // flush any pending text
    start_doc_sect();

    letter[0]  = 0;
    letter[1]  = 0;
    ixh1 = index_dict;
    find_symvar( &sys_dict, "$ixref", no_subscript, &ixrefval);

    while( ixh1 != NULL ) {             // level 1


        if( letter[0] != toupper( *(ixh1->ix_term) ) ) {

            /* Set g_subs_skip for next IXHEAD */

            set_skip_vars( NULL, &layout_work.ixhead.pre_skip,
                           NULL, spacing, 
                           layout_work.ixhead.font );

            /* Generate IXHEAD heading */

            letter[0] = toupper( *(ixh1->ix_term) );
            if( layout_work.ixhead.header == true ) {
                process_text( letter, layout_work.ixhead.font );
                scr_process_break();        // flush letter heading
            }
        }

        if( ixh1->prt_term == NULL ) {
            process_text( ixh1->ix_term, g_curr_font );
        } else {
            process_text( ixh1->prt_term, g_curr_font );
        }

        ref = ixh1->entry;
        while( ref != NULL ) {                      // something more to print
            if( ref->entry_typ >= pgstring ) {      // 'pageno' is text
                process_text( ref->page_text, g_curr_font );
            } else {                                // 'pageno' is numeric
                ultoa( ref->page_no, &buffer, 10 );
                process_text( buffer, g_curr_font );
            }
            ref = ref->next;
        }
        scr_process_break();

        ixh2 = ixh1->lower;
        while( ixh2 != NULL ) {     // level 2
            if( ixh2->prt_term == NULL ) {
                process_text( ixh2->ix_term, g_curr_font );
            } else {
                process_text( ixh2->prt_term, g_curr_font );
            }

            ref = ixh2->entry;
            while( ref != NULL ) {                      // something more to print
                if( ref->entry_typ >= pgstring ) {      // 'pageno' is text
                    process_text( ref->page_text, g_curr_font );
                } else {                                // 'pageno' is numeric
                    ultoa( ref->page_no, &buffer, 10 );
                    process_text( buffer, g_curr_font );
                }
                ref = ref->next;
            }
            scr_process_break();

            ixh3 = ixh2->lower;
            while( ixh3 != NULL ) {     // level 3
                if( ixh3->prt_term == NULL ) {
                    process_text( ixh3->ix_term, g_curr_font );
                } else {
                    process_text( ixh3->prt_term, g_curr_font );
                }

                ref = ixh3->entry;
                while( ref != NULL ) {                      // something more to print
                    if( ref->entry_typ >= pgstring ) {      // 'pageno' is text
                        process_text( ref->page_text, g_curr_font );
                    } else {                                // 'pageno' is numeric
                        ultoa( ref->page_no, &buffer, 10 );
                        process_text( buffer, g_curr_font );
                    }
                    ref = ref->next;
                }
                scr_process_break();
                ixh3 = ixh3->next;
            }
            ixh2 = ixh2->next;
        }
        ixh1 = ixh1->next;

        if( ixh1 != NULL ) {
            if( letter[0] != toupper( *(ixh1->ix_term) ) ) {

                /* Set g_post_skip for next IXHEAD */

                set_skip_vars( NULL, NULL, &layout_work.ixhead.post_skip, spacing, 
                               layout_work.ixhead.font );
            }
        }
    }
}

/***************************************************************************/
/*  output TOC                                                             */
/*  Note: these attributes appear to have no effect:                       */
/*        TOCHn attribute align                                            */
/*        TOCHn attribute display_in_toc                                   */
/*  Note: this attribute is ignored (but may have an effect - TBD):        */
/*        TOCHn attribute group                                            */
/***************************************************************************/

static void gen_toc( void )
{
    bool            levels[7];              // track levels
    char            buffer[11];
    char            postfix[12];
    ffh_entry   *   curr;
    int             i;
    int             j;
    uint32_t        cur_level;
    uint32_t        indent[7];
    uint32_t        size;

    if( hd_list == NULL ) return;       // no hd_list, no TOC

    /* Insert TOC into current section */

    last_page_out();                // ensure are on new page
    g_skip = 0;                     // ignore remaining skip value
    set_section_banners( doc_sect_toc );
    reset_t_page();

    /* Set TOC margins and other values */
    
    g_page_left = g_page_left_org + 2 *
                  conv_hor_unit( &layout_work.toc.left_adjust, g_curr_font );    // matches wgml 4.0
    g_page_right = g_page_right_org -
                   conv_hor_unit( &layout_work.toc.right_adjust, g_curr_font );
    size = conv_hor_unit( &layout_work.tocpgnum.size, g_curr_font );     // space from fill to right edge
    figlist_toc_tabs( layout_work.toc.fill_string, size );

    /* Initialize levels and indent values */

    for( i = 0; i < 7; i++ ) {
        levels[i] = false;
        indent[i] = 0;
    }
    levels[0] = true;       // H0 is active at start

    /* Get converted indent values, which are cumulative */

    for( i = 0; i < 7; i++ ) {
        for( j = i; j < 7; j++ ) {
            indent[j] += conv_hor_unit( &layout_work.tochx[i].indent, g_curr_font );
        }
    }

    /* Output TOC */

    concat_save = ProcFlags.concat;
    ProcFlags.concat = true;
    justify_save = ProcFlags.justify;
    ProcFlags.justify = ju_off;
    ProcFlags.keep_left_margin = true;  // keep all indents while outputting text
    curr = hd_list;
    while( curr != NULL ) {
        cur_level = curr->number;
        for( i = 0; i < 7; i++ ) {
            if( i > cur_level ) {       // all lower levels are inactive
                levels[i] = false;
            }                
        }
        if( cur_level < layout_work.toc.toc_levels ) {
            g_curr_font = layout_work.tochx[cur_level].font;
            if( levels[cur_level] && !curr->abs_pre ) {
                spacing = layout_work.toc.spacing;
                set_skip_vars( &layout_work.tochx[cur_level].skip, NULL, NULL,
                               spacing, g_curr_font );
            } else {
                spacing = 1;
                set_skip_vars( &layout_work.tochx[cur_level].pre_skip, NULL,
                               &layout_work.tochx[cur_level].post_skip,
                               spacing, g_curr_font );
            }
            g_cur_left = g_page_left + indent[cur_level];
            g_cur_h_start = g_cur_left;

            if( curr->prefix != NULL ) {
                process_text( curr->prefix, g_curr_font );
                g_cur_left = t_line->last->x_address + t_line->last->width +
                             wgml_fonts[g_curr_font].spc_width;
                g_cur_h_start = g_cur_left;
                ProcFlags.ct = true;                // emulate CT
                post_space = 0;
            } else {
                t_line = alloc_text_line();         // capture spacing if no prefix
            }
            if( !levels[cur_level] ) {
                spacing = layout_work.toc.spacing;
                set_skip_vars( NULL, NULL, NULL, spacing, g_curr_font );
            }
            if( curr->text != NULL ) {
                g_page_right -= size;
                if( ProcFlags.has_aa_block ) {      // matches wgml 4.0
                    g_page_right -= tab_col;
                } else {
                    g_page_right -= 3 * tab_col;
                }
                ProcFlags.stop_xspc = true;         // suppress 2nd space after stop
                process_text( curr->text, g_curr_font );
                if( ProcFlags.has_aa_block ) {      // matches wgml 4.0
                    g_page_right += tab_col;
                } else {
                    g_page_right += 3 * tab_col;
                }
                g_page_right += size;
            }
            ProcFlags.ct = true;                    // emulate CT
            g_curr_font = FONT0;
            process_text( "$", g_curr_font );
            format_num( curr->pageno, &buffer, sizeof( buffer ), curr->style );
            strcpy_s( postfix, 12, "$" );           // insert tab characters
            strcat_s( postfix, 12, buffer );        // append page number
            g_curr_font = layout_work.tocpgnum.font;
            process_text( postfix, g_curr_font );
        }
        scr_process_break();                        // ensure line break
        levels[cur_level] = true;                   // first entry of level done
        curr = curr->next;
    }

    ProcFlags.concat = concat_save;
    ProcFlags.justify = justify_save;

    /* Re-establish current section */

    last_page_out();                // ensure all pages output
    set_section_banners( ProcFlags.doc_sect );
    reset_t_page();

    return;
}

/***************************************************************************/
/*  set new vertical position depending on banner existance                */
/***************************************************************************/

static void document_new_position( void )
{
    region_lay_tag  *   top_reg;
    uint32_t            top_pos;

    /* The value used for fb_position() should be the first line of text,
     * even if that is from a TITLE tag (top banners do not apply to TITLEP).
     * This handles documents starting with banners and text only.
     */

    if( sect_ban_top[page & 1] != NULL ) {
        top_reg = sect_ban_top[page & 1]->top_line;
        if( bin_driver->y_positive == 0x00 ) {
            top_pos = g_page_top_org - top_reg->reg_depth;
        } else {
            top_pos = g_page_top_org + top_reg->reg_depth;
        }
        g_cur_v_start = top_pos;
    } else {
        top_pos = g_page_top;
        if( bin_driver->y_positive == 0x00 ) {
            g_cur_v_start = g_page_top - wgml_fonts[FONT0].line_height;
        } else {
            g_cur_v_start = g_page_top + wgml_fonts[FONT0].line_height;
        }
    }
    g_cur_h_start = g_page_left_org;

    if( GlobalFlags.lastpass ) {
        if( ProcFlags.fb_position_done ) {
            fb_new_section( g_cur_v_start );
        } else {
            fb_position( g_cur_h_start, g_cur_v_start );
            ProcFlags.fb_position_done = true;
        }
    }
    g_cur_v_start = top_pos; // reset so first line positioning is correct
    return;
}

/***************************************************************************/
/*  set up the columns                                                     */
/*  Note: only sets t_page.max_width; the new column structure is to come  */
/***************************************************************************/

static void set_cols( void )
{
//  <<set up new-form columns when multicolumn is being implemented>>
//    t_page.max_width = g_net_page_width/t_page.col_count;
//    t_page.max_width -= conv_hor_unit(&layout_work.defaults.gutter);
    t_page.max_width = g_cl * box_col_width;
    return;
}

/***************************************************************************/
/*  start_doc_sect true section start                                      */
/*  Note: not used with FIGLIST or TOC, as these are not sections but      */
/*        rather are inserted into sections                                */
/***************************************************************************/

void start_doc_sect( void )
{
    bool                first_section;
    bool                header;
    bool                lvl_reset;
    bool                page_r;         // page reset
    char            *   h_text;
    doc_section         ds;
    hdsrc               hds_lvl;
    int                 k;
    page_ej             page_e;         // page eject tag
    uint32_t            page_c;         // page columns
    uint32_t            page_s;         // page spacing


    if( ProcFlags.start_section ) {
        return;                         // once is enough
    }
    if( !ProcFlags.fb_document_done ) { // the very first section/page
        do_layout_end_processing();
    }

    scr_process_break();                // commit any prior text 

    first_section = (ProcFlags.doc_sect == doc_sect_none);

    ProcFlags.start_section = true;
    ProcFlags.keep_left_margin = false;

    page_c = layout_work.defaults.columns;
    ds = ProcFlags.doc_sect_nxt;    // new section

    if( ds == doc_sect_none ) {
        ds = doc_sect_body;      // if text without section start assume body
    }

    /***********************************************************************/
    /*  process special section attributes                                 */
    /***********************************************************************/

    switch( ds ) {
    case   doc_sect_titlep :
        page_c = layout_work.titlep.columns;
        page_e = ej_yes;
        page_r = false;                 // no page number reset
        header = false;                 // no header string output
        lvl_reset = false;
        init_nest_cb();
        nest_cb->p_stack = copy_to_nest_stack();
        nest_cb->c_tag = t_TITLEP;
        nest_cb->p_stack->lineno = titlep_lineno; // correct line number
        break;
    case   doc_sect_abstract :
        page_c = layout_work.abstract.columns;
        page_e = layout_work.abstract.page_eject;
        page_r = layout_work.abstract.page_reset;
        page_s = layout_work.hx.hx_sect[hds_abstract].spacing;
        header = layout_work.hx.hx_sect[hds_abstract].header;
        if( header ) {
            h_text = &layout_work.abstract.string;
            hds_lvl = hds_abstract;
        }
        lvl_reset = false;
        break;
    case   doc_sect_preface :
        page_c = layout_work.preface.columns;
        page_e = layout_work.preface.page_eject;
        page_r = layout_work.preface.page_reset;
        page_s = layout_work.hx.hx_sect[hds_preface].spacing;
        header = layout_work.hx.hx_sect[hds_preface].header;
        if( header ) {
            h_text = &layout_work.preface.string;
            hds_lvl = hds_preface;
        }
        lvl_reset = false;
        break;
    case   doc_sect_body :
        page_c = layout_work.body.columns;
        page_e = layout_work.body.page_eject;
        page_r = layout_work.body.page_reset;
        page_s = layout_work.hx.hx_sect[hds_body].spacing;
        header = layout_work.hx.hx_sect[hds_body].header;
        if( header ) {
            h_text = &layout_work.body.string;
            hds_lvl = hds_body;
        }
        lvl_reset = true;
        break;
    case   doc_sect_appendix :
        page_c = layout_work.appendix.columns;
        page_e = layout_work.appendix.section_eject;
        page_r = layout_work.appendix.page_reset;
        page_s = layout_work.hx.hx_sect[hds_appendix].spacing;
        header = false;                 // no section header string output, as such
        if( page_e != ej_no ) {
            page_e = ej_yes;                        // "even" and "odd" act like "yes"
        }
        lvl_reset = true;
        break;
    case   doc_sect_backm :
        page_c = layout_work.backm.columns;
        page_e = layout_work.backm.page_eject;
        page_r = layout_work.backm.page_reset;
        page_s = layout_work.hx.hx_sect[hds_backm].spacing;
        header = layout_work.hx.hx_sect[hds_backm].header;
        if( header ) {
            h_text = &layout_work.backm.string;
            hds_lvl = hds_backm;
        }
        lvl_reset = true;
        break;
    case   doc_sect_index :
        page_c = layout_work.index.columns;
        page_e = layout_work.index.page_eject;
        page_r = layout_work.index.page_reset;
        page_s = layout_work.hx.hx_sect[hds_index].spacing;
        header = layout_work.hx.hx_sect[hds_index].header;
        if( header ) {
            h_text = &layout_work.index.index_string;
            hds_lvl = hds_index;
        }
        lvl_reset = false;
        break;
    case   doc_sect_gdoc :
    case   doc_sect_etitlep :
    case   doc_sect_frontm :
        page_c = layout_work.defaults.columns;
        page_e = ej_no;                         // no page eject
        page_r = false;                         // no page number reset
        page_s = layout_work.defaults.spacing;  // default spacing
        header = false;                         // no section header
        lvl_reset = false;
        break;
    case   doc_sect_egdoc :
        page_c = layout_work.defaults.columns;
        page_e = ej_yes;
        page_r = false;                         // no page number reset
        page_s = layout_work.defaults.spacing;  // default spacing
        header = false;                         // no section header
        lvl_reset = false;
        break;
    default:
        internal_err( __FILE__, __LINE__ );
        break;
    }

    if( first_section ) {               // nothing precedes the first section
        if( page_e == ej_even ) {
            do_page_out();              // apage of first page is odd
            page = 0;                   // restart page for first text page
            ProcFlags.page_ejected = true;
        }
        set_section_banners( ds );
        reset_t_page();
        document_new_position();        // first text page ready for content
    } else if( page_e == ej_no ) {
        full_page_out();                // ensure are on last page
        ProcFlags.page_ejected = false;
        set_section_banners( ds );
        reset_bot_ban();
    } else {
        last_page_out();                // ensure last page output
        ProcFlags.page_ejected = true;  // only first section has nothing to output

        if( page_e == ej_odd ) {
            if( (page & 1) ) {          // first page will be odd
                do_page_out();          // emit blank page
            }
        } else if( page_e == ej_even ) {
            if( !(page & 1) ) {         // first page will be even
                do_page_out();          // emit blank page
            }
        } else if( page_e != ej_yes ) {
            internal_err( __FILE__, __LINE__ );
        }
        g_skip = 0;                     // ignore remaining skip value
        set_section_banners( ds );
        reset_t_page();
    }

    ProcFlags.doc_sect = ds;
    ProcFlags.first_hdr = false;
    t_page.col_count = page_c;
    set_cols();
    if( page_r ) {
        page = 0;
    }
    spacing = page_s;

    /* Reset all heading numbers for ABSTRACT, BODY, APPENDIX and BACKM */

    if( lvl_reset ) {
        for( k = 0; k < hds_appendix; k++ ) {
            hd_nums[k].headn = 0;// reset all levels
            hd_nums[k].hnumstr[0] = '\0';
            if( hd_nums[k].hnumsub != NULL ) {
                *(hd_nums[k].hnumsub->value) = '\0';
            }
        }
    }



    g_cur_left = g_page_left_org;
    if( header ) {
        concat_save = ProcFlags.concat;
        ProcFlags.concat = true;
        justify_save = ProcFlags.justify;
        ProcFlags.justify = ju_off;
        gen_heading( h_text, NULL, 0, hds_lvl );
        g_indent = 0;                           // reset for section body
        ProcFlags.concat = concat_save;
        ProcFlags.justify = justify_save;
    }
    g_curr_font = layout_work.defaults.font;
    g_cur_h_start = g_page_left_org + g_indent;
    ProcFlags.doc_sect = ds;
}

/***************************************************************************/
/*  routine to init document section change                                */
/***************************************************************************/

static void gml_doc_xxx( doc_section ds )
{

    if( ProcFlags.doc_sect >= ds ) {    // wrong sequence of sections
        g_err_doc_sect( ds );
    }
    ProcFlags.doc_sect_nxt = ds;        // remember new section
    ProcFlags.start_section = false;    // do real section start later

    scan_start = scan_stop + 1;
    return;
}

/***************************************************************************/
/*  Document section tags                                                  */
/*                                                                         */
/*  :GDOC                 the only one with attributes                     */
/*  :FRONTM    optional                                                    */
/*  :TITLEP    optional                                                    */
/*  :ETITLEP   optional                                                    */
/*  :ABSTRACT  optional                                                    */
/*  :PREFACE   optional                                                    */
/*  :TOC       optional                                                    */
/*  :FIGLIST   optional                                                    */
/*  :BODY              default                                             */
/*  :APPENDIX  optional                                                    */
/*  :BACKM     optional                                                    */
/*  :INDEX     optional                                                    */
/*  :EGDOC     optional                                                    */
/***************************************************************************/

extern void gml_abstract( const gmltag * entry )
{
    if( ProcFlags.doc_sect_nxt == doc_sect_egdoc ) {
        xx_line_err( err_eof_expected, tok_start );
        return;
    }
    if( !ProcFlags.frontm_seen ) {
        xx_line_err( err_doc_sec_expected_1, tok_start );
        return;
    }
    if( blank_lines > 0 ) {
        set_skip_vars( NULL, NULL, NULL, 0, 0 );    // set g_blank_lines
    }
    scr_process_break();
    gml_doc_xxx( doc_sect_abstract );
    g_cur_left = g_page_left;
    g_cur_h_start = g_page_left;

    if( layout_work.hx.hx_sect[hds_abstract].header ) {
        start_doc_sect();                           // a header is enough
    }
    g_indent = 0;
    g_indentr = 0;
    set_h_start();
}

extern void gml_appendix( const gmltag * entry )
{
    if( blank_lines > 0 ) {
        set_skip_vars( NULL, NULL, NULL, 0, 0 );    // set g_blank_lines
    }
    scr_process_break();
    gml_doc_xxx( doc_sect_appendix );
    ProcFlags.frontm_seen = false;  // no longer in FRONTM section
    if( !ProcFlags.fb_document_done ) { // the very first section/page
        do_layout_end_processing();
    }
    g_indent = 0;
    g_indentr = 0;
    set_h_start();
}

extern void gml_backm( const gmltag * entry )
{
    if( !ProcFlags.fb_document_done ) { // the very first section/page
        do_layout_end_processing();
    }

    if( blank_lines > 0 ) {
        set_skip_vars( NULL, NULL, NULL, 0, 0 );    // set g_blank_lines
    }
    scr_process_break();
    gml_doc_xxx( doc_sect_backm );
    ProcFlags.frontm_seen = false;  // no longer in FRONTM section
    g_cur_left = g_page_left;
    g_cur_h_start = g_page_left;

    if( layout_work.hx.hx_sect[hds_backm].header ) {
        start_doc_sect();                           // a header is enough
    }
    g_indent = 0;
    g_indentr = 0;
}

extern void gml_body( const gmltag * entry )
{
    if( blank_lines > 0 ) {
        set_skip_vars( NULL, NULL, NULL, 0, 0 );    // set g_blank_lines
    }
    scr_process_break();
    gml_doc_xxx( doc_sect_body );

    ProcFlags.just_override = true;     // justify for first line ?? TBD
    g_cur_left = g_page_left;
    g_cur_h_start = g_page_left
                    + conv_hor_unit( &layout_work.p.line_indent, g_curr_font );

    ProcFlags.frontm_seen = false;      // no longer in FRONTM section
    if( !ProcFlags.fb_document_done ) { // the very first section/page
        do_layout_end_processing();
    }
    if( layout_work.hx.hx_sect[hds_body].header ) {
        start_doc_sect();                           // a header is enough
    }
    g_indent = 0;
    g_indentr = 0;
    set_h_start();
}

extern void gml_figlist( const gmltag * entry )
{
    scr_process_break();
    figlist_toc |= gs_figlist;
    if( pass > 1 ) { 
        gen_figlist();
    }
}

extern void gml_frontm( const gmltag * entry )
{
    scr_process_break();
    gml_doc_xxx( doc_sect_frontm );
    if( !ProcFlags.fb_document_done ) { // the very first section/page
        do_layout_end_processing();
    }
    ProcFlags.frontm_seen = true;
}

/***************************************************************************/
/*  :INDEX tag is special, not really a section                            */
/***************************************************************************/

extern void gml_index( const gmltag * entry )
{
    if( ProcFlags.doc_sect_nxt == doc_sect_egdoc ) {
        xx_line_err( err_eof_expected, tok_start );
        return;
    }

    if( ProcFlags.doc_sect_nxt == doc_sect_index ) {// duplicate :INDEX tag
        scan_start = scan_stop + 1;     // ignore this call
        return;                         // wgml4 OS/2 crashes with page fault
    }

    if( !((ProcFlags.doc_sect == doc_sect_backm) ||
          (ProcFlags.doc_sect_nxt == doc_sect_backm)) ) {
        xx_line_err( err_doc_sec_expected_1, tok_start );
        return;
    }
    if( !GlobalFlags.index ) {          // index option not active
        return;
    }

    scr_process_break();
    gml_doc_xxx( doc_sect_index );

    /* When gen_index() is finalized, the resets may need to be moved */

    g_indent = 0;
    g_indentr = 0;
    set_h_start();

    /* Must be called each pass */

    gen_index();                        // output the formatted index
}

extern void gml_preface( const gmltag * entry )
{
    if( ProcFlags.doc_sect_nxt == doc_sect_egdoc ) {
        xx_line_err( err_eof_expected, tok_start );
        return;
    }
    if( !ProcFlags.frontm_seen ) {
        xx_line_err( err_doc_sec_expected_1, tok_start );
        return;
    }
    if( blank_lines > 0 ) {
        set_skip_vars( NULL, NULL, NULL, 0, 0 );    // set g_blank_lines
    }
    scr_process_break();
    gml_doc_xxx( doc_sect_preface );
    if( layout_work.hx.hx_sect[hds_preface].header ) {
        start_doc_sect();                           // a header is enough
    }
    g_indent = 0;
    g_indentr = 0;
    set_h_start();
}

extern void gml_titlep( const gmltag * entry )
{
    if( ProcFlags.doc_sect_nxt == doc_sect_egdoc ) {
        xx_line_err( err_eof_expected, tok_start );
        return;
    }
    if( !ProcFlags.frontm_seen ) {
        xx_line_err( err_doc_sec_expected_1, tok_start );
        return;
    }
    scr_process_break();
    gml_doc_xxx( doc_sect_titlep );

    add_symvar( &global_dict, "$stitle", "", no_subscript, 0 );// set nullstring
    add_symvar( &global_dict, "$title", "", no_subscript, 0 );// set nullstring

    rs_loc = titlep_tag;
    if( input_cbs->fmflags & II_file ) {    // save line number
        titlep_lineno = input_cbs->s.f->lineno;
    } else if( input_cbs->fmflags & II_tag_mac ) {
        titlep_lineno = input_cbs->s.m->lineno;
    } else {
        titlep_lineno = 0;                  // not clear what to do here
    }
    save_indent = g_indent;
    save_indentr = g_indentr;
    g_indent = 0;
    g_indentr = 0;
    set_h_start();
}

extern void gml_etitlep( const gmltag * entry )
{
    tag_cb  *   wk;

    scr_process_break();
    gml_doc_xxx( doc_sect_etitlep );
    rs_loc = 0;
    titlep_lineno = 0;

    if( nest_cb != NULL ) { // guard against no FRONTM, empty TITLEP section
        g_indent = save_indent;
        g_indentr = save_indentr;
        set_h_start();
        wk = nest_cb;
        nest_cb = nest_cb->prev;
        add_tag_cb_to_pool( wk );
    }
}

extern void gml_toc( const gmltag * entry )
{
    scr_process_break();
    figlist_toc |= gs_toc;
    if( pass > 1 ) { 
        gen_toc();
    }
}

extern void gml_egdoc( const gmltag * entry )
{
    fwd_ref *   curr;
    
    if( blank_lines > 0 ) {
        set_skip_vars( NULL, NULL, NULL, 0, 0 );    // set g_blank_lines
    }
    scr_process_break();                        // outputs last element in file

    if( GlobalFlags.lastpass ) {                // output on last pass only
        if( passes == 1 ) {                     // first and only pass
            if( figlist_toc & gs_toc ) {        // only if TOC was found
                gen_toc();
            }
            if( figlist_toc & gs_figlist ) {    // only if FIGLIST was found
                gen_figlist();
            }
            curr = fig_fwd_refs;
            while( curr != NULL ) {     // output figure forward/undefined references
                if( find_refid( fig_ref_dict, curr->id ) != NULL ) {
                    fwd_id_warn( curr->id, "figure" );
                } else {
                    undef_id_warn( curr->id, "Figure" );
                }
                curr = curr->next;
            }
            curr = hd_fwd_refs;
            while( curr != NULL ) { // output header forward/undefined references
                if( find_refid( hd_ref_dict, curr->id ) != NULL ) {
                    fwd_id_warn( curr->id, "heading" );
                } else {
                    undef_id_warn( curr->id, "Heading" );
                }
                curr = curr->next;
            }
            curr = fn_fwd_refs;
            while( curr != NULL ) { // output footnote forward/undefined references
                if( find_refid( fn_ref_dict, curr->id ) != NULL ) {
                    fwd_id_warn( curr->id, "footnote" );
                } else {
                    undef_id_warn( curr->id, "Footnote" );
                }
                curr = curr->next;
            }
            if( figlist_toc ) {
                xx_simple_warn( wng_pass_1 );   // more than one pass needed 
            }
        } else {                                // last pass of at least 2
            curr = fig_fwd_refs;
            while( curr != NULL ) { // output figure undefined/page change references
                fwd_id_warn( curr->id, "figure" );
                curr = curr->next;
            }
            curr = hd_fwd_refs;
            while( curr != NULL ) { // output header undefined/page changereferences
                fwd_id_warn( curr->id, "heading" );
                curr = curr->next;
            }
            if( ProcFlags.new_pagenr ) {
                xx_simple_warn( wng_pass_many );// at least one more pass needed
            }
        }
        if( !GlobalFlags.index ) {          // index option not active
            xx_simple_warn( wng_index_opt );// give hint to activate index
        }
    }

    gml_doc_xxx( doc_sect_egdoc );
}

/***************************************************************************/
/*  :gdoc sec='TOP secret, destroy before reading'                         */
/***************************************************************************/

extern void gml_gdoc( const gmltag * entry )
{
    char        *   p;

    scan_err = false;
    p = scan_start;
    if( *p ) p++;

    while( *p == ' ' ) {                // over WS to attribute
        p++;
    }
    if( *p &&
        ! (strnicmp( "sec ", p, 4 ) &&  // look for "sec " or "sec="
           strnicmp( "sec=", p, 4 )) ) {
        char        quote;
        char    *   valstart;

        p += 3;
        while( *p == ' ' ) {
            p++;
        }
        if( *p == '=' ) {
            p++;
            while( *p == ' ' ) {
                p++;
            }
        }
        if( *p == '"' || *p == '\'' ) {
            quote = *p;
            ++p;
        } else {
            quote = ' ';
        }
        valstart = p;
        while( *p && *p != quote ) {
            ++p;
        }
        *p = '\0';

        add_symvar( &global_dict, "$sec", valstart, no_subscript, 0 );
    } else {
        add_symvar( &global_dict, "$sec", "", no_subscript, 0 );// set nullstring
    }

    gml_doc_xxx( doc_sect_gdoc );
    if( !ProcFlags.fb_document_done ) { // the very first section/page
        do_layout_end_processing();
    }
    return;
}

