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
* Description:  WGML Process text not tags / controlwords
*
*
*               add_text_chars_to_pool  prepare reuse of a text_word instance
*               alloc_text_chars        create a text_chars instance
*               intrans                 perform input translation
*               process_text
*               do_justify
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"
#include "outbuff.h"


/***************************************************************************/
/*  justification  experimental                                     TBD    */
/***************************************************************************/

void    do_justify( uint32_t lm, uint32_t rm )
{

    text_chars  *tw;
    int32_t     dist;
    int32_t     dist1;
    int32_t     cnt;
    int32_t     line_width;
    int32_t     delta;
    int32_t     delta0;
    ju_enum     just;
    symsub  *   symjusub;

    if( ProcFlags.justify == ju_off || ProcFlags.literal  ) {
        return;
    }
    dist = 0;
    dist1 = 0;
    cnt = 0;
    tw = t_line.first;
    while( tw != NULL )  {              // calculate used width
        cnt++;                          // number of 'words'
        dist += tw->width;              // sum of widths
        if( tw->next == NULL ) {        // last element
            dist1 = tw->x_address + tw->width;
        }
        tw = tw->next;
    }
    line_width = rm - lm;

    if( (dist <= 0) || (dist1 > rm) || (line_width < 1) ) {
        return;                         // no justify needed / possible
    }
    delta0 = line_width + t_line.first->x_address - dist1;
    if( ProcFlags.justify == ju_on ) {
        if( cnt < 2 ) {
            return;
        }
    }
    if( cnt < 2 ) {
        delta = delta0;
    } else {
        delta = delta0 / (cnt - 1);
    }

    if( GlobalFlags.research && GlobalFlags.lastpass ) {
        find_symvar( &sys_dict, "$ju", no_subscript, &symjusub);// .ju as string
        out_msg( "\n  ju_%s lm:%d rm:%d line_width:%d dist:%d dist1:%d"
                 " delta:%d delta0:%d cnt:%d\n", symjusub->value,
                 lm, rm, line_width, dist, dist1, delta, delta0, cnt );
    }
    if( delta < 1 ) {                   // nothing to distribute
        return;
    }
    switch( ProcFlags.justify ) { // convert inside / outside to left / right
    case ju_inside :                    // depending on odd / even page
        if( page & 1 ) {
            just = ju_left;
        } else {
            just = ju_right;
        }
        break;
    case ju_outside :
        if( page & 1 ) {
            just = ju_right;
        } else {
            just = ju_left;
        }
        break;
    default :
        just = ProcFlags.justify;
        break;
    }

    switch( just ) {
    case  ju_half :
        delta /= 2;
        if( delta < 1 ) {
            break;
        }
        // falltrough
    case  ju_on :
        if( t_line.first->x_address < lm ) {
            break;                      // left of left margin no justify
        }
        delta0 = delta;
        tw = t_line.first->next;
        while( tw != NULL ) {
               tw->x_address += delta;
               delta += delta0;
               tw = tw->next;
        }
        break;
    case  ju_left :
        if( t_line.first->x_address <= lm ) {
            break;                      // already left
        }
        delta = t_line.first->x_address - lm;   // shift to the left
        if( delta < 1 ) {
            break;
        }
        tw = t_line.first;
        while( tw != NULL ) {
               tw->x_address += delta;
               tw = tw->next;
        }
        break;
    case  ju_right :
        if( dist1 >= rm ) {
            break;                      // already at right margin
        }
        delta = rm - dist1;             // shift right
        if( delta < 1 ) {
            break;
        }
        tw = t_line.first;
        while( tw != NULL ) {
               tw->x_address += delta;
               tw = tw->next;
        }
        break;
    case  ju_centre :
        if( dist1 >= rm ) {
            break;                      // too wide no centre possible
        }
        delta = (rm - dist1) / 2;
        if( delta < 1 ) {
            break;
        }
        tw = t_line.first;
        while( tw != NULL ) {
               tw->x_address += delta;
               tw = tw->next;
        }
        break;
    default:
        break;
    }
}


/***************************************************************************/
/*  if input translation is active                                         */
/*      look for input escape char and translate the follwoing char,       */
/*      delete the escape char                                             */
/***************************************************************************/

static  void    intrans( char * data, uint16_t * len, uint8_t font )
{
    char    *   ps;                     // source ptr
    char    *   pt;                     // target ptr
    uint32_t    k;

    if( !ProcFlags.in_trans ) {
        return;                         // input translation not active
    }
    k = *len;
    ps = data;
    pt = data;
    for( k = 0; k <= *len; k++ ) {
        if( *ps == in_esc ) {           // translate needed
            ps++;                       // skip escape char
            k++;                        // and count
            *pt = cop_in_trans( *ps, font );   // translate
            ps++;
            pt++;
        } else {
            *pt++ = *ps++;              // else copy byte
        }
    }
    if( pt < ps ) {                     // something translated
        *len -= (ps - pt);              // new length
        *pt = ' ';
    }
}

/***************************************************************************/
/*  allocate / reuse and init a text_chars  instance                        */
/***************************************************************************/

