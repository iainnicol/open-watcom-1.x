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
* Description: WGML implement processing for banner output
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include "wgml.h"
#include "gvars.h"

static  text_line       ban_line;       // for constructing banner line
static  text_chars  *   reg_text[3];    // 3 possible ban region parts

static  banner_lay_tag  *   ban_top[max_ban][2];
static  banner_lay_tag  *   ban_bot[max_ban][2];


/***************************************************************************/
/*  set banner pointers for head x heading                                 */
/*  NOTE: this ignores differences in line height ant their effect on page */
/*        top and page depth and so on pagination                          */
/***************************************************************************/
void set_headx_banners( int hx_lvl )
{
    if( (ban_top[hx_lvl + head0_ban][0] != NULL) ||
            (ban_top[hx_lvl + head0_ban][1] != NULL) ||
            (ban_bot[hx_lvl + head0_ban][0] != NULL) ||
            (ban_bot[hx_lvl + head0_ban][1] != NULL) ) {
        ProcFlags.heading_banner = true;        // at least one Hn banner exists
    }
    if( ProcFlags.heading_banner ) {            // change all banners if any exist
        sect_ban_top[0] = ban_top[hx_lvl + head0_ban][0];
        sect_ban_top[1] = ban_top[hx_lvl + head0_ban][1];
        sect_ban_bot[0] = ban_bot[hx_lvl + head0_ban][0];
        sect_ban_bot[1] = ban_bot[hx_lvl + head0_ban][1];
    }
    return;
}

/***************************************************************************/
/*  set banner pointers                                                    */
/***************************************************************************/
void set_banners( void )
{
    banner_lay_tag  *   ban;
    int                 k;

    static const struct {
        ban_docsect     ban_tag;
        e_tags          tag;
    }  ban_2_tag[max_ban] =  {
        { no_ban,       t_NONE     },   // dummy
        { abstract_ban, t_ABSTRACT },
        { appendix_ban, t_APPENDIX },
        { backm_ban,    t_BACKM    },
        { body_ban,     t_BODY     },
        { figlist_ban,  t_FIGLIST  },
        { index_ban,    t_INDEX    },
        { preface_ban,  t_PREFACE  },
        { toc_ban,      t_TOC      },
        { head0_ban,    t_H0       },
        { head1_ban,    t_H1       },
        { head2_ban,    t_H2       },
        { head3_ban,    t_H3       },
        { head4_ban,    t_H4       },
        { head5_ban,    t_H5       },
        { head6_ban,    t_H6       },
        { letfirst_ban, t_NONE     },   // dummy
        { letlast_ban,  t_NONE     },   // dummy
        { letter_ban,   t_NONE     },   // dummy
    };

    for( k = 0; k < max_ban; k++ ) {    // init banner list
        ban_top[k][0] = ban_top[k][1] = NULL;
        ban_bot[k][0] = ban_bot[k][1] = NULL;
    }

    for( ban = layout_work.banner; ban != NULL; ban = ban->next ) {

        if( ban->docsect > no_ban && ban->docsect < max_ban ) {
            for( k = 0; k < max_ban; k++ ) {
                if( ban->docsect == ban_2_tag[k].ban_tag ) {// tag found
                    switch( ban->place ) {
                    case   top_place :
                        ban_top[k][0] = ban;
                        ban_top[k][1] = ban;
                        break;
                    case   bottom_place :
                        ban_bot[k][0] = ban;
                        ban_bot[k][1] = ban;
                        break;

                    case   topodd_place :
                        ban_top[k][1] = ban;
                        break;
                    case   topeven_place :
                        ban_top[k][0] = ban;
                        break;

                    case   botodd_place :
                        ban_bot[k][1] = ban;
                        break;
                    case   boteven_place :
                        ban_bot[k][0] = ban;
                        break;
                    default:
                        break;
                    }
                    break;              // tag for banner found
                }
            }
        }
    }
}


/***************************************************************************/
/*  actually set a pgnum_style value from a given banner                   */
/***************************************************************************/

