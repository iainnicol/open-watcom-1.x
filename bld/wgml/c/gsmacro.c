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
* Description:  macro utility functions
*               add_macro_cb_entry  -- add macro as input source
*               add_macro_parms     -- add macro call parms to local dictionary
*               free_lines          -- free macro source lines
*               scr_dm              -- .dm control word processing
*               scr_me              -- .me control word processing
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"



/***************************************************************************/
/*  add info about macro   to LIFO input list                              */
/***************************************************************************/

void    add_macro_cb_entry( mac_entry *me )
{
    macrocb *   new;
    inputcb *   nip;

    new = mem_alloc( sizeof( macrocb ) );

    nip = mem_alloc( sizeof( inputcb ) );
    nip->hidden_head = NULL;
    nip->hidden_tail = NULL;
    nip->if_cb       = mem_alloc( sizeof( ifcb ) );
    memset( nip->if_cb, '\0', sizeof( ifcb ) );

    init_dict( &nip->local_dict );

    nip->fmflags      = II_macro;
    nip->s.m          = new;

    new->lineno       = 0;
    new->macline      = me->macline;
    new->mac          = me;
    new->flags        = FF_macro;

    nip->prev = input_cbs;
    input_cbs = nip;
    return;
}


/*
 * add macro parms from input line as local symbolic variables
 * for non quoted parms try to assign symbolic variables
 * i.e.  a b c *var="1.8" d "1 + 2"
 *    will give &* =a b c *var="1.8" d "1 + 2"
 *              &*0=5
 *              &*1=a
 *              &*2=b
 *              &*3=c
 *              &*4=d
 *              &*5=1 + 2
 *       and &*var = 1.8
 *
 *  the variable for &* is named _  This can change if this leads to
 *  conflicts  -> change define MAC_STAR_NAME in gtype.h
 *
 */

void    add_macro_parms( char * p )
{
    int             len;
    condcode        cc;

    while( *p && *p == ' ' ) {
        ++p;
    }
    len   = strlen( p );
    if( len > 0 ) {
        char    starbuf[ 12 ];
        int     star0;

                                        // the macro parameter line
                                        // the name _ has to change (perhaps)
        add_symvar( &input_cbs->local_dict, MAC_STAR_NAME, p, no_subscript,
                    local_var );

        star0 = 0;
        garginit();
        cc = getarg();
        while( cc > omit ) {            // as long as there are parms
            char        c;
            char    *   scan_save;

            if( cc == pos ) {           // argument not quoted
                           /* look if it is a symbolic variable definition */
                scan_save  = scan_start;
                c          = *scan_save; // prepare value end
                *scan_save = '\0';      // terminate string
                scan_start = tok_start; // rescan for variable
                ProcFlags.suppress_msg = true;  // no errmsg please
                ProcFlags.blanks_allowed = 0;   // no blanks please

                scr_se();               // try to set variable and value

                ProcFlags.suppress_msg = false; // reenable err msg
                ProcFlags.blanks_allowed = 1;   // blanks again
                *scan_save = c;        // restore original char at string end
                scan_start = scan_save; // restore scan address
                if( scan_err ) {        // not valid
                    cc = omit;
                    star0++;
                    sprintf( starbuf, "%d", star0 );
                    p = tok_start + arg_flen ;
                    c = *p;                 // prepare value end
                    *p = '\0';              // terminate string
                    add_symvar( &input_cbs->local_dict, starbuf, tok_start,
                                no_subscript, local_var );
                    *p = c;                // restore original char at string end
                }

            }
            if( cc == quotes ) {        // add argument as local symbolic var
                star0++;
                sprintf( starbuf, "%d", star0 );
                p = tok_start + arg_flen ;
                c = *p;                 // prepare value end
                *p = '\0';              // terminate string
                add_symvar( &input_cbs->local_dict, starbuf, tok_start,
                            no_subscript, local_var );
                *p = c;                // restore original char at string end
            }
            cc = getarg();              // look for next parm
        }
                                        // the positional parameter count
        add_symvar( &input_cbs->local_dict, "0", starbuf,
                    no_subscript, local_var );
    }

    if( GlobalFlags.research && GlobalFlags.firstpass ) {
        print_sym_dict( input_cbs->local_dict );
    }
}


/*
 * free storage for macro lines
 *              or split input lines
 */

void    free_lines( inp_line * line )
{
    inp_line    *wk;
    inp_line    *wk1;

    wk = line;
    while( wk != NULL ) {
         wk1 = wk->next;
         mem_free( wk );
         wk = wk1;
    }
    return;
}

