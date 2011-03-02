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
/*  Split banregion into left middle right part if region is script format */
/***************************************************************************/
static  void    preprocess_script_region( banner_lay_tag * ban ) {
    char    *   pl;
    char        sep;
    int         k;

    if( (ban->region->contents.content_type == string_content)
        && ban->region->script_format ) {

            /***************************************************************/
            /*  script format is a 3 part region: left middle right        */
            /*  first char is separator char                               */
            /*  /left//right/  empty middle part in this case              */
            /***************************************************************/


            /***************************************************************/
            /*  preprocess script format banner region for speed           */
            /***************************************************************/
        pl = ban->region->contents.string;
        sep = *pl;                      // first char is separator
                                        // isolate region parts
        for( k = 0; k < 3; ++k ) {      // left, center, right
            pl++;
            if( k == 2 ) {// special hack for right part without success
                while( *pl == ' ' ) {
                    pl++;               // remove leading spaces
                }           // still not quite the same result as wgml4   TBD
            }
            ban->region->script_region[k].string = pl;
            while( *pl &&  *pl != sep ) {
                pl++;
            }
            ban->region->script_region[k].len =  pl -
                ban->region->script_region[k].string ;

            if( ban->region->script_region[k].len == 0 ) {
                ban->region->script_region[k].string = NULL;
            } else {
                *pl = '\0';             // null terminate
            }
        }
    }
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
        { index_ban,    t_INDEX    },
        { preface_ban,  t_PREFACE  },
        { toc_ban,      t_TOC      },
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
                    preprocess_script_region( ban );
                    break;              // tag for banner found
                }
            }
        }
    }
}


/***************************************************************************/
/*  calc banner top region position                                        */
/*  this may or may not be the first region listed!                        */
/***************************************************************************/

extern  uint32_t    ban_top_pos( banner_lay_tag * ban )
{
    uint32_t            ban_depth;
    uint32_t            v_pos;
    uint32_t            reg_off;
    int32_t             skip;

    ban_depth = ban->ban_depth;
    reg_off = ban->top_line->reg_voffset;

    skip = ban_depth - reg_off - wgml_fonts[ban->top_line->font].line_height;
    if( skip > 0 ) {               // if region start is not last banner line
        post_top_skip = skip;           // reserve space
    } else {
        post_top_skip = 0;
    }

    if( bin_driver->y_positive == 0 ) {
        v_pos = g_page_top - reg_off;
    } else {
        v_pos = g_page_top + reg_off;
    }
    return( v_pos );
}

/***************************************************************************/
/*  calc banner bottom region position                                    */
/*  this may or may not be the first region listed!                        */
/***************************************************************************/

extern  uint32_t    ban_bot_pos( banner_lay_tag * ban )
{
    uint32_t    vpos;
    uint32_t    ban_depth;

    ban_depth = ban->ban_depth;

    if( bin_driver->y_positive == 0 ) {
        vpos = bin_device->y_start - g_page_depth + ban_depth
               - ban->top_line->reg_voffset;
    } else {
        vpos = bin_device->y_start + g_page_depth - ban_depth
               + ban->top_line->reg_voffset;
        vpos--; // produces same result as wgml 4.0
    }
    return( vpos );
}

/***************************************************************************/
/*  substitute a variable in ban region text                               */
/***************************************************************************/

static char * subst_1var( char * pout, char * pvar, size_t len )
{
    sub_index           var_ind;
    symvar              symvar_entry;
    symsub          *   symsubval;
    int                 rc;
    char            *   pchar;

    ProcFlags.suppress_msg = true;
    scan_err = false;

    pchar = scan_sym( pvar, &symvar_entry, &var_ind );
    ProcFlags.suppress_msg = false;
    if( !scan_err ) {
        if( symvar_entry.flags & local_var ) {  // lookup var in dict
            rc = find_symvar_l( &input_cbs->local_dict, symvar_entry.name,
                              var_ind, &symsubval );
        } else {
            rc = find_symvar( &global_dict, symvar_entry.name, var_ind,
                              &symsubval );
        }
        if( rc == 2 ) {
            pchar = symsubval->value;
            while( *pchar ) {
                *pout++ = *pchar++;
            }
        }
    }
    *pout = '\0';
    return( pout );
}

/***************************************************************************/
/*  substitute vars in ban region buffer                                   */
/***************************************************************************/