static bool do_set_pgnum_style( banner_lay_tag * ban, uint8_t index )
{
    bool    retval  = true;

    if( ban == NULL ) {         // nothing to do
        retval = false;
    } else if( ban->style == pgnuma_content ) {
        pgnum_style[index] = h_style;
    } else if( ban->style == pgnumad_content ) {
        pgnum_style[index] = h_style | xd_style;
    } else if( ban->style == pgnumr_content ) {
        pgnum_style[index] = r_style;
    } else if( ban->style == pgnumrd_content ) {
        pgnum_style[index] = r_style | xd_style;
    } else if( ban->style == pgnumc_content ) {
        pgnum_style[index] = c_style;
    } else if( ban->style == pgnumcd_content ) {
        pgnum_style[index] = c_style | xd_style;
    } else {    // banner content is not a page number style
        retval = false;
    }

    return(retval);
}


/***************************************************************************/
/*  set the pgnum_style array from the banner set arrays                   */
/*      first use a switch to identify the banners to use                  */
/*      then set the value by examining the banners in the order used by   */
/*      wgml 4.0                                                           */
/***************************************************************************/

void set_pgnum_style( void )
{
    int         i;
    ban_docsect ban_offset;

    for( i = 0; i < pns_max; i++ ) {
        switch( i ) {
        case pns_abstract :
            ban_offset = abstract_ban;
            break;
        case pns_appendix :
            ban_offset = appendix_ban;
            break;
        case pns_backm :
            ban_offset = backm_ban;
            break;
        case pns_body :
            ban_offset = body_ban;
            break;
        }
        if( do_set_pgnum_style( ban_top[ban_offset][0], i ) ) {
        } else if( do_set_pgnum_style( ban_top[ban_offset][1], i ) ) {
        } else if( do_set_pgnum_style( ban_bot[ban_offset][1], i ) ) {
        } else if( do_set_pgnum_style( ban_bot[ban_offset][0], i ) ) {
        } else {
            pgnum_style[i] = h_style;
        }
    }
    return;
}


/***************************************************************************/
/* Return a rule or char line doc_element                                  */
/* This function must check whether a graphic line or a character line of  */
/* hyphens is needed                                                       */
/***************************************************************************/

static doc_element * create_rule( uint32_t start, uint32_t width )
{
    doc_element *   h_line_el;

    if( bin_driver->hline.text == NULL ) {              // character device
        line_buff.current = width;
        while( line_buff.current > line_buff.length ) {
            line_buff.length *= 2;
            line_buff.text = mem_realloc( line_buff.text, line_buff.length + 1 );
        }
        memset( line_buff.text, bin_device->box.horizontal_line, line_buff.current );
        line_buff.text[line_buff.current] = '\0';
        process_text( line_buff.text, FONT0 );  // matches wgml 4.0
        h_line_el = init_doc_el( el_text, 0 );
        h_line_el->element.text.first = t_line;
        t_line = NULL;
    } else {                                        // page-oriented device

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
    }
    return (h_line_el);
}



/*  prepare 1 or more text_chars with region content                       */
/*                                                                         */
/***************************************************************************/