/***************************************************************************/
/* DEFINE  MACRO defines  a  sequence of  input lines  to  be invoked  by  */
/* ".name" as  a user-defined control word  or as an Execute  Macro (.EM)  */
/* operand.                                                                */
/*                                                                         */
/*      旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴커       */
/*      |       |                                                  |       */
/*      |       |    name /line1/.../linen</>                      |       */
/*      |  .DM  |    name <BEGIN|END>                              |       */
/*      |       |    name DELETE                                   |       */
/*      |       |                                                  |       */
/*      읕컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴켸       */
/*                                                                         */
/* Such user macros may be used for common sequences of control words and  */
/* text.   Keyword and positional parameters (&*, &*0, &*1, etc.)  may be  */
/* checked and substituted when the macro is invoked.                      */
/*                                                                         */
/* name:  The user  macro is known by  "name",  a one to  eight character  */
/*    identifier.                                                          */
/* name /line 1/line 2/.../line n/:  The  "macro body" of "name" consists  */
/*    of the input lines that are  separated by a self-defining character  */
/*    shown in the command prototype as "/".                               */
/* name <BEGIN|END>:  Longer user macros  are defined with a "name BEGIN"  */
/*    at the start and "name END" to terminate.   The ".DM name END" must  */
/*    start in column one of the input line.                               */
/* name DELETE:  A user macro may  be deleted by specifying "name DELETE"  */
/*    as an operand; "name OFF" is an alternate way to delete a macro.     */
/*                                                                         */
/* This control word does not cause a break.                               */
/*                                                                         */
/* NOTES                                                                   */
/* (1) The invoking of  defined user macros by ".name"  can be suppressed  */
/*     with the ".MS"  (Macro Substitution)  control word.    Invoking by  */
/*     ".EM .name" cannot be suppressed.                                   */
/* (2) The ".DM name END" operands  are verified for a  macro "name" that  */
/*     matches the ".DM name BEGIN".   ".DM" starting  in column one with  */
/*     no operands will also successfully terminate a macro definition.    */
/* (3) The user-defined  macro may  be invoked  with a  variable list  of  */
/*     keyword and positional operands                                     */
/*       .name operand1 operand2                                           */
/*     that will assign to the local Set Symbols &*1, &*2, ..., the value  */
/*     of corresponding operands in the macro call.   Each operand may be  */
/*     a character string,  a delimited  character string,  or a numeric.  */
/*     Numeric operands  that do not consist  entirely of digits  will be  */
/*     treated as a character string.                                      */
/*       .name key1=value key2=value                                       */
/*     Operands  that consist  of  a valid  Set  Symbol name  immediately  */
/*     followed by an  equal sign will assign  the value on the  right of  */
/*     the equal  sign to  the specified Set  Symbol before  invoking the  */
/*     macro.   If the Set Symbol begins with an asterisk the symbol will  */
/*     be local to the invoked macro.                                      */
/***************************************************************************/

