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
* Description:  WGML tags :CIT :eCIT :HP0 :eHP0 :HP1, :eHP1 :HP2, :eHP2
*                         :HP3, :eHP3, :Q, :eQ, :SF, and :eSF processing
*
* These tags all begin/end some form of inline phrase
*
****************************************************************************/
#include    "wgml.h"
#include    "gvars.h"

static  char    *       double_q    = "\""; // string for output of '"'
static  char    *       single_q    = "'";  // string for output of "'"
static  font_number     tt_font     = 0;    // font number to be replaced with "0"
static  uint32_t        quote_lvl   = 0;    // nesting level of Q phrases

/***************************************************************************/
/*  :CIT :HPx :Q :SF common processing                                        */
/***************************************************************************/

static void gml_inline_common( const gmltag * entry, int level, e_tags t )
{
    char    *   p;

    // keep any existing post_space, even if CT follows

    if( (input_cbs->fmflags & II_sol) ) {
        ProcFlags.fsp = true;
        if( post_space == 0 ) {
            post_space = wgml_fonts[g_curr_font].spc_width;
        }
        if( t_line != NULL && ProcFlags.utc ) {  // add second space after stop
            if( is_stop_char( t_line->last->text[t_line->last->count - 1] ) ) {
                post_space += wgml_fonts[g_curr_font].spc_width;
            }
        }
    }

    init_nest_cb();
    nest_cb->p_stack = copy_to_nest_stack();

    g_phrase_font = level;
    if( level >= wgml_font_cnt ) {
        level = FONT0;
    }
    nest_cb->font = level;
    g_curr_font = level;

    nest_cb->c_tag = t;

    nest_cb->align = nest_cb->prev->align;
    nest_cb->left_indent = nest_cb->prev->left_indent;
    nest_cb->right_indent = nest_cb->prev->right_indent;


    if( nest_cb->prev != NULL ) {               // at least one prior entry
        if( nest_cb->prev->prev == NULL ) {     // but only one
            if( nest_cb->font != nest_cb->prev->font ) {           // font actually changed
                tt_font = level;                // save current value
            }
        }
    }

    if( t == t_Q ) {                            // Q/eQ inserts quote char
        if( (quote_lvl % 2) ) {
            process_text( single_q, g_curr_font );
        } else {
            process_text( double_q, g_curr_font );
        }
        quote_lvl++;
    }

    scan_err = false;
    p = scan_start;
    if( *p == '.' ) p++;                // over '.'
    if( *p ) {
        process_text( p, g_curr_font );
    }
    if( !ProcFlags.concat && (input_cbs->fmflags & II_eol)
            && (input_cbs->fmflags & II_file) ) {
        scr_process_break();            // ensure line is output
    }
    scan_start = scan_stop + 1;
    return;
}


/***************************************************************************/
/*  :HP0  :HP1  :HP2  :HP3                                                 */
/*                                                                         */
/* Format: :HPn. (n=0,1,2,3)                                               */
/* These tags start the highlighting of phrases at one of the four levels  */
/* provided by GML. The actual highlighting to be performed is determined  */
/* by the type of device for which the document is being formatted.        */
/* Examples of highlighting include underlining, displaying in bold face,  */
/* or using a different character shape (such as italics).                 */
/* Highlighting may not be used when the GML layout explicitly determines  */
/* the emphasis to be used, such as in the text of a heading.              */
/* The highlighting tags are paragraph elements. They are used with text   */
/* to create the content of a basic document element, such as a paragraph. */
/* A corresponding :EHPn tag must be specified for each :HPn tag.          */
/***************************************************************************/

void gml_hp0( const gmltag * entry )
{
    gml_inline_common( entry, 0, t_HP0 );
}

void gml_hp1( const gmltag * entry )
{
    gml_inline_common( entry, 1, t_HP1 );
}

void gml_hp2( const gmltag * entry )
{
    gml_inline_common( entry, 2, t_HP2 );
}

void gml_hp3( const gmltag * entry )
{
    gml_inline_common( entry, 3, t_HP3 );
}