static text_chars    * alloc_text_chars( char * p, size_t cnt, uint8_t font_num )
{
    text_chars   *   curr;
    text_chars   *   prev;

    if( text_pool != NULL ) {
        curr = text_pool;
        prev = text_pool;
        while( (curr != NULL) && (curr->length <= cnt) ) {
            prev = curr;
            curr = curr->next;
        }
        if( curr == prev ) {            // first is large enough
            text_pool = curr->next;
        } else {
            if( curr == NULL ) {        // no one large enough found
                curr = mem_alloc( sizeof( *curr ) + cnt );
                curr->length = cnt;     // set max text size
            } else {
                prev->next = curr->next;// unchain curr
            }
        }
    } else {                            // pool is empty
        curr = mem_alloc( sizeof( *curr ) + cnt );
        curr->length = cnt;             // set max text size
    }

    curr->next = NULL;
    curr->font_number = font_num;
    curr->width = 0;
    curr->count = cnt;                  // set current size
    memcpy_s(curr->text, cnt + 1, p, cnt ); // and copy text
    curr->text[cnt] = 0;

    return( curr );
}


/***************************************************************************/
/*  add text_chars instance to free pool                                   */
/***************************************************************************/

void    add_text_chars_to_pool( text_line * a_line )
{
    text_chars           *   tw;

    if( text_pool == NULL ) {        // add text_chars chars to pool for reuse
        text_pool = a_line->first;
    } else {
        tw = text_pool;
        while( tw->next != NULL ) {
            tw = tw->next;
        }
        tw->next = a_line->first;
    }
}


/***************************************************************************/
/*                                                                         */
/***************************************************************************/

void    process_line_full( text_line * a_line )
{
    if( a_line->first == NULL ) {
        return;
    }
    if( GlobalFlags.lastpass ) {
        if( GlobalFlags.research ) {
            test_out_t_line( a_line );
        }
        if( !ProcFlags.literal && ProcFlags.justify > ju_off ) {

            do_justify( g_page_left, g_page_left + g_cl );
            if( GlobalFlags.research ) {
                test_out_t_line( a_line );
            }
        }
    }
    fb_output_textline( a_line );

    add_text_chars_to_pool( a_line );
    a_line->first = NULL;
    g_cur_h_start = g_page_left;

    if( bin_driver->y_positive == 0x00 ) {// single line spacing assumed for now
        g_cur_v_start -= (1 * g_max_line_height);
    } else {
        g_cur_v_start += (1 * g_max_line_height);
    }

}


/***************************************************************************/
/*  process text                                                           */
/*      split into 'words'                                                 */
/*      translate if input translation active                              */
/*      calculate width with current font                                  */
/*      add text to output line                                 TBD        */
/***************************************************************************/

void    process_text( char * text, uint8_t font_num )
{
    static  text_chars   *   text_wk;
    text_chars           *   curr_t;
    size_t                  count;
    char                *   pb;
    char                *   p;

    p = pb = text;
    while( *(++p) ) {
        if( *p != ' ' ) {               // no space no word end
            continue;
        }
        if( ProcFlags.in_trans && *(p - 1) == in_esc ) {
            continue;                   // guarded space no word end
        } else {
            if( (*(p - 1) == ' ') || (*(p + 1) == ' ') ) {
                while( *p == ' ' ) {    // more than 1 space no word end
                    p++;
                }
                p--;
            } else {                    // word end
                count = p - pb;         // no of bytes
                curr_t = alloc_text_chars( pb, count, font_num );

                intrans( curr_t->text, &curr_t->count, font_num );
                curr_t->x_address = g_cur_h_start;
                curr_t->width = cop_text_width( curr_t->text,
                                                curr_t->count,
                                                font_num );
                if( g_cur_h_start + curr_t->width > g_page_right ) {
                    process_line_full( &t_line );
                    curr_t->x_address = g_page_left;

                }

                if( t_line.first == NULL ) {
                    t_line.first = curr_t;
                    t_line.y_address = g_cur_v_start;
                } else {
                    text_wk->next = curr_t;
//                    curr_t->x_address += wgml_fonts[font_num].spc_width;
                }
                text_wk = curr_t;
                g_cur_h_start += curr_t->width + wgml_fonts[font_num].spc_width;

                pb = p + 1;             // new word start
            }
        }
    }
    if( p > pb ) {                      // last word
        count = p - pb;                 // no of bytes
        curr_t = alloc_text_chars( pb, count, font_num );

        intrans( curr_t->text, &curr_t->count, g_curr_font_num );
        curr_t->x_address = g_cur_h_start;
        curr_t->width = cop_text_width( curr_t->text, curr_t->count,
                                        font_num );

        if( g_cur_h_start + curr_t->width > g_page_right ) {

            process_line_full( &t_line );
            curr_t->x_address = g_page_left;
        }

        if( t_line.first == NULL ) {
            t_line.first = curr_t;
            t_line.y_address = g_cur_v_start;
        } else {
            text_wk->next = curr_t;
//            curr_t->x_address += wgml_fonts[font_num].spc_width;
        }
        text_wk = curr_t;
        g_cur_h_start += curr_t->width + wgml_fonts[font_num].spc_width;
    }

    if( !ProcFlags.concat && (t_line.first != NULL) && GlobalFlags.lastpass) {

        process_line_full( &t_line );


    }
}