extern  void    scr_dm( void )
{
    char        *   nmstart;
    char        *   p;
    char        *   pn;
    char            save;
    int             len;
    int             macro_line_count;
    int             compbegin;
    int             compend;
    char            macname[ MAC_NAME_LENGTH + 1 ];
    inp_line    *   head;
    inp_line    *   last;
    inp_line    *   work;
    ulong           lineno_start;
    condcode        cc;
    inputcb     *   cb;

    cb = input_cbs;

    garginit();

    cc = getarg();

    if( cc == omit ) {
        err_count++;
        out_msg( "ERR_MACRO_NAME_MISSING line %d of file '%s'\n",
                 cb->s.f->lineno, cb->s.f->filename );
        return;
    }

    p = tok_start;

    pn      = macname;
    len     = 0;

    /*  truncate name if too long WITHOUT error msg
     *  this is wgml 4.0 behaviour
     *
     */
    while( *p && test_macro_char( *p ) ) {
        if( len < MAC_NAME_LENGTH ) {
            *pn++ = *p++;               // copy macroname
            *pn   = '\0';
        } else {
            break;
        }
        len++;
    }
    macname[ MAC_NAME_LENGTH ] = '\0';

    cc = getarg();
    if( cc == omit ) {                  // nothing found
        err_count++;
        // SC--048 A control word parameter is missing
        out_msg( "ERR_MACRO_DEFINITON '%s'"
                 " expecting BEGIN END /macro/lines/\n"
                 "\t\t\tLine %d of file '%s'\n",
                 macname, cb->s.f->lineno, cb->s.f->filename );
        return;
    }

    p = scan_start;
    head = NULL;
    last = NULL;
    save = *p;             // save char so we can make null terminated string
    *p   = '\0';
    macro_line_count = 0;

    compend   = !stricmp( tok_start, "end" );
    compbegin = !stricmp( tok_start, "begin" );
    if( !(compbegin | compend) ) { // only .dm macname /line1/line2/ possible
        char    sepchar;

        if( ProcFlags.in_macro_define ) {
            err_count++;
            out_msg( "ERR_NESTED_MACRO_DEFINE '%s' expecting END\n"
                     "\t\t\tline %d of file '%s'\n",
                     tok_start, cb->s.f->lineno, cb->s.f->filename );
            return;
        }
        ProcFlags.in_macro_define = 1;

        *p   = save;
        lineno_start = cb->s.f->lineno;


        p = tok_start;
        sepchar = *p++;
        nmstart = p;
        while( *p ) {
            while( *p && *p != sepchar ) {  // look for seperator
                ++p;
            }
            len = p - nmstart;
            *p = '\0';
            work = mem_alloc( sizeof( inp_line ) + len );
            work->next = NULL;
            strcpy_s( work->value, len + 1, nmstart );
            if( last != NULL ) {
                last->next = work;
            }
            last = work;
            if( head == NULL ) {
                head = work;
            }
            nmstart = ++p;
            macro_line_count++;
        }
        compend = 1;                    // so the end processing will happen
    }                                   // BEGIN or END not found

    if( compend && !(ProcFlags.in_macro_define) ) {
        err_count++;
        // SC--003: A macro is not being defined
        out_msg( "ERR_MACRO_DEFINE END without BEGIN '%s'\n"
                 "\t\t\tLine %d of file '%s'\n",
                 macname, cb->s.f->lineno, cb->s.f->filename );
        return;
    }
    if( compbegin && (ProcFlags.in_macro_define) ) {
        err_count++;
        // SC--002 The control word parameter '%s' is invalid
        out_msg( "ERR_NESTED_MACRO_DEFINE '%s' expecting END\n"
                 "\t\t\tline %d of file '%s'\n",
                 macname, cb->s.f->lineno, cb->s.f->filename );
    }
    *p   = save;
    if( compbegin ) {                   // start new macro define

        ProcFlags.in_macro_define = 1;
        lineno_start = cb->s.f->lineno;

        while( !(cb->s.f->flags & FF_eof) ) {  // process all macro lines

            get_line();

            if( cb->s.f->flags & (FF_eof | FF_err) ) {
                break;                  // out of read loop
            }
            p = buff2;
            if( *p == SCR_char ) {      // possible macro end
                if( tolower( *(p + 1) ) == 'd' &&
                    tolower( *(p + 2) ) == 'm' &&
                    (*(p + 3) == ' ' || *(p + 3) == '\0') ) {

                    garginit();

                    cc = getarg();
                    if( cc == omit ) {  // only .dm  means macro end
                        compend = 1;
                        break;          // out of read loop
                    }
                    p = scan_start;
                    save = *p;
                    *p = '\0';
                    if( strncmp( macname, tok_start, MAC_NAME_LENGTH ) ) {
                        // macroname from begin different from end
                        err_count++;
                        // SC--005 Macro '%s' is not being defined
                        out_msg( "ERR_MACRO_DEF Macro '%s' is not being defined\n"
                                 "\t\t\tLine %d of file '%s'\n",
                                 tok_start, cb->s.f->lineno, cb->s.f->filename );
                        *p = save;
                        free_lines( head );
                        return;
                    }
                    *p = save;
                    cc = getarg();
                    if( cc == omit ) {
                        err_count++;
                        // SC--048 A control word parameter is missing
                        out_msg( "ERR_PARM_MISSING "
                                 "A control word parameter is missing\n"
                                 "\t\t\tLine %d of file '%s'\n",
                                 cb->s.f->lineno, cb->s.f->filename );
                        free_lines( head );
                        return;
                    }
                    p = scan_start;
                    save = *p;
                    *p = '\0';
                    if( strcmp( tok_start, "end") ) {
                        err_count++;
                        // SC--002 The control word parameter '%s' is invalid
                        out_msg( "ERR_PARMINVALID "
                                 "The control word parameter '%s' is invalid\n"
                                 "\t\t\tLine %d of file '%s'\n",
                                 cb->s.f->lineno, cb->s.f->filename );
                        free_lines( head );
                        return;
                    }
                    compend = 1;
                    break;              // out of read loop
                }
            }
            work = mem_alloc( sizeof( inp_line ) + cb->s.f->usedlen );
            work->next = NULL;
            strcpy_s( work->value, cb->s.f->usedlen + 1, buff2 );
            if( last != NULL ) {
                last->next = work;
            }
            last = work;
            if( head == NULL ) {
                head = work;
            }
            macro_line_count++;
        }                               // end read loop
        if( cb->s.f->flags & (FF_eof | FF_err) ) {
            err_count++;
            // error SC--004 End of file reached
            // macro '%s' is still being defined
            out_msg( "ERR_MACRO_DEFINE End of file reached"
                     " line %d of file '%s'\n"
                     "\t\t\tmacro '%s' is still being defined\n",
                     cb->s.f->lineno, cb->s.f->filename, macname );
            free_lines( head );
            return;
        }
    }                                   // end compbegin

    if( compend ) {                     // macro END definition processing
        mac_entry   *   me;

        me = find_macro( macro_dict, macname );
        if( me != NULL ) {              // delete macro with same name
            free_macro_entry( &macro_dict, me );
        }

        ProcFlags.in_macro_define = 0;

        len = strlen( cb->s.f->filename );
        me  = mem_alloc( len + sizeof( mac_entry ) );
        me->next = NULL;
        me->label_cb = NULL;
        strcpy( me->name, macname );
        me->macline = head;
        me->lineno = lineno_start;
        strcpy( me->mac_file_name, cb->s.f->filename );

        add_macro_entry( &macro_dict, me );

        if( GlobalFlags.research && GlobalFlags.firstpass ) {
            out_msg( "INF_MACRO '%s' defined with %d lines\n", macname,
                     macro_line_count );
        }
    } else {
        err_count++;
        out_msg( "ERR_MACRO_DEFINE_logic error '%s'\n", macname );
        free_lines( head );
        show_include_stack();
        return;
    }
    return;
}