/***************************************************************************/
/*  :eCIT :eHPx :eQ :eSF common processing                                           */
/***************************************************************************/

static void gml_e_inlne_common( const gmltag * entry, e_tags t )
{
    char    *   p;
    tag_cb  *   wk;

    if( nest_cb->c_tag != t ) {         // unexpected exxx tag
        if( nest_cb->c_tag == t_NONE ) {
            g_err_tag_no( str_tags[t + 1] );// no exxx expected
        } else {
            g_err_tag_nest( str_tags[nest_cb->c_tag + 1] ); // exxx expected
        }
    } else {
        if( nest_cb->prev->font == tt_font ) {    // returning to second stack entry
            tt_stack = nest_cb->prev;             // set tt_stack 
        }
        if( nest_cb == tt_stack ) {         // closing second stack entry
            tt_stack = NULL;                // clear tt_stack 
        }
        nest_cb->prev->left_indent = nest_cb->left_indent;
        nest_cb->prev->right_indent = nest_cb->right_indent;
        wk = nest_cb;
        nest_cb = nest_cb->prev;
        add_tag_cb_to_pool( wk );
        if( t != t_Q ) {                    // Q/eQ does not restore the prior font
            g_curr_font = nest_cb->font;
        }

        // recompute space at SOL if inline end tag - TBD
        if( (post_space !=0) && (input_cbs->fmflags & II_sol) ) {
            post_space = wgml_fonts[g_curr_font].spc_width;

            if( (t_line != NULL) && (t_line->last != NULL) ) {  // add second space after stop
                if( is_stop_char( t_line->last->text[t_line->last->count - 1] ) ) {
                    post_space += wgml_fonts[g_curr_font].spc_width;
                }
            }
        }

        if( t == t_Q ) {                    // Q/eQ insert quote character
            quote_lvl--;
            if( (quote_lvl % 2) ) {
                process_text( single_q, g_curr_font );
            } else {
                process_text( double_q, g_curr_font );
            }
        }

        scan_err = false;
        p = scan_start;
        if( *p == '.' ) p++;            // over '.'
        if( *p ) {
            process_text( p, g_curr_font );
        }
        if( !ProcFlags.concat && (input_cbs->fmflags & II_eol)
                && (input_cbs->fmflags & II_file) ) {
            scr_process_break();        // ensure line is output
        }
    }
    scan_start = scan_stop + 1;
}


/***************************************************************************/
/*                                                                         */
/* EHP0, EHP1, EHP2, EHP3                                                  */
/*                                                                         */
/* Format: :eHPn. (n=0,1,2,3)                                              */
/* These tags end the highlighting of phrases at one of the four levels    */
/* provided by GML.                                                        */
/* Each :ehpn tag must be preceded by a corresponding :hpn tag.            */
/***************************************************************************/

void gml_ehp0( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_HP0 );
}

void gml_ehp1( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_HP1 );
}

void gml_ehp2( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_HP2 );
}

void gml_ehp3( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_HP3 );
}

/***************************************************************************/
/*  :esf tag processing                                                    */
/*                                                                         */
/*   Format: :eSF.                                                         */
/*                                                                         */
/*   This tag ends the highlighting of phrases started by the last :sf tag */
/***************************************************************************/

void gml_esf( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_SF );
}


/***************************************************************************/
/*  :SF  processing                                                        */
/*                                                                         */
/*  Format: :SF font=number.                                               */
/*  The set font tag starts the highlighting of phrases at the level       */
/*  specified by the required attribute font. The actual highlighting      */
/*  to be performed is determined by the type of device for which the      */
/*  document is being formatted. Examples of highlighting include          */
/*  underlining, displaying in bold face, or using a different             */
/*  character shape (such as italics).                                     */
/*  The value of the font attribute is a non-negative integer number.      */
/*  If the specified number is larger than the last defined font for the   */
/*  document, font for zero is used. Highlighting may not be used when     */
/*  the GML layout explicitly determines the emphasis to be used, such     */
/*  as in the text of a heading. The set font tag is a paragraph element.  */
/*  It is used with text to create the content of a basic document element,*/
/*  such as a paragraph. A corresponding :ESF tag must be specified for    */
/*  each :SF tag.                                                          */
/*                                                                         */
/*  NOTE:                                                                  */
/*    A font number greater than the maximum font number will indeed be    */
/*    replaced by "0", but it cannot be done here because subsequent       */
/*    processing needs to know what the actual font was                    */
/***************************************************************************/