static void content_reg( region_lay_tag * region )
{
    text_chars  *   curr_t;
    char        *   pbuf;
    symsub      *   symsubval;
    int             k;
    int             rc;

    switch( region->contents.content_type ) {
    case   string_content:
        pbuf = mem_alloc( buf_size );
        *pbuf = '\0';
        if( region->script_format ) {
            /***************************************************************/
            /*  substitute variables and create text_chars instances       */
            /***************************************************************/
            for( k = 0; k < 3; ++k ) {

                if( region->script_region[k].string != NULL ) {
                    strcpy_s( pbuf, strlen(region->contents.string) + 1, region->contents.string );
                    resolve_symvar_functions( pbuf );
                    resolve_symvar_functions( pbuf );
                    if( *pbuf ) {
                        curr_t = alloc_text_chars( pbuf, strlen( pbuf ), region->font );
                        /***************************************************/
                        /* use current font for width calculation          */
                        /* even if another font is used for banregion      */
                        /* to get the same result as wgml4                 */
                        /***************************************************/
                        curr_t->width = cop_text_width( curr_t->text, curr_t->count, g_curr_font );
                                                       //   region->font );
                        reg_text[k] = curr_t;
                    }
                }
            }
        } else {    // no script format only normal string with perhaps vars

            strcpy_s( pbuf, strlen(region->contents.string) + 1, region->contents.string );
            resolve_symvar_functions( pbuf );
            resolve_symvar_functions( pbuf );
            if( *pbuf ) {
                curr_t = alloc_text_chars( pbuf, strlen( pbuf ), region->font );
                /***********************************************************/
                /*  is font 0 used for width calc?                    TBD  */
                /***********************************************************/
                curr_t->width = cop_text_width( curr_t->text, curr_t->count, region->font );
                if( region->region_position == pos_left ) {
                    reg_text[0] = curr_t;
                } else if( region->region_position == pos_center ) {
                    reg_text[1] = curr_t;
                } else if( region->region_position == pos_right ) {
                    reg_text[2] = curr_t;
                } else {
                    reg_text[0] = curr_t;   // position left if unknown
                }
            }
        }

        mem_free( pbuf );
        break;
    case author_content :
        rc = find_symvar( &global_dict, "$author", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "author", 6, region->font );
        }
        break;
    case bothead_content :
        rc = find_symvar( &global_dict, "$bothead", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "bothead", 7, region->font );
        }
        break;
    case date_content :
        rc = find_symvar( &global_dict, "$date", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "date", 4, region->font );
        }
        break;
    case docnum_content :
        rc = find_symvar( &global_dict, "$docnum", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "docnum", 6, region->font );
        }
        break;
    case head0_content :
        rc = find_symvar( &global_dict, "$head0", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head0", 5, region->font );
        }
        break;
    case head1_content :
        rc = find_symvar( &global_dict, "$head1", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head1", 5, region->font );
        }
        break;
    case head2_content :
        rc = find_symvar( &global_dict, "$head2", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head2", 5, region->font );
        }
        break;
    case head3_content :
        rc = find_symvar( &global_dict, "$head3", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head3", 5, region->font );
        }
        break;
    case head4_content :
        rc = find_symvar( &global_dict, "$head4", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head4", 5, region->font );
        }
        break;
    case head5_content :
        rc = find_symvar( &global_dict, "$head5", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head5", 5, region->font );
        }
        break;
    case head6_content :
        rc = find_symvar( &global_dict, "$head6", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "head6", 5, region->font );
        }
        break;
    case headnum0_content :
        rc = find_symvar( &global_dict, "$hnum0", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum0", 5, region->font );
        }
        break;
    case headnum1_content :
        rc = find_symvar( &global_dict, "$hnum1", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum1", 5, region->font );
        }
        break;
    case headnum2_content :
        rc = find_symvar( &global_dict, "$hnum2", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum2", 5, region->font );
        }
        break;
    case headnum3_content :
        rc = find_symvar( &global_dict, "$hnum3", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum3", 5, region->font );
        }
        break;
    case headnum4_content :
        rc = find_symvar( &global_dict, "$hnum4", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum4", 5, region->font );
        }
        break;
    case headnum5_content :
        rc = find_symvar( &global_dict, "$hnum5", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum5", 5, region->font );
        }
        break;
    case headnum6_content :
        rc = find_symvar( &global_dict, "$hnum6", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "hnum6", 5, region->font );
        }
        break;
    case headtext0_content :
        rc = find_symvar( &global_dict, "$htext0", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext0", 5, region->font );
        }
        break;
    case headtext1_content :
        rc = find_symvar( &global_dict, "$htext1", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext1", 5, region->font );
        }
        break;
    case headtext2_content :
        rc = find_symvar( &global_dict, "$htext2", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext2", 5, region->font );
        }
        break;
    case headtext3_content :
        rc = find_symvar( &global_dict, "$htext3", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext3", 5, region->font );
        }
        break;
    case headtext4_content :
        rc = find_symvar( &global_dict, "$htext4", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext4", 5, region->font );
        }
        break;
    case headtext5_content :
        rc = find_symvar( &global_dict, "$htext5", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext5", 5, region->font );
        }
        break;
    case headtext6_content :
        rc = find_symvar( &global_dict, "$htext6", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "htext6", 5, region->font );
        }
        break;
    case pgnuma_content :
        rc = find_symvar( &global_dict, "$pgnuma", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "pgnuma", 6, region->font );
        }
        break;
    case pgnumad_content :
        rc = find_symvar( &global_dict, "$pgnumad", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumad", 7, region->font );
        }
        break;
    case pgnumc_content :
        rc = find_symvar( &global_dict, "$pgnumc", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumc", 6, region->font );
        }
        break;
    case pgnumcd_content :
        rc = find_symvar( &global_dict, "$pgnumcd", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumcd", 7, region->font );
        }
        break;
    case pgnumr_content :
        rc = find_symvar( &global_dict, "$pgnumr", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumr", 6, region->font );
        }
        break;
    case pgnumrd_content :
        rc = find_symvar( &global_dict, "$pgnumrd", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumrd", 7, region->font );
        }
        break;
    case sec_content :
        rc = find_symvar( &global_dict, "$sec", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "sec", 3, region->font );
        }
        break;
    case stitle_content :
        rc = find_symvar( &global_dict, "$stitle", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "stitle", 6, region->font );
        }
        break;
    case title_content :
        rc = find_symvar( &global_dict, "$title", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "title", 6, region->font );
        }
        break;
    case time_content :
        rc = find_symvar( &global_dict, "$time", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "time", 4, region->font );
        }
        break;
    case tophead_content :
        rc = find_symvar( &global_dict, "$tophead", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ), region->font );
        } else {
            curr_t = alloc_text_chars( "tophead", 7, region->font );
        }
        break;
    case no_content :                   // empty region
        curr_t = NULL;
        curr_t = alloc_text_chars( "<no content>", 12, region->font );
        break;
    default:
        internal_err( __FILE__, __LINE__ );
    }
    if( curr_t == NULL ) {
        /* do nothing                                              */
    } else {
        if( region->contents.content_type != string_content ) {
            /***********************************************************/
            /*  is font 0 used for width calc?                    TBD  */
            /***********************************************************/
            curr_t->width = cop_text_width( curr_t->text, curr_t->count, region->font );
            if( region->region_position == pos_left ) {
                reg_text[0] = curr_t;
            } else if( region->region_position == pos_center ) {
                reg_text[1] = curr_t;
            } else if( region->region_position == pos_right ) {
                reg_text[2] = curr_t;
            } else {
                reg_text[0] = curr_t;  // position left if invalid
            }
        }
    }
    return;
}