static void substitute_vars( char * pbuf, char * pin, size_t length )
{
    char    *   p;
    char    *   pvar;
    char    *   pout;
    int         k;
    int         len;

    p = pin;
    pout = pbuf;
    for( len = 0; len < length; ++len ) {
        if( *p != '&' ) {
            *pout++ = *p++;
        } else {
            pvar = p + 1;
            for( k = len; k < length; ++k ) {
                if( *p == '.' ) {
                    break;          // var end found
                } else {
                    p++;
                }
            }
            len = k;
            if( *p == '.' ) {
                *p = '\0';
                pout = subst_1var( pout, pvar, p - pvar );
                *p++ = '.';         // restore .
            } else {
                p = pvar - 1;       // no variable treat as text
                *pout++ = *p++;
                continue;
            }
        }
    }
    *pout = '\0';
    return;
}


/***************************************************************************/
/*  prepare 1 or more text_chars with region content                       */
/*                                                                         */
/*  More than 1 ban_region may be specified for a banner in :LAYOUT        */
/*  but only the first is processed                   TBD if really needed */
/***************************************************************************/

static void content_reg( banner_lay_tag * ban )
{
    text_chars  *   curr_t;
    char        *   pbuf;
    symsub      *   symsubval;
    int             k;
    int             rc;

    switch( ban->region->contents.content_type ) {
    case   string_content:
        pbuf = mem_alloc( buf_size );
        *pbuf = '\0';
        if( ban->region->script_format ) {
            /***************************************************************/
            /*  substitute variables and create text_chars instances       */
            /***************************************************************/
            for( k = 0; k < 3; ++k ) {

                if( ban->region->script_region[k].string != NULL ) {
                    substitute_vars( pbuf, ban->region->script_region[k].string,
                                     ban->region->script_region[k].len );
                    if( *pbuf ) {
                        curr_t = alloc_text_chars( pbuf, strlen( pbuf ),
                                                   ban->region->font );

                        /***************************************************/
                        /* use font 0 for width calculation                */
                        /* even if another font is used for banregion      */
                        /* to get the same result as wgml4            TBD  */
                        /***************************************************/
                        curr_t->width = cop_text_width( curr_t->text,
                                                        curr_t->count,
                                                   //   ban->region->font );
                                                        0 );// TBD
                        reg_text[k] = curr_t;
                    }
                }
            }
        } else {    // no script format only normal string with perhaps vars
            substitute_vars( pbuf, ban->region->contents.string,
                             strlen( ban->region->contents.string ) );
            if( *pbuf ) {
                curr_t = alloc_text_chars( pbuf, strlen( pbuf ),
                                    ban->region->font );
                curr_t->width = cop_text_width( curr_t->text, curr_t->count,

                /***********************************************************/
                /*  is font 0 used for width calc?                    TBD  */
                /***********************************************************/

                                                ban->region->font );

                if( ban->region->region_position == pos_left ) {
                    reg_text[0] = curr_t;
                } else if( ban->region->region_position == pos_center ) {
                    reg_text[1] = curr_t;
                } else if( ban->region->region_position == pos_right ) {
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
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "author", 6, ban->region->font );
        }
        break;
    case bothead_content :
        rc = find_symvar( &global_dict, "$bothead", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "bothead", 7, ban->region->font );
        }
        break;
    case date_content :
        rc = find_symvar( &global_dict, "$date", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "date", 4, ban->region->font );
        }
        break;
    case docnum_content :
        rc = find_symvar( &global_dict, "$docnum", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "docnum", 6, ban->region->font );
        }
        break;
    case head0_content :
        rc = find_symvar( &global_dict, "$head0", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head0", 5, ban->region->font );
        }
        break;
    case head1_content :
        rc = find_symvar( &global_dict, "$head1", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head1", 5, ban->region->font );
        }
        break;
    case head2_content :
        rc = find_symvar( &global_dict, "$head2", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head2", 5, ban->region->font );
        }
        break;
    case head3_content :
        rc = find_symvar( &global_dict, "$head3", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head3", 5, ban->region->font );
        }
        break;
    case head4_content :
        rc = find_symvar( &global_dict, "$head4", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head4", 5, ban->region->font );
        }
        break;
    case head5_content :
        rc = find_symvar( &global_dict, "$head5", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head5", 5, ban->region->font );
        }
        break;
    case head6_content :
        rc = find_symvar( &global_dict, "$head6", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "head6", 5, ban->region->font );
        }
        break;
    case headnum0_content :
        rc = find_symvar( &global_dict, "$hnum0", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum0", 5, ban->region->font );
        }
        break;
    case headnum1_content :
        rc = find_symvar( &global_dict, "$hnum1", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum1", 5, ban->region->font );
        }
        break;
    case headnum2_content :
        rc = find_symvar( &global_dict, "$hnum2", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum2", 5, ban->region->font );
        }
        break;
    case headnum3_content :
        rc = find_symvar( &global_dict, "$hnum3", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum3", 5, ban->region->font );
        }
        break;
    case headnum4_content :
        rc = find_symvar( &global_dict, "$hnum4", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum4", 5, ban->region->font );
        }
        break;
    case headnum5_content :
        rc = find_symvar( &global_dict, "$hnum5", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum5", 5, ban->region->font );
        }
        break;
    case headnum6_content :
        rc = find_symvar( &global_dict, "$hnum6", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "hnum6", 5, ban->region->font );
        }
        break;
    case headtext0_content :
        rc = find_symvar( &global_dict, "$htext0", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext0", 5, ban->region->font );
        }
        break;
    case headtext1_content :
        rc = find_symvar( &global_dict, "$htext1", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext1", 5, ban->region->font );
        }
        break;
    case headtext2_content :
        rc = find_symvar( &global_dict, "$htext2", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext2", 5, ban->region->font );
        }
        break;
    case headtext3_content :
        rc = find_symvar( &global_dict, "$htext3", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext3", 5, ban->region->font );
        }
        break;
    case headtext4_content :
        rc = find_symvar( &global_dict, "$htext4", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext4", 5, ban->region->font );
        }
        break;
    case headtext5_content :
        rc = find_symvar( &global_dict, "$htext5", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext5", 5, ban->region->font );
        }
        break;
    case headtext6_content :
        rc = find_symvar( &global_dict, "$htext6", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "htext6", 5, ban->region->font );
        }
        break;
    case pgnuma_content :
        rc = find_symvar( &global_dict, "$pgnuma", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "pgnuma", 6, ban->region->font );
        }
        break;
    case pgnumad_content :
        rc = find_symvar( &global_dict, "$pgnumad", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumad", 7, ban->region->font );
        }
        break;
    case pgnumc_content :
        rc = find_symvar( &global_dict, "$pgnumc", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumc", 6, ban->region->font );
        }
        break;
    case pgnumcd_content :
        rc = find_symvar( &global_dict, "$pgnumcd", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumcd", 7, ban->region->font );
        }
        break;
    case pgnumr_content :
        rc = find_symvar( &global_dict, "$pgnumr", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumr", 6, ban->region->font );
        }
        break;
    case pgnumrd_content :
        rc = find_symvar( &global_dict, "$pgnumrd", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "pgnumrd", 7, ban->region->font );
        }
        break;
    case sec_content :
        rc = find_symvar( &global_dict, "$sec", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "sec", 3, ban->region->font );
        }
        break;
    case stitle_content :
        rc = find_symvar( &global_dict, "$stitle", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "stitle", 6, ban->region->font );
        }
        break;
    case title_content :
        rc = find_symvar( &global_dict, "$title", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "title", 6, ban->region->font );
        }
        break;
    case time_content :
        rc = find_symvar( &global_dict, "$time", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "time", 4, ban->region->font );
        }
        break;
    case tophead_content :
        rc = find_symvar( &global_dict, "$tophead", no_subscript, &symsubval );
        if( rc == 2 ) {
            curr_t = alloc_text_chars( symsubval->value, strlen( symsubval->value ),
                                       ban->region->font );
        } else {
            curr_t = alloc_text_chars( "tophead", 7, ban->region->font );
        }
        break;
    default:
        // the other possible banner region values are TBD

        curr_t = alloc_text_chars( "Dummy region", 12, ban->region->font );
        break;
    }

    if( ban->region->contents.content_type != string_content ) {
        curr_t->width = cop_text_width( curr_t->text, curr_t->count,

        /***********************************************************/
        /*  is font 0 used for width calc?                    TBD  */
        /***********************************************************/

                                        ban->region->font );
        if( ban->region->region_position == pos_left ) {
            reg_text[0] = curr_t;
        } else if( ban->region->region_position == pos_center ) {
            reg_text[1] = curr_t;
        } else if( ban->region->region_position == pos_right ) {
            reg_text[2] = curr_t;
        } else {
            reg_text[0] = curr_t;  // position left if invalid
        }
    }
    return;
}