void gml_sf( const gmltag * entry )
{
    char    *   p;
    char    *   pe;
    long        font;

    p = scan_start;
    p++;
    while( *p == ' ' ) {
        p++;
    }
    if( !strnicmp( "font", p, 4 ) ) {
        p += 4;
        while( (*p == ' ') || (*p == '=') ) {
            p++;
        }
        pe = p;
        while( (*pe >= '0') && (*pe <= '9') ) {
            pe++;
        }
        if( *pe && ( (*pe != '.') && (*pe != ' ')) ) { // not properly formed
            xx_err( ERR_NUM_TOO_LARGE );
        } else {
            font = strtol( p, &pe, 10 );
            scan_start = pe;
            gml_inline_common( entry, font, t_SF );
        }
    } else {
        err_count++;
        // AT-001 Required attribute not found
        g_err( err_att_missing );
        file_mac_info();
    }
    scan_start = scan_stop + 1;
    return;
}


/********************************************************************************************/
/* Format: :CIT.                                                                            */
/*                                                                                          */
/* This tag starts the highlighting of a citation (e.g., the title of a book). The actual   */
/* highlighting to be performed is determined by the layout and the type of output device   */
/* the document is processed for. Examples of highlighting include underlining,             */
/* displaying in bold face, or using a different character shape (such as italics).         */
/*                                                                                          */
/* A citation may not be used where the GML layout explicitly determines the emphasis to    */
/* be used, such as in the text of a heading.                                               */
/*                                                                                          */
/* The citation tag is a paragraph element. It is used with text to create the content of a */
/* basic document element, such as a paragraph. A corresponding :ecit tag must be           */
/* specified for each :cit tag.                                                             */
/*                                                                                          */
/********************************************************************************************/

void gml_cit( const gmltag * entry )
{
    gml_inline_common( entry, layout_work.cit.font, t_CIT );
    return;
}


/************************************************************************************/
/* Format: :eCIT.                                                                   */
/*                                                                                  */
/* This tag ends the highlighting of a citation. A corresponding :cit tag must be   */
/* previously specified for each :ecit tag.                                         */
/*                                                                                  */
/************************************************************************************/

void gml_ecit( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_CIT );
}


/***********************************************************************************************/
/* Format: :Q.                                                                                 */
/*                                                                                             */
/* This tag starts a quote. The quote is enclosed in double quotation marks. When quotes       */
/* are specified within other quotes, they are alternately enclosed by single and double       */
/* quotation marks.                                                                            */
/* The quote tag is a paragraph element. It is used with text to create the content of a basic */
/* document element, such as a paragraph. A corresponding :eq tag must be specified for        */
/* each :q tag.                                                                                */
/*                                                                                             */
/* NOTE: Q always uses font 0, even when the value of attribute font of the LAYOUT tag         */
/*       DEFAULT has a different value.                                                        */
/*                                                                                             */
/***********************************************************************************************/

void gml_q( const gmltag * entry )
{
    gml_inline_common( entry, FONT0, t_Q );
    return;
}


/************************************************************************************/
/* Format: :eQ.                                                                     */
/* This tag signals the end of a quote. A corresponding :q tag must be previously   */
/* specified for each :eq tag.                                                      */
/*                                                                                  */
/* NOTE: eQ does not restore the prior font in wgml 4.0, and so also here.         */
/*                                                                                  */
/************************************************************************************/

void gml_eq( const gmltag * entry )
{
    gml_e_inlne_common( entry, t_Q );
}