/***************************************************************************/
/*  output top / bottom banner                                             */
/*  multiple columns not supported, as it is not clear if they are needed  */
/***************************************************************************/

static  void    out_ban_common( banner_lay_tag * ban, bool top )
{
    ban_reg_group   *   cur_grp;
    doc_element     *   cur_doc_el;
    int                 k;
    region_lay_tag  *   cur_region;
    text_chars      *   curr_t;
    text_chars      *   curr_p;
    uint32_t            ban_left;
    uint32_t            h_left;
    uint32_t            ban_right;
    uint32_t            h_right;
    uint32_t            reg_indent;
    uint32_t            curr_x;

    ban_line.first = NULL;

    /* calc banner horizontal margins */
    ban_left  = ban->ban_left_adjust;
    ban_right = t_page.page_width - ban->ban_right_adjust;  // banners are not placed in page columns

    /* This is the simplest way to process multiple BANREGIONs -- more may be needed */

    cur_grp = ban->by_line;
    while( cur_grp != NULL ) {
        cur_region = cur_grp ->first;
        while( cur_region != NULL ) {

            reg_text[0] = NULL;
            reg_text[1] = NULL;
            reg_text[2] = NULL;

            if( cur_region->contents.content_type == rule_content ) {
                cur_doc_el = create_rule( ban_left, ban_right - ban_left );  /// TEMPORARY: NEED ACTUAL VALUES!
            } else {
                content_reg( cur_region );
                curr_x = 0;

                for( k = 0; k < 3; ++k ) {          // for all region parts
                    if( reg_text[k] == NULL ) {
                        continue;                   // skip empty part
                    }
                    if( top ) {
                        g_prev_font = reg_text[k]->font;
                    }
                    if( ban_line.first == NULL ) {
                        ban_line.first = reg_text[k];
                        ban_line.line_height = wgml_fonts[reg_text[k]->font].line_height;
                    } else {
                        ban_line.last->next = reg_text[k];
                        reg_text[k]->prev = ban_line.last;
                    }
                    if( ban_line.line_height < wgml_fonts[reg_text[k]->font].line_height ) {
                        ban_line.line_height = wgml_fonts[reg_text[k]->font].line_height;
                    }
                    curr_t = reg_text[k];
                    ban_line.last  = reg_text[k];

                    h_left  = ban_left;
                    h_right = ban_right;
                    reg_indent = cur_region->reg_indent;
                    if( cur_region->hoffset.su_u >= SU_lay_left  ) {   // symbolic
                        if( cur_region->hoffset.su_u == SU_lay_left ) {
                            h_left += reg_indent;
                        } else if( cur_region->hoffset.su_u == SU_lay_right ) {
                            h_right -= reg_indent;
                        } else if( cur_region->hoffset.su_u == SU_lay_centre ) {
                            h_left += reg_indent;
                        }
                    } else {                            // in horiz space units
                        h_left += reg_indent + cur_region->reg_hoffset;
                    }

                    if( cur_region->region_position == pos_center || k == 1) {
                        if( h_left + curr_t->width < h_right ) {
                            h_left += (h_right - h_left - curr_t->width) / 2;
                            curr_x = h_left;
                        }
                    } else if( cur_region->region_position == pos_right || k == 2) {
                        h_left = h_right - curr_t->width;
                        curr_x = h_left;
                    }
                    if( curr_x == 0 ) {
                        curr_x = h_left;
                    }
                    curr_t->x_address = curr_x;
                    curr_x += curr_t->width;
                }
                if( ban_line.first != NULL) {
                    if( input_cbs->fmflags & II_research ) {
                        test_out_t_line( &ban_line );
                    }

                    /*******************************************************************/
                    /*  truncate the left part(s) in case of overlap                   */
                    /*******************************************************************/
                    curr_p = ban_line.first;

                    for( curr_t = curr_p->next; curr_t != NULL; curr_t = curr_t->next ) {
                        while( (curr_p->x_address + curr_p->width) > curr_t->x_address ) {
                            if( curr_p->count < 2) {// sanity check
                                break;
                            }
                            curr_p->count -= 1;     // truncate text, adjust width
                            curr_p->width -= wgml_fonts[curr_p->font].width_table[(unsigned char)curr_p->text[curr_p->count]];
                        }
                        curr_p = curr_t;
                    }
                    cur_doc_el = alloc_doc_el( el_text );
                    cur_doc_el->top_skip = ban->by_line->voffset;
                    cur_doc_el->subs_skip = ban->by_line->voffset;
                    cur_doc_el->element.text.first = alloc_text_line();

                    cur_doc_el->element.text.first->next = ban_line.next;
                    cur_doc_el->element.text.first->line_height = ban_line.line_height;
                    cur_doc_el->element.text.first->spacing = 0;   // hbus; banners are always single-spaced
                    cur_doc_el->element.text.first->y_address = ban_line.y_address;
                    cur_doc_el->element.text.first->first = ban_line.first;
                    cur_doc_el->element.text.first->last = ban_line.last;
                    ban_line.first = NULL;
                }
            }

            /****************************************************************/
            /*  insert ban_line into t_page                                 */
            /*  ban_line is taken to be a linked list of text_lines when    */
            /*  a banregion has depth > 1 and enough text to fill the       */
            /*  first line                                                  */
            /*  this will need adjustment as banner output is enhanced      */
            /****************************************************************/

            if( top ) {
                if( t_page.top_ban == NULL ) {
                    t_page.top_ban = alloc_ban_col();
                }
                if( t_page.top_ban->first == NULL ){
                    t_page.top_ban->first = cur_doc_el;
                    t_page.top_ban->last = t_page.top_ban->first;
                } else {
                    t_page.top_ban->last->next = cur_doc_el;
                    t_page.top_ban->last = t_page.top_ban->last->next;
                }
            } else {
                if( t_page.bot_ban == NULL ) {
                    t_page.bot_ban = alloc_ban_col();
                }
                if( t_page.bot_ban->first == NULL ){
                    t_page.bot_ban->first = cur_doc_el;
                    t_page.bot_ban->last = t_page.bot_ban->first;
                } else {
                    t_page.bot_ban->last->next = cur_doc_el;
                    t_page.bot_ban->last = t_page.bot_ban->last->next;
                }
            }
            cur_region = cur_region->next;
        }
        cur_grp = cur_grp->next;
    }
}

/***************************************************************************/
/*  output top or bottom banner                                            */
/***************************************************************************/
void    out_ban_top( void )
{
    out_ban_common( t_page.top_banner, true );      // true for top banner
}

void    out_ban_bot( void )
{
    out_ban_common( t_page.bottom_banner, false );  // false for bottom banner
}

