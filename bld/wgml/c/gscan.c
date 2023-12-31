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
* Description:  utility functions for wgml input line scanning
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include "wgml.h"
#include "gvars.h"


/***************************************************************************/
/*    GML tags                                                             */
/***************************************************************************/

#define pickg( name, length, routine, gmlflags, locflags ) { #name, length, routine, gmlflags, locflags },

static  const   gmltag  gml_tags[] = {

#include "gtags.h"
    { "   ", 0, NULL, 0, 0 }            // end

};

#define GML_TAGMAX  (sizeof( gml_tags ) / sizeof( gml_tags[0] ) - 1)

#undef pick


/***************************************************************************/
/*    GML layout tags                                                      */
/***************************************************************************/

#define pick( name, length, routine, gmlflags, locflags ) { #name, length, routine, gmlflags, locflags },

static  const   gmltag  lay_tags[] = {

#include "gtagslay.h"
    { "   ", 0, NULL, 0, 0 }            // end

};

#define LAY_TAGMAX  (sizeof( lay_tags ) / sizeof( lay_tags[0] ) - 1)

#undef pick


/***************************************************************************/
/*    SCR control words                                                    */
/***************************************************************************/

#define picks( name, routine, flags) { #name, routine, flags },
#define picklab( name, routine, flags) { #name, routine, flags },

static  const   scrtag  scr_tags[] = {

#include "gscrcws.h"

    { "  ", NULL, 0   }                 // end
};

#define SCR_TAGMAX  (sizeof( scr_tags ) / sizeof( scr_tags[0] ) - 1)

#undef pick
#undef pickg
#undef picklab
#undef picks

void set_overload( gtentry * in_gt )
{
    int     k;
    uint8_t len;        // user tag name max length is 15
    
    in_gt->overload = false;
    len = strlen( in_gt->name );
    for( k = 0; k < GML_TAGMAX; ++k ) {
        if( len == gml_tags[k].taglen ) {
            if( !strcmpi( gml_tags[k].tagname, in_gt->name ) ) {
                in_gt->overload = true;
                break;
            }
        }
    }
    return;
}

/***************************************************************************/
/*  scan for gml tags                                                      */
/***************************************************************************/

