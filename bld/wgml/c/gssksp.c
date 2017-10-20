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
* Description: implement script control words .sk (skip) and .sp (space)
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include "wgml.h"
#include "gvars.h"

static  int32_t    vspace  = 0;                 // vertical space entered (vbus)

static void sksp_common( void )
{
    bool            a_seen          = false;    // records use of operand A (or ABS)
    bool            c_seen          = false;    // records use of operand C (or COND)
    bool            scanerr         = false;
    char        *   p;
    char        *   pa;
    size_t          len;
    su              spskwork;
    uint32_t        line_spacing    = spacing;  // forced to "1" if A (ABS) is used with integer

    p = scan_start;

    if( *p ) {
        while( *p == ' ' ) {
            p++;
        }
        pa = p;
 
        while( *p && *p != ' ' ) {          // end of word
            p++;
        }
        len = p - pa;

        if( len > 0 ) {                     // arguments exist
            p = pa;
            scanerr = cw_val_to_su( &p, &spskwork );
            if( scanerr ) {
                p = pa;                     // reset scan pointer if no space value found
            }

            while( *p ) {                   // the operands can appear in either order, or not at all
                while( *p == ' ' ) {
                    p++;
                }

                pa = p;
                while( *pa && (*pa != ' ') ) {
                    pa++;
                }
                len = pa - p;
                if( !a_seen && (len <= 3) ) {
                    if( !memicmp( p, "abs", len ) ) {   // wgml 4.0 matches 'a', 'ab', 'abs' only
                        a_seen = true;
                        p = pa;
                        continue;
                    }
                }

                if( !c_seen && (len <= 4) ) {
                    if( !memicmp( p, "cond", len ) ) {  // wgml 4.0 matches 'c', 'co', 'con', 'cond' only
                        c_seen = true;
                        p = pa;
                        continue;
                    }
                }

                if( *p ) {                              // more text on line
                    xx_line_err( err_parm_invalid, p );
                    break;                              // avoids looping
                }
            }
        }
    }

    if( c_seen && (vspace > 0) ) {
//        ProcFlags.sk_cond = true;           // conditional skip
    }

    if( !scanerr ) {
        vspace = conv_vert_unit( &spskwork, 1, g_curr_font );
    }

    if( vspace == 0 ) {                     // no vertical space value specified
        vspace = 1;                         // set default value
    }

    if( vspace <= -1 ) {
        ProcFlags.overprint = true;     // enable overprint
        vspace = 0;                     // avoid evaluating negative spacing
    } else {
        ProcFlags.overprint = false;    // disable overprint
    }

    if( (vspace > 0) && (spskwork.su_u == SU_chars_lines) ) { // special processing for integers
        if( a_seen ) {
            line_spacing = 1;               // with abs always single spacing
        }
        vspace = (line_spacing * spskwork.su_whole * (int32_t)bin_device->vertical_base_units ) / LPI;
    }

    if( (blank_lines > 0) || g_space > 0 ) {
        ProcFlags.sk_2nd = true;
    }

    return;
}


/**************************************************************************/
/* SKIP generates the specified number of blank lines.                    */
/*                                                                        */
/*      ����������������������������������������������������������Ŀ      */
/*      |       |                                                  |      */
/*      |  .SK  |    <1|v>  <A>  <C>                               |      */
/*      |       |                                                  |      */
/*      ������������������������������������������������������������      */
/*                                                                        */
/* This control word causes a break.   SKIPs  that occur at the top of an */
/* output column or page will not be printed;  this includes SKIPs at the */
/* start of any in-storage text block that  prints at the top of a column */
/* or page.                                                               */
/*                                                                        */
/* <1|n>:  If used without an integer operand,  "1" will be assumed.   An */
/*    operand of zero (0) is equivalent to the .BR control word.   If the */
/*    operand is minus one (-1),  the next  input text line will be over- */
/*    printed  on the  last output  line and  will not  count toward  the */
/*    number of lines  in the text area.   For values  greater than zero, */
/*    there will be  "v" blank lines generated if Single  Spacing (.SS or */
/*    .LS 0) is in effect.   If Multiple Line Spacing (.DS or .LS >0)  is */
/*    in effect then "v" times the line  spacing plus one blank lines are */
/*    generated.   For example,  in Double Space mode a ".SK 2" generates */
/*    four blank lines.                                                   */
/* <1|v> <A> <C>:  The "A" or "ABS"  operand may be specified to generate */
/*    only the specified number of blank  lines regardless of the current */
/*    .LS value.                                                          */
/*       The "C" or  "COND" operand may be specified to  define a "condi- */
/*    tional skip".    The effect of a  conditional skip depends  on what */
/*    follows.  If followed by output lines generated by a SKIP or SPACE, */
/*    the result will be the larger of the two requests.   If either is a */
/*    conditional space, then the result will be processed as a SPACE and */
/*    will generate blank lines even at the top of a column or page.   If */
/*    followed by a text output line, the "conditional skip" line(s) will */
/*    be printed before the text output line.  Conditional skips are also */
/*    ignored at the top of a column or page,  including those that occur */
/*    at the beginning  of in-storage blocks that  print at the top  of a */
/*    column or page.   If an in-storage text block ends with conditional */
/*    skips,  those conditional  skips will be put into  effect after the */
/*    block has printed, rather than as part of the block.                */
/*                                                                        */
/* When .SK -1 is used to generate an overprint line,  the visual appear- */
/* ance of the result  is dependent on whether the output  device has the */
/* ability to overprint lines.   For output directed to the line printer, */
/* and for output to online terminals that have a negative linefeed capa- */
/* bility,  the  result will appear  properly.   For output  devices that */
/* cannot handle printing  one line on top of another  the overprint line */
/* will display on the  subsequent line,  even though it will  not add to */
/* SCRIPT's internal counting of the number of lines in the text area for */
/* pagination purposes.                                                   */
/*                                                                        */
/**************************************************************************/

void    scr_sk( void )
{
    scr_process_break();
    sksp_common();                  // set vspace
    if( vspace > g_skip ) {         // merge with existing value
        g_skip = vspace;
    }

    scan_restart = scan_stop + 1;
    return;
}


/***************************************************************************/
/* SPACE generates the specified number of blank output lines.             */
/*                                                                         */
/*      ����������������������������������������������������������Ŀ       */
/*      |       |                                                  |       */
/*      |  .SP  | <1|v> <A> <C>                                    |       */
/*      |       |                                                  |       */
/*      ������������������������������������������������������������       */
/*                                                                         */
/* This control word causes a break. The operands and the results are      */
/* identical to those for the SKIP (.SK) control word with the exception   */
/* that SPACE lines are never thrown away at the top of the page or        */
/* column when .LE YES is in effect. For details, see the .SK description. */
/*                                                                         */
/* NOTE: SP ignores "A" in wgml 4.0                                        */
/*                                                                         */
/***************************************************************************/

void    scr_sp( void )
{
    scr_process_break();
    sksp_common();                  // set vspace
    if( vspace > g_space ) {        // merge with existing value
        g_space = vspace;
    }

    scan_restart = scan_stop + 1;
    return;
}

