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
* Description:  WGML tag :BINCLUDE processing
*
****************************************************************************/
#define __STDC_WANT_LIB_EXT1__  1
#include <string.h>
#include    "wgml.h"
//#include    "findfile.h"
#include    "gvars.h"


/***************************************************************************/
/*  :BINCLUDE tag                                                          */
/***************************************************************************/

void    gml_binclude( const gmltag * entry )
{
    bool        depth_found             = false;
    bool        file_found              = false;
    bool        has_rec_type            = false;
    bool        reposition;
    bool        reposition_found        = false;
    char        file[FILENAME_MAX];
    char        rt_buff[MAX_FILE_ATTR];
    char    *   p;
    su          cur_su;
    uint32_t    depth;

    if( (ProcFlags.doc_sect < doc_sect_gdoc) ) {
        if( (ProcFlags.doc_sect_nxt < doc_sect_gdoc) ) {
            xx_tag_err( err_tag_before_gdoc, entry->tagname );
            scan_start = scan_stop + 1;
            return;
        }
    }
    file[0] = '\0';
    rt_buff[0] = '\0';
    p = scan_start;
    for( ;; ) {
        while( *p == ' ' ) {            // over WS to attribute
            p++;
        }
        if( *p == '\0' ) {              // end of line: get new line
            if( !(input_cbs->fmflags & II_eof) ) {
                if( get_line( true ) ) {      // next line for missing attribute
 
                    process_line();
                    scan_start = buff2;
                    scan_stop  = buff2 + buff2_lg;
                    if( (*scan_start == SCR_char) ||    // cw found: end-of-tag
                        (*scan_start == GML_char) ) {   // tag found: end-of-tag
                        ProcFlags.tag_end_found = true; 
                        break;          
                    } else {
                        p = scan_start; // new line is part of current tag
                        continue;
                    }
                }
            }
        }
        if( !strnicmp( "file", p, 4 ) ) {
            p += 4;
            p = get_att_value( p );
            if( val_start == NULL ) {
                break;
            }
            file_found = true;
            memcpy_s( file, FILENAME_MAX, val_start, val_len );
            if( val_len < FILENAME_MAX ) {
                file[val_len] = '\0';
            } else {
                file[FILENAME_MAX - 1] = '\0';
            }
            split_attr_file( file, rt_buff, MAX_FILE_ATTR );
            if( (rt_buff[0] != '\0') ) {
                has_rec_type = true;
                if( rt_buff[0] != 't' ) {
                    xx_warn( wng_rec_type_binclude );
                }
            }
            if( ProcFlags.tag_end_found ) {
                break;
            }
        } else if( !strnicmp( "depth", p, 5 ) ) {
            p += 5;
            p = get_att_value( p );
            if( val_start == NULL ) {
                break;
            }
            depth_found = true;
            if( att_val_to_SU( &cur_su, true ) ) {
                return;
            }
            depth = conv_vert_unit_rdd( &cur_su, spacing );
            if( ProcFlags.tag_end_found ) {
                break;
            }
        } else if( !strnicmp( "reposition", p, 10 ) ) {
            p += 10;
            p = get_att_value( p );
            if( val_start == NULL ) {
                break;
            }
            reposition_found = true;
            if( !strnicmp( "start", val_start, 5 ) ) {
                reposition = true;  // moving following text down by depth
            } else if( !strnicmp( "end", val_start, 3 ) ) {
                reposition = false; // device at proper position after insertion
            } else {
                xx_line_err( err_inv_att_val, val_start );
                scan_start = scan_stop + 1;
                return;
            }
            if( ProcFlags.tag_end_found ) {
                break;
            }
        } else {    // no match = end-of-tag in wgml 4.0
            ProcFlags.tag_end_found = true;
            break;
        }
    }
    // detect missing required attributes
    if( !depth_found || !file_found || !reposition_found ) {
        xx_err( err_att_missing );
        scan_start = scan_stop + 1;
        return;
    }
out_msg( ":BINCLUDE file name: %s\n", file );
out_msg( ":BINCLUDE depth: %i\n", depth );
if( reposition ) {
    out_msg( ":BINCLUDE reposition: start\n" );
} else {
    out_msg( ":BINCLUDE reposition: end\n" );
}
    start_doc_sect();                   // if not already done

/// now call the implementation code, once it is written.

    scan_start = scan_stop + 1;         // skip following text
}