static void scan_gml( void )
{
    inputcb     *   cb;
    char        *   p;
    int             toklen;
    int             k;
    char            csave;
    bool            processed;
    gtentry     *   ge;                 // GML user tag entry
    mac_entry   *   me;                // script macro for processing GML tag
    char            linestr[MAX_L_AS_STR];
    char            tok_upper[TAG_NAME_LENGTH + 1];

    cb = input_cbs;

    p = scan_start + 1;
    tok_start = scan_start;
    while( is_id_char( *p ) && p <= scan_stop ) { // search end of TAG
        p++;
    }
    scan_start = p;                      // store argument start address
    toklen = p - tok_start - 1;
    csave = *p;
    *p = '\0';
    if( toklen >= TAG_NAME_LENGTH ) {
        err_count++;
        // SC--009 The tagname is too long
        if( cb->fmflags & II_tag_mac ) {
            utoa( cb->s.m->lineno, linestr, 10 );
            g_err( err_tag_name, tok_start + 1, linestr, "macro",
                   cb->s.m->mac->name );
        } else {
            utoa( cb->s.f->lineno, linestr, 10 );
            g_err( err_tag_name, tok_start + 1, linestr, "file",
                   cb->s.f->filename );
        }
        if( inc_level > 0 ) {
            show_include_stack();
        }
        *p = csave;
        scan_start = tok_start;         // process as text
        return;
    }

    if( GlobalFlags.firstpass && cb->fmflags & II_research ) {

        if(  stricmp( tok_start + 1, "cmt" ) ) {   // quiet for :cmt.

            if( cb->fmflags & II_tag_mac ) {
                printf_research( "L%d    %c%s tag found in macro %s(%d)\n\n",
                                 inc_level, GML_char, tok_start + 1,
                                 cb->s.m->mac->name, cb->s.m->lineno );
            } else {
                printf_research( "L%d    %c%s tag found in file %s(%d)\n\n",
                                 inc_level, GML_char, tok_start + 1,
                                 cb->s.f->filename, cb->s.f->lineno );
            }
        }
        add_GML_tag_research( tok_start + 1 );
    }

    if( ProcFlags.layout ) {
        ge = NULL;                      // no user tags within :LAYOUT
    } else {
        ge = find_tag( &tag_dict, tok_start + 1 );
    }
    processed = false;
    me = NULL;
    if( ge != NULL ) {                  // GML user defined Tag found
        *p = csave;
        if( ge->tagflags & tag_off ) {  // inactive, treat as text
            scan_start = tok_start;
            return;
        }
        me = find_macro( macro_dict, ge->macname );
        if( me == NULL ) {
            err_count++;
            // SC--037: The macro 'xxxxxx' for the gml tag 'yyyyy'
            //          is not defined
            if( cb->fmflags & II_tag_mac ) {
                utoa( cb->s.m->lineno, linestr, 10 );
                g_err( err_tag_macro,
                         ge->macname, ge->name,
                         linestr, "macro", cb->s.m->mac->name );
            } else {
                utoa( cb->s.f->lineno, linestr, 10 );
                g_err( err_tag_macro,
                         ge->macname, ge->name,
                         linestr, "file", cb->s.f->filename );
            }
            if( inc_level > 0 ) {
                show_include_stack();
            }
            *p = csave;
            scan_start = tok_start;         // process as text
            return;
        } else {

            /*******************************************************************/
            /*  When a user-defined tag which overloads a predefined tag (ie,  */
            /*  the names are the same) is used inside a macro, whether that   */
            /*  macro is used with a user-defined tag or not, the predefined   */
            /*  tag is used instead by wgml 4.0.                               */
            /*                                                                 */
            /*  Note that this allows a macro used with a user-defined tag to  */
            /*  use that tag name without any danger of recursion, but is far  */
            /*  more general than simply preventing recursive user-defined tag */
            /*  definitions.                                                   */
            /*******************************************************************/

            if( (cb->fmflags & II_tag_mac) && ge->overload ) {
                me = NULL;
            }
    
        }
    }
    if( me != NULL ) {                  // usertag and coresponding macro ok
        processed = process_tag( ge, me );
    } else {
        *p ='\0';
        for( k = 0; k <= toklen; k++ ) {
            tok_upper[k] = toupper( *(tok_start + 1 + k) );
        }
        tok_upper[k] = '\0';

        if( ProcFlags.layout ) {        // different tags within :LAYOUT
            for( k = 0; k < LAY_TAGMAX; ++k ) {
                if( toklen == lay_tags[k].taglen ) {
                    if( !strcmp( lay_tags[k].tagname, tok_upper ) ) {
                        *p = csave;
                        lay_ind = -1;   // process tag not attribute

                        if( rs_loc == 0 ) {
                            // no restrictions: do them all
                            lay_tags[k].gmlproc( &lay_tags[k] );
                        } else if( (lay_tags[k].taglocs & rs_loc) != 0 ) {
                            // tag allowed in this restricted location
                            lay_tags[k].gmlproc( &lay_tags[k] );
                        } else if( (lay_tags[k].tagflags & tag_is_general) != 0 ) {
                            // tag allowed everywhere
                            lay_tags[k].gmlproc( &lay_tags[k] );
                        } else if( rs_loc == banner_tag ) {
                            xx_tag_err( err_tag_expected, "eBANNER" );
                        } else {    // rs_loc == banreg_tag    
                            xx_tag_err( err_tag_expected, "eBANREGION" );
                        }
                        processed = true;
                        lay_ind = k;    // now process attributes if any
                        if( *scan_start == '.' ) {
                            scan_start++;
                        }
                        break;
                    }
                }
            }
            if( !processed ) {          // check for gml only tag in :LAYOUT
                for( k = 0; k < GML_TAGMAX; ++k ) {
                    if( toklen == gml_tags[k].taglen ) {
                        if( !strcmp( gml_tags[k].tagname, tok_upper ) ) {
                            g_err( err_gml_in_lay, gml_tags[k].tagname );
                            err_count++;
                            file_mac_info();
                            processed = true;
                            scan_start = scan_stop + 1;
                            break;
                        }
                    }
                }
            }
        } else {                        // not within :LAYOUT
            for( k = 0; k < GML_TAGMAX; ++k ) {
                if( toklen == gml_tags[k].taglen ) {
                    if( !strcmp( gml_tags[k].tagname, tok_upper ) ) {
                        if( GlobalFlags.firstpass &&
                            !strcmp(tok_upper, "LAYOUT" ) &&
                            ProcFlags.fb_document_done  ) {

                            g_err( err_lay_too_late );
                            err_count++;
                            file_mac_info();
                            processed = true;
                            scan_start = scan_stop + 1;
                            break;
                        }
                        *p = csave;

                        if( script_style.style != SCT_none ) {
                            scr_style_end();        // cancel BD, BI, US
                        }

                        ProcFlags.need_tag = false;

                        /*******************************************************************/
                        /*  The Procflags must be cleared to prevent the error from being  */
                        /*  reported for every tag until the proper end tag is found.      */
                        /*  If the number of errors reported is limited at some point,     */
                        /*  then those lines can be removed.                               */
                        /*******************************************************************/

                        if( ProcFlags.need_ddhd ) {
                            if( (gml_tags[k].taglocs & def_tag) != 0 ) {
                                // tag is DD, DDHD or GD
                                gml_tags[k].gmlproc( &gml_tags[k] );
                            } else {
                                xx_tag_err( err_tag_expected, "DDHD");
                            }
                            ProcFlags.need_ddhd = false;
                        } else if( ProcFlags.need_dd ) {
                            if( (gml_tags[k].taglocs & def_tag) != 0 ) {
                                // tag is DD, DDHD or GD
                                gml_tags[k].gmlproc( &gml_tags[k] );
                            } else {
                                xx_tag_err( err_tag_expected, "DD");
                            }
                            ProcFlags.need_dd = false;
                        } else if( ProcFlags.need_gd ) {
                            if( (gml_tags[k].taglocs & def_tag) != 0 ) {
                                // tag is DD, DDHD or GD
                                gml_tags[k].gmlproc( &gml_tags[k] );
                            } else {
                                xx_tag_err( err_tag_expected, "GD");
                            }
                            ProcFlags.need_gd = false;
                        } else if( ProcFlags.need_li_lp ) {
                            if( (gml_tags[k].taglocs & li_lp_tag) != 0 ) {
                                // tag is LP or LI
                                gml_tags[k].gmlproc( &gml_tags[k] );
                            } else {
                                xx_nest_err( err_no_li_lp );
                            }
                        } else if( rs_loc == 0 ) {
                            // no restrictions: do them all
                            gml_tags[k].gmlproc( &gml_tags[k] );
                        } else if( (gml_tags[k].taglocs & rs_loc) != 0 ) {
                            // tag allowed in this restricted location
                            gml_tags[k].gmlproc( &gml_tags[k] );
                        } else if( (gml_tags[k].tagflags & tag_is_general) != 0 ) {
                            // tag allowed everywhere
                            gml_tags[k].gmlproc( &gml_tags[k] );
                        } else {
                            start_doc_sect();   // if not already done
                            g_err_tag_rsloc( rs_loc, tok_start );
                        }
                        processed = true;
                        if( *scan_start == '.' ) {
                            scan_start++;
                        }
                        break;
                    }
                }
            }
            if( !processed ) {         // check for layout tag in normal text
                for( k = 0; k < LAY_TAGMAX; ++k ) {
                    if( toklen == lay_tags[k].taglen ) {
                        if( !strcmp( lay_tags[k].tagname, tok_upper ) ) {
                            g_err( err_lay_in_gml, lay_tags[k].tagname );
                            err_count++;
                            file_mac_info();
                            processed = true;
                            scan_start = scan_stop + 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    if( *p == '\0' ) {
        *p = csave;
    }
    if( !processed ) {                  // treat as text
        scan_start = tok_start;
    }
}


/*
 * search for (control word) separator in string outside of quotes
 *       returns ptr to sep char or NULL if not found
 *      quotes are single or double quotes only
 */

static char *   search_separator( char * str, char sep )
{
    bool        instring = false;
    char        quote = '\0';

    while( *str != '\0' ) {
        if( instring ) {
            if( *str == quote ) {
                instring = false;
            }
        } else {
            if( (*str == '\"') || (*str == '\'') ) {
                instring = true;
                quote = *str;
            } else {
                if( *str == sep ) {
                    break;
                }
            }
        }
        str++;
    }
    if( *str == sep ) {
        return( str );
    } else {
        return( NULL );
    }
}


/*
 * Scan line with script control word
 *      uses scan_start ptr, but assumes this is in buff2
 */

static void     scan_script( void )
{
    inputcb     *   cb;
    mac_entry   *   me;
    char        *   p;
    char        *   pt;
    int             toklen;
    int             k;
    bool            cwfound;

    cb = input_cbs;
    p = scan_start + 1;
    scan_restart = scan_start;

    if( (*p == '*') || !strnicmp( p, "cm ", 3 ) ) {
        scan_start = scan_stop + 1;     // .cm  +++ ignore comment up to EOL
        return;                         // .*   +++ ignore comment up to EOL
    }

    if( *p == SCR_char && *(p+1) == SCR_char ) {
            pt = token_buf;
            *pt++ = SCR_char;               // special for ...label
            *pt++ = SCR_char;
            *pt   = '\0';
            me = NULL;
            scan_start = p + 2;
            toklen = 2;
    } else {
        if( *p == '\'' ) {                  // .'
            p++;
            if( !ProcFlags.CW_indented ) {  // only change if not indented
                ProcFlags.CW_sep_ignore = true;
            }
        } else {                            // no ': set per CW_sep_char
            if( CW_sep_char == '\0') {
                ProcFlags.CW_sep_ignore = true;// no separator char no split
            } else{
                ProcFlags.CW_sep_ignore = false;
            }
            if( *p == SCR_char ) {          // ..
                p++;
                ProcFlags.macro_ignore = true;
                me = NULL;
            } else {
                ProcFlags.macro_ignore = false;
            }
        }
        if( ProcFlags.literal ) {       // no macro or split line if literal
            ProcFlags.CW_sep_ignore = true;
            ProcFlags.macro_ignore = true;
        }
        if( !ProcFlags.CW_sep_ignore ) { // scan line for CW_sep_char
            char    *   pchar;

            pchar = search_separator( buff2, CW_sep_char );

            if( pchar != NULL ) {
                if( *(pchar + 1) != '\0' ) {    // only split if more follows
                    split_input( buff2, pchar + 1, false );// ignore CW_sep_char
                }
                *pchar= '\0';               // delete CW_sep_char
                buff2_lg = strlen( buff2 ); // new length of first part
            }
        }

        scan_start = p;

        pt = token_buf;
        while( *p && is_macro_char( *p ) ) {  // end of controlword
           *pt++ = tolower( *p++ );     // copy lowercase to TokenBuf
        }
        *pt = '\0';

        toklen = pt - token_buf;

        if( !ProcFlags.CW_sep_ignore &&
                (*p && (*p != ' ') || toklen == 0) ) {// no valid script controlword / macro
            scan_start = scan_restart;  // treat as text
            return;
        }

        if( toklen >= MAC_NAME_LENGTH ) {
            *(token_buf + MAC_NAME_LENGTH) = '\0';
        }
        if( !ProcFlags.macro_ignore ) {
            me = find_macro( macro_dict, token_buf );
        } else {
            me = NULL;
        }
    }

    if( me != NULL ) {                  // macro found
        if( GlobalFlags.firstpass && cb->fmflags & II_research ) {
            if( cb->fmflags & II_tag_mac ) {
                printf_research( "L%d    %c%s macro found in macro %s(%d)\n\n",
                                 inc_level, SCR_char, token_buf,
                                 cb->s.m->mac->name, cb->s.m->lineno );
            } else {
                printf_research( "L%d    %c%s macro found in file %s(%d)\n\n",
                                 inc_level, SCR_char, token_buf,
                                 cb->s.f->filename, cb->s.f->lineno );
            }
            add_SCR_tag_research( token_buf );
        }
        add_macro_cb_entry( me, NULL );
        inc_inc_level();
        add_macro_parms( p );
        scan_restart = scan_stop + 1;
    } else if( !ProcFlags.literal ) {    // try script controlword if not in LI
        cwfound = false;
        if( cb->fmflags & II_research && GlobalFlags.firstpass ) {
            if( cb->fmflags & II_tag_mac ) {
                printf_research( "L%d    %c%s CW found in macro %s(%d)\n\n",
                                 inc_level, SCR_char, token_buf,
                                 cb->s.m->mac->name, cb->s.m->lineno );
            } else {
                printf_research( "L%d    %c%s CW found in file %s(%d)\n\n",
                                 inc_level, SCR_char, token_buf,
                                 cb->s.f->filename, cb->s.f->lineno );
            }
            add_SCR_tag_research( token_buf );
        }

        if( toklen == SCR_KW_LENGTH ) {
            for( k = 0; k < SCR_TAGMAX; ++k ) {
                if( !strcmp( scr_tags[k].tagname, token_buf ) ) {
                    if( !ProcFlags.layout && !ProcFlags.fb_document_done
                            && (scr_tags[k].cwflags & cw_o_t) ) {

                        /********************************************************/
                        /* this is the first control word which produces output */
                        /* start the document, the layout is done               */
                        /* start_doc_sect() calls do_layout_end_processing()    */
                        /********************************************************/

                        start_doc_sect();
                    }
                    if( ProcFlags.literal  ) {  // .li active
                        if( !strcmp( token_buf, "li" ) ) {  // .li
                            scan_start = p; // found, process
                            scr_tags[k].tagproc();
                        }
                    } else {
                        scan_start = p; // script controlword found, process
                        if( scr_tags[k].cwflags & cw_break ) {
                            scr_process_break();// output incomplete line, if any
                        }
                        scr_tags[k].tagproc();
                    }
                    cwfound = true;
                    break;
                }
            }
        }
        if( !cwfound ) {
            cw_err();                   // unrecognized control word
        }
    }
    scan_start = scan_restart;
}


/***************************************************************************/
/*  logic for decision on skipping or processing line depending on         */
/*  the current state of the .if .th .el .do  controlwords encountered     */
/*                                                                         */
/*  The //comments refer to labels in the ASM code  see comment in wgml.c  */
/*  file cbt284.011                                                        */
/***************************************************************************/

#define DEBTESTPROC             // to reduce test output don't define this

condcode    test_process( ifcb * cb )
{
    condcode    cc;
    char        linestr[MAX_L_AS_STR];

#ifdef DEBTESTPROC
    int     start_level = cb->if_level;

    if( input_cbs->fmflags & II_research && GlobalFlags.firstpass
        && cb->if_level ) {
        show_ifcb( "Anf teif", cb );
    }
#endif

    cc = no;
//mainif
    if( cb->if_flags[cb->if_level].iflast   // 1. rec after .if
        && !cb->if_flags[cb->if_level].ifcwte) {// not .th or .el

        cb->if_flags[cb->if_level].iflast = false;  // reset first switch
        cb->if_flags[cb->if_level].ifthen = true;   // treat as then
    }

//mnif01
    if( cb->if_flags[cb->if_level].ifcwif ) {   // .if
//mnif03
        if( cb->if_flags[cb->if_level].ifthen
            || cb->if_flags[cb->if_level].ifelse ) {// object of .th or .el

            cc = pos;
        } else {

//mnif03a
            while( cb->if_level > 0 ) { // pop one level
                cb->if_level--;
                if( cb->if_flags[cb->if_level].ifdo ) {
                    break;
                }
            }
            cc = pos;                   // .do or all popped
        }

#ifdef DEBTESTPROC
        if( input_cbs->fmflags & II_research && GlobalFlags.firstpass
            && (start_level || cb->if_level) ) {
            char * txt = (cc == pos ? "EX1 pos" : "EX1 no" );

            show_ifcb( txt, cb );
        }
#endif
        return( cc );

    } else {                            // not .if

//mnif01 cont.
        if( cb->if_flags[cb->if_level].ifcwdo ) {   // if  .do
            cc = pos;
#ifdef DEBTESTPROC
        if( input_cbs->fmflags & II_research && GlobalFlags.firstpass
                && (start_level || cb->if_level) ) {
                char * txt = (cc == pos ? "Edo pos" : "Edo no" );

                show_ifcb( txt, cb );
            }
#endif
            return( cc );
        }

        if( cb->if_flags[cb->if_level].ifthen
            || cb->if_flags[cb->if_level].ifelse ) {// object of .th or .el
//mnif05
            if( cb->if_flags[cb->if_level].ifelse ) {   // object of .el
//mnif06
                if( cb->if_flags[cb->if_level].iftrue ) {// omit if true for .el
//mnif08
                    cc = neg;
                } else {
                    cc = pos;
                }
            } else {
                if( cb->if_flags[cb->if_level].iffalse ) {// omit false for .th
                    cc = neg;
                } else {
                    cc = pos;
                }
            }
        } else {
            if( cb->if_flags[cb->if_level].ifcwte ) {
                cc = pos;
            } else {
//mnif02
                while( cb->if_level > 0 ) {
                    cb->if_level--;
                    if( cb->if_flags[cb->if_level].ifdo ) {
//mnif05
                        if( cb->if_flags[cb->if_level].ifelse ) {// object of .el
//mnif06
                            if( cb->if_flags[cb->if_level].iftrue ) {
//mnif08
                                cc = neg;   // omit if true for .el
                            } else {
                                cc = pos;
                            }
                        } else {
                            if( cb->if_flags[cb->if_level].iffalse ) {
                                cc = neg;   // omit false for .th
                            } else {
                                cc = pos;
                            }
                        }
                        break;
                    }
                }
                if( cc == no ) {        // not set then process record
                    cc = pos;
                }
            }
        }
    }
    if( cc == no ) {                    // cc not set program logic error
        if( input_cbs->fmflags & II_tag_mac ) {
            utoa( input_cbs->s.m->lineno, linestr, 10 );
            g_err( err_if_intern, linestr, "macro", input_cbs->s.m->mac->name );
        } else {
            utoa( input_cbs->s.f->lineno, linestr, 10 );
            g_err( err_if_intern,
                     linestr, "file", input_cbs->s.f->filename );
        }
        if( inc_level > 1 ) {
            show_include_stack();
        }
        err_count++;
    }
#ifdef DEBTESTPROC
    if( input_cbs->fmflags & II_research && GlobalFlags.firstpass
        && (start_level || cb->if_level) ) {
        char * txt = (cc == pos ? "EX3 pos" : "EX3 no" );

        show_ifcb( txt, cb );
    }
#endif
    return( cc );

}
#undef DEBTESTPROC


/***************************************************************************/
/*  first pass at script control words .if .th .el .do                     */
/*                                                                         */
/*  This is needed for routine test_process above                          */
/*                                                                         */
/***************************************************************************/

void set_if_then_do( ifcb * cb )
{
    char        cw[3];
    char        c;

    if( *buff2 == SCR_char ) {          // only test script control words
        cw[0] = '\0';
        if( (*(buff2 + 1) == SCR_char)  ||  // ..CW
            (*(buff2 + 1) == '\'') ) {  // .'CW
            cw[0] = tolower( *(buff2 + 2) );// copy possible controlword
            cw[1] = tolower( *(buff2 + 3) );
            c = *(buff2 + 4);
        } else {                        // .CW
            cw[0] = tolower( *(buff2 + 1) );// copy possible controlword
            cw[1] = tolower( *(buff2 + 2) );
            c = *(buff2 + 3);
        }
        cw[2] = '\0';
        if( c == '\0' || c == ' ' ) {
            if( !strcmp( cw, "if" ) ) {
                cb->if_flags[cb->if_level].ifcwif = true;
            } else if( !strcmp( cw, "do" ) ) {
                cb->if_flags[cb->if_level].ifcwdo = true;
            } else if( !strcmp( cw, "th" ) || !strcmp( cw, "el" ) ) {
                cb->if_flags[cb->if_level].ifcwte = true;
            }
        }
    }
}


/*
 *  scan_line look whether input is script / gml control line or text
 *  special for attributes during :LAYOUT processing
 */

void    scan_line( void )
{
    condcode        cc;
    ifcb        *   cb;

    cb         = input_cbs->if_cb;
    scan_start = buff2;
    scan_stop  = buff2 + buff2_lg;

    if( !ProcFlags.literal ) {
        set_if_then_do( cb );
        cc = test_process( cb );
    } else {
        if( !ProcFlags.ct ) {           // special for .ct .li construct
            if( (t_line != NULL) && (t_line->first != NULL) ) {
                scr_process_break();
            }
        }
        cc = pos;
    }
    if( cc == pos ) {                   // process record
        if( ProcFlags.scr_cw ) {
            scan_script();              // script control line

        } else if( ProcFlags.gml_tag ) {
            scan_gml();                 // GML tags

        }

        /*******************************************************************/
        /*  here we arrive if no script keyword / GML tag recognized       */
        /*  or for unprocessed text in the input record                    */
        /*******************************************************************/

        if( (*scan_start != '\0') && (scan_start <= scan_stop) ) {
            if( input_cbs->fmflags & II_research && GlobalFlags.firstpass ) {
                g_info_lm( inf_text_line, scan_start );
            }
            if( ProcFlags.layout ) {    // LAYOUT active: should not happen
                internal_err( __FILE__, __LINE__ );
            } else {
                // processs (remaining) text
                if( rs_loc > 0 ) {
                    start_doc_sect();   // if not already done
                    // catch blank lines: not an error
                    while( scan_start < scan_stop ) {
                        if( (*scan_start != ' ') && (*scan_start != '\0') ) {
                            break;
                        }
                        scan_start++;
                    }
                    if( scan_start < scan_stop ) {
                        g_err_tag_rsloc( rs_loc, scan_start );
                    } else {
                        blank_lines++;
                    }
                } else {
                    process_text( scan_start, g_curr_font );
                }
            }
        } else if( !ProcFlags.concat && (*buff2 == '\0') ) {    // blank line found with concatenation off
            blank_lines++;
        }

        /*******************************************************************/
        /* For .co off or :xmp and the last part of the line just processed*/
        /* ensure the line is output                                       */
        /*******************************************************************/

        if( !ProcFlags.layout && (input_cbs->fmflags & II_eol) ) {
            if( !ProcFlags.concat && (input_cbs->fmflags & II_file) ) {

                /*******************************************************************/
                /* This fixes a problem found when BX was implemented: when PA is  */
                /* used inside a box before a text line with CO OFF. But whether   */
                /* this is the best place or whether the restriction is needed     */
                /* remains to be determined                                        */
                /*******************************************************************/

                if( ProcFlags.in_bx_box && !ProcFlags.keep_left_margin) {
                    t_page.cur_width = g_indent;
                }
                scr_process_break();
            }
        }
    } else if( input_cbs->fmflags & II_research && GlobalFlags.firstpass ) {
        g_info_lm( inf_skip_line );     // show skipped line
    }
    if( ProcFlags.literal ) {
        if( li_cnt < LONG_MAX ) {   // we decrement, do not wait for .li OFF
            if( li_cnt-- <= 0 ) {
                ProcFlags.literal = false;
            }
        }
        if( input_cbs->fmflags & II_eol ) {
            scr_process_break();        // ensure the line is output
        }
    }
}


/***************************************************************************/
/*  search gml tag entry for given token                                   */
/*  This is for system (predefined) tags only                              */
/*  return ptr to entry if found, else NULL                                */
/***************************************************************************/

const gmltag * find_sys_tag( char * token, size_t toklen )
{
    int k;

    for( k = 0; k < GML_TAGMAX; ++k ) {
        if( toklen == gml_tags[k].taglen ) {
            if( !stricmp( gml_tags[k].tagname, token ) ) {
                return( &gml_tags[k] );
            }
        }
    }
    return( NULL );                     // not found
}


/***************************************************************************/
/*  search gml layout tag entry for given token                            */
/*  This is for layout tags only                                           */
/*  return ptr to entry if found, else NULL                                */
/***************************************************************************/

const gmltag * find_lay_tag( char * token, size_t toklen )
{
    int k;

    for( k = 0; k < LAY_TAGMAX; ++k ) {
        if( toklen == lay_tags[k].taglen ) {
            if( !stricmp( lay_tags[k].tagname, token ) ) {
                return( &lay_tags[k] );
            }
        }
    }
    return( NULL );                     // not found
}


/***************************************************************************/
/*  find gml tag entry by e_tag value and determine if is an ip_tag        */
/*  ip_tags are CIT, HPx, Q, SF                                            */
/*  return true if offset is for an ip_tag, false otherwise                */
/*  NOTE: for some reason, an offset specified as, say "t_CIT" is actually */
/*        the offset for the gmltag object for tag eCIT, hence the         */
/*        adjustment                                                       */
/***************************************************************************/

bool is_ip_tag( e_tags offset )
{
    if( (offset < t_NONE) || (offset >= t_MAX) ) {  // catch invalid offset values
        internal_err( __FILE__, __LINE__ );
    } else if( offset != t_NONE ) {                 // t_NONE is valid, but is not an ip_tag
        return( gml_tags[offset - 1].taglocs & ip_tag );
    }
    return( false );                                // not found
}