/***************************************************************************/
/* MACRO EXIT  causes immediate  termination of the  macro or  input file  */
/* currently being processed  and resumption of the  higher-level file or  */
/* macro (if any) or termination of processing (if none).                  */
/*                                                                         */
/*     +----------------------------------------------------------+        */
/*     |       |                                                  |        */
/*     |  .ME  |    <line>                                        |        */
/*     |       |                                                  |        */
/*     +----------------------------------------------------------+        */
/*                                                                         */
/* This control word does  not cause a break.   If an  operand "line" has  */
/* been specified,  it will be processed  as an input line immediately on  */
/* return to the higher-level file or macro.   If the .ME control word is  */
/* used in the highest-level file, SCRIPT advances to the top of the next  */
/* page  and  prints  any  stacked   output  before  termination  of  all  */
/* processing.                                                             */
/*                                                                         */
/* EXAMPLES                                                                */
/*  (1) .me .im nextfile                                                   */
/*      This will  terminate the file  or macro currently  being processed */
/*      and  cause the  higher-level  file or  macro  to imbed  "nextfile" */
/*      before it does anything else.                                      */
/*  (2) .me .me                                                            */
/*      This will  terminate the current  file or  macro and will  in turn */
/*      terminate the higher-level file or macro.                          */
/*                                                                         */
/*                                                                         */
/* ! the line operand is ignored for .me in the master document file       */
/*                                                                         */
/***************************************************************************/

void    scr_me( void )
{
    condcode        cc;

    if( input_cbs->prev != NULL ) {     // if not master document file

        garginit();

        cc = getarg();
        if( cc != omit ) {              // line operand present

            free_lines( input_cbs->hidden_head );   // clear stacked input
            split_input( buff2, tok_start );// stack line operand

            // now move stacked line to previous input stack

            input_cbs->hidden_head->next = input_cbs->prev->hidden_head;
            input_cbs->prev->hidden_head = input_cbs->hidden_head;

            input_cbs->hidden_head = NULL;  // and delete from current input
            input_cbs->hidden_tail = NULL;
        }
    }

    input_cbs->fmflags |= II_eof;       // set eof

    input_cbs->if_cb->if_level = 0;     // terminate
    ProcFlags.keep_ifstate = false;     // ... all .if controls
    return;
}