/***************************************************************************/
/*  output top / bottom banner      incomplete    TBD                      */
/*  only the first banregion is output                                     */
/***************************************************************************/
static  void    out_ban_common( banner_lay_tag * ban, bool top )
{
    text_chars      *   curr_t;
    text_chars      *   curr_p;
    uint32_t            ban_left;
    uint32_t            h_left;
    uint32_t            ban_right;
    uint32_t            h_right;
    uint32_t            reg_indent;
    uint32_t            curr_x;
    int                 k;

    ProcFlags.top_ban_proc = top;       // set for top banner
    if( ban == NULL ) {
        return;
    }

    reg_text[0] = NULL;
    reg_text[1] = NULL;
    reg_text[2] = NULL;

    ban_line.first = NULL;

    /* calc banner horizontal margins */
    ban_left  = g_page_left_org + ban->ban_left_adjust;
    ban_right = g_page_right_org - ban->ban_right_adjust;

    content_reg( ban );
    curr_x = 0;

    for( k = 0; k < 3; ++k ) {          // for all region parts
        if( reg_text[k] == NULL ) {
            continue;                   // skip empty part
        }
        g_curr_font_num = reg_text[k]->font_number;
        if( ban_line.first == NULL ) {
            ban_line.first = reg_text[k];
            ban_line.line_height = wgml_fonts[reg_text[k]->font_number].line_height;
            if( top ) {
                g_cur_v_start = ban_top_pos( ban );
            } else {
                g_cur_v_start = ban_bot_pos( ban );
            }
            ban_line.y_address = g_cur_v_start;
        } else {
            ban_line.last->next = reg_text[k];
            reg_text[k]->prev = ban_line.last;
        }
        if( ban_line.line_height < wgml_fonts[reg_text[k]->font_number].line_height ) {
            ban_line.line_height = wgml_fonts[reg_text[k]->font_number].line_height;
        }
        curr_t = reg_text[k];
        ban_line.last  = reg_text[k];

        h_left  = ban_left;
        h_right = ban_right;
        reg_indent = ban->region->reg_indent;
        if( ban->region->hoffset.su_u >= SU_lay_left  ) {   // symbolic
            if( ban->region->hoffset.su_u == SU_lay_left ) {
                h_left += reg_indent;
            } else if( ban->region->hoffset.su_u == SU_lay_right ) {
                h_right -= reg_indent;
            } else if( ban->region->hoffset.su_u == SU_lay_centre ) {
                h_left += reg_indent;
            }
        } else {                            // in horiz space units
            h_left = reg_indent + ban->region->reg_hoffset;
        }

        if( ban->region->region_position == pos_center || k == 1) {
            if( h_left + curr_t->width < h_right ) {
                h_left += (h_right - h_left - curr_t->width) / 2;
                curr_x = h_left;
            }
        } else if( ban->region->region_position == pos_right || k == 2) {
            h_left = h_right - curr_t->width;
            curr_x = h_left;
        }
        if( curr_x == 0 ) {
            curr_x = h_left;
        }
        curr_t->x_address = curr_x;
        curr_x += curr_t->width;

    }
    /*******************************************************************/
    /*  adjust vertical position from upper to lower border of line    */
    /*******************************************************************/

    if( bin_driver->y_positive == 0x00 ) {
        ban_line.y_address -= ban_line.line_height;
        g_cur_v_start -= ban_line.line_height;
    } else {
        ban_line.y_address += ban_line.line_height;
        g_cur_v_start += ban_line.line_height;
    }

    if( GlobalFlags.lastpass && ban_line.first != NULL) {
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
                curr_p->width -= wgml_fonts[curr_p->font_number].width_table
                                                 [curr_p->text[curr_p->count]];
            }
            curr_p = curr_t;
        }
        fb_output_textline( &ban_line );
    }

    if( ban_line.first != NULL) {
        add_text_chars_to_pool( &ban_line );
        ban_line.first = NULL;
    }
    g_curr_font_num = layout_work.defaults.font;
    if( top ) {                        // for top banner calculate text start

    /***********************************************************************/
    /*  for page 1, the textarea starts 1 line deeper than for following   */
    /*  pages                                                       TBD    */
    /***********************************************************************/

        if( post_top_skip == 0 ) {
            if( post_skip != NULL ) {
                uint32_t pskip = conv_vert_unit( post_skip, 0 );

                if( pskip > 0 ) {
                    post_top_skip += pskip;
                }
                post_skip = NULL;
            } else {
                post_top_skip = 0;
            }
        } else {
            if( page > 1 ) {            // hack for page 1    TBD
                 post_top_skip = 0;
            }
        }
        if( bin_driver->y_positive == 0 ) {
            g_cur_v_start -= post_top_skip;
        } else {
            g_cur_v_start += post_top_skip;
        }
        post_top_skip = 0;
    }
}

/***************************************************************************/
/*  output top or bottom  banner                                           */
/***************************************************************************/
void    out_ban_top( banner_lay_tag * ban )
{
    out_ban_common( ban, true );        // true for top banner
}

void    out_ban_bot( banner_lay_tag * ban )
{
    out_ban_common( ban, false );       // false for bottom banner
}

