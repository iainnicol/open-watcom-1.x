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
* Description:  WGML top level driver module and file I/O.
*               not yet functional
*
*
*
*   some logic / ideas adopted from Watcom Script 3.2 IBM S/360 Assembler
*   as found on www.cbttape.org files 280 - 288
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1       /* use safer C library             */

#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "wgml.h"
#include "copfiles.h"
#include "findfile.h"
#include "gvars.h"
#include "banner.h"


#define mystr(x)            # x
#define xmystr(s)           mystr(s)

#define CRLF            "\n"



/***************************************************************************/
/*  Program end                                                            */
/***************************************************************************/

void my_exit( int rc )
{
    exit( rc );
}


/***************************************************************************/
/*  Output Banner if wanted and not yet done                               */
/***************************************************************************/

void g_banner( void )
{
    if( !(GlobalFlags.bannerprinted | GlobalFlags.quiet) ) {
        out_msg( banner1w( "WGML Script/GML", _WGML_VERSION_ ) CRLF );
        out_msg( banner2a() CRLF );
        out_msg( banner3 CRLF );
        out_msg( banner3a CRLF );
        out_msg( "Compiled with WATCOMC "xmystr(__WATCOMC__)
                 " "__DATE__" "__TIME__ CRLF);
#ifdef  TRMEM
        out_msg( "Compiled with TRMEM memory tracker (trmem)" CRLF );
#endif
        GlobalFlags.bannerprinted = 1;
    }
}

/***************************************************************************/
/*  Usage info TBD                                                         */
/***************************************************************************/

static void usage( void )
{
    int     k;
    int     kscreen;

    g_banner();

    kscreen = 0;
    for( k = inf_use_start; k <= inf_use_end; k++ ) {
        g_info( k );
        if( isatty( fileno( stdin ) ) ) {
            if( kscreen == 22 ) {
                kscreen = 0;
                g_info( inf_pause );
                getchar();
            } else {
                kscreen++;
            }
        }
    }
    my_exit( 4 );
}

#if 0                                   // not used for the moment
char *get_filename_full_path( char *buff, char const * name, size_t max )
{
    char    *   p;

    p = _fullpath( buff, name, max );
    if( p == NULL ) {
        p = (char *)name;
    }

#ifdef __UNIX__
    if( (p[0] == '/' && p[1] == '/') && (name[0] != '/' || name[1] != '/') ) {
        //
        // if the _fullpath result has a node number and
        // the user didn't specify one, strip the node number
        // off before returning
        //
        p += 2;
        while( *(p++) != '/' ) ;
    }
#endif
    return( p );
}
#endif


/***************************************************************************/
/*  Try to close an opened include file                                    */
/***************************************************************************/

static  bool    free_inc_fp( void )
{
    inputcb *   ip;
    filecb  *   cb;
    int         rc;

    ip = input_cbs;
    while( ip != NULL ) {              // as long as input stack is not empty
        if( ip->fmflags & II_file ) {   // if file (not macro)
            if( (cb = ip->s.f) != NULL ) {
                if( (cb->flags & FF_open) ) {   // and file is open
                    rc = fgetpos( cb->fp, &cb->pos );
                    if( rc != 0 ) {
                        strerror_s( buff2, buf_size, errno );
                        g_err( err_file_io, buff2, cb->filename );
                        err_count++;
                        g_suicide();
                    }
                    rc = fclose( cb->fp );
                    if( rc != 0 ) {
                        strerror_s( buff2, buf_size, errno );
                        g_err( err_file_io, buff2, cb->filename );
                        err_count++;
                        g_suicide();
                    }
                    cb->flags &= ~FF_open;
                    return( true );
                }
            }
        }
        ip = ip->prev;                  // next higher input level
    }
    return( false );                    // nothing to close
}

static void reopen_inc_fp( filecb *cb )
{
    int         rc;
    errno_t     erc;
    errno_t     erc2;

    if( ! cb->flags & FF_open ) {
        for( ;; ) {
            erc = fopen_s( &cb->fp, cb->filename, "rb" );
            if( erc == 0 ) break;
            erc2 = errno;
            if( errno != ENOMEM && errno != ENFILE && errno != EMFILE ) break;
            if( !free_inc_fp() ) break; // try closing an include file
        }
        if( erc == 0 ) {
            rc = fsetpos( cb->fp, &cb->pos );
            if( rc != 0 ) {
                strerror_s( buff2, buf_size, errno );
                g_err( err_file_io, buff2, cb->filename );
                err_count++;
                g_suicide();
            }
            cb->flags |= FF_open;
        } else {
            strerror_s( buff2, buf_size, erc2 );
            g_err( err_file_io, buff2, cb->filename );
            err_count++;
            g_suicide();
        }
    }
    return;
}

/***************************************************************************/
/*  Report resource exhaustion: may eventually try to correct the problem  */
/***************************************************************************/

bool    free_resources( errno_t in_errno )
{
    if( in_errno == ENOMEM) g_err( err_no_memory );
    else g_err( err_no_handles );
    err_count++;
    return( false );
}

/***************************************************************************/
/*  Set the extension of the Master input file as default extension        */
/***************************************************************************/

static  void    set_default_extension( const char * masterfname )
{
    char        buff[FILENAME_MAX];
    char    *   ext;

    _splitpath2( masterfname, buff, NULL, NULL, NULL, &ext );
    if( strlen( ext ) > 0) {
        if( strlen( ext ) > strlen( def_ext ) ) {
            mem_free( def_ext);
            def_ext = mem_alloc( 1+ strlen( ext ) );
        }
        strcpy_s( def_ext, 1 + strlen( ext ), ext );
    }
    return;
}


/***************************************************************************/
/*  add info about file  to LIFO list                                      */
/***************************************************************************/

static  void    add_file_cb_entry( void )
{
    filecb  *   new;
    inputcb *   nip;
    size_t      fnlen;

    fnlen = strlen( try_file_name );
    new = mem_alloc( sizeof( filecb ) + fnlen );// count for terminating \0
                                                //  is in filecb structure
    nip = mem_alloc( sizeof( inputcb ) );
    nip->hidden_head = NULL;
    nip->hidden_tail = NULL;
    nip->if_cb       = mem_alloc( sizeof( ifcb ) );
    memset( nip->if_cb, '\0', sizeof( ifcb ) );
    nip->pe_cb.line = NULL;
    nip->pe_cb.count = 0;
    nip->fmflags = II_file;
    nip->s.f     = new;
    init_dict( &nip->local_dict );

    new->lineno   = 0;
    new->linemin  = line_from;
    new->linemax  = line_to;
    new->label_cb = NULL;
    strcpy_s( new->filename, fnlen + 1, try_file_name );
    mem_free( try_file_name );
    try_file_name = NULL;

    if( try_fp ) {
        new->flags = FF_open;
        new->fp    = try_fp;
        try_fp     = NULL;
    } else {
        new->flags = FF_clear;
        new->fp    = NULL;
    }

    nip->prev = input_cbs;
    input_cbs = nip;
    return;
}


/***************************************************************************/
/*  remove info about file or macro  from LIFO list                        */
/***************************************************************************/

static  void    del_input_cb_entry( void )
{
    inputcb     *   wk;
    labelcb     *   lw;

    wk = input_cbs;
    if( wk == NULL ) {
        return;
    }
    free_lines( wk->hidden_head );

    free_dict( &wk->local_dict );
    if( wk->if_cb != NULL ) {
//      if( wk->if_cb->if_level > 0 ) {
//          char linestr[MAX_L_AS_STR];
//          utoa( wk->if_cb->if_level, linestr, 10 );
//          g_err( err_if_level, linestr );
//          show_include_stack();
//          err_count++;
//      }
        mem_free( wk->if_cb );
    }
    if( wk->pe_cb.line != NULL ) {
        mem_free( wk->pe_cb.line );
    }

    if( wk->fmflags & II_macro ) {
/*
 *  The macrolines in s.m don't need to be freed, as these point to
 *  mac_entry, and freeing is done with macro_dict
 */
        mem_free( wk->s.m );
    } else {
        if( wk->s.f->flags & FF_open ) {// close file if neccessary
            fclose( wk->s.f->fp );
        }
        lw = wk->s.f->label_cb;         // free labels
        if( GlobalFlags.research ) {
            print_labels( lw );         // print labels
        }
        while( lw != NULL ) {
           wk->s.f->label_cb = lw->prev;
           mem_free( lw );
           lw = wk->s.f->label_cb;
        }
        mem_free( wk->s.f );
    }
    input_cbs = wk->prev;
    mem_free( wk );
    return;
}


/***************************************************************************/
/*  get line from current macro                                            */
/***************************************************************************/
static  void    get_macro_line( void )
{
    macrocb *   cb;

    if( input_cbs->fmflags & II_file ) {
        g_err( err_logic_mac );
        show_include_stack();
        err_count++;
        g_suicide();
    }
    cb = input_cbs->s.m;

    if( cb->macline == NULL ) {         // no more macrolines
        input_cbs->fmflags |= II_eof;
        cb->flags          |= FF_eof;
        cb->flags          &= ~FF_startofline;
        *buff2              = '\0';
    } else {
        cb->lineno++;
        cb->flags          |= FF_startofline;
        cb->flags          &= ~FF_eof;
        input_cbs->fmflags &= ~II_eof;
        strcpy_s( buff2, buf_size, cb->macline->value );
        cb->macline         = cb->macline->next;
    }
}


/***************************************************************************/
/*  get line from current input ( file )                                   */
/*  skipping lines before the first one to process if neccessary           */
/***************************************************************************/
bool    get_line( void )
{
    filecb      *   cb;
    char        *   p;
    inp_line    *   pline;

    if( input_cbs->hidden_head != NULL ) {  // line was previously split,
        strcpy( buff2, input_cbs->hidden_head->value ); // take 2nd part
        pline = input_cbs->hidden_head;
        input_cbs->hidden_head = input_cbs->hidden_head->next;
        mem_free( pline );
        if( input_cbs->hidden_head == NULL ) {
            input_cbs->hidden_tail = NULL;
        }
    } else {
        if( input_cbs->pe_cb.count > 0 ) {  // .pe perform active
            strcpy( buff2, input_cbs->pe_cb.line );
            input_cbs->pe_cb.count--;
            if( input_cbs->pe_cb.count <= 0 ) {
                reset_pe_cb();
            }
        } else {
            if( input_cbs->fmflags & II_macro ) {
                get_macro_line();       // input from macro line
            } else {
                cb = input_cbs->s.f;    // input from file
                if( !(cb->flags & FF_open) ) {
                    g_info( err_inf_reopen );
                    show_include_stack();
                    reopen_inc_fp( cb );
                }
                do {
                    fgetpos( cb->fp, &cb->pos );// remember position for label
                    p = fgets( buff2, buf_size, cb->fp );
                    if( p != NULL ) {
                        if( cb->lineno >= cb->linemax ) {
                            input_cbs->fmflags |= II_eof;
                            cb->flags |= FF_eof;
                            cb->flags &= ~FF_startofline;
                            *buff2 = '\0';
                            break;
                        }
                        cb->lineno++;
                        cb->flags |= FF_startofline;

                        if( cb->flags & FF_crlf ) {// try to delete CRLF at end
                            p += strlen( p ) - 1;
                            if( *p == '\r' ) {
                                *p-- = '\0';
                                if( *p == '\n' ) {
                                    *p-- = '\0';
                                }
                            } else if( *p == '\n' ) {
                                *p-- = '\0';
                                if( *p == '\r' ) {
                                    *p-- = '\0';
                                }
                            }
                        }
                    } else {
                        if( feof( cb->fp ) ) {
                            input_cbs->fmflags |= II_eof;
                            cb->flags |= FF_eof;
                            cb->flags &= ~FF_startofline;
                            *buff2 = '\0';
                            break;
                        } else {
                            strerror_s( buff2, buf_size, errno );
                            g_err( err_file_io, buff2, cb->filename );

                            err_count++;
                            g_suicide();
                        }
                    }
                } while( cb->lineno < cb->linemin );
            }
        }
    }

    buff2_lg = strnlen_s( buff2, buf_size );
    *(buff2 + buff2_lg) = '\0';
    *(buff2 + buff2_lg + 1) = '\0';
    if( input_cbs->fmflags & II_file ) {
        input_cbs->s.f->usedlen = buff2_lg;
    }

    if( !(input_cbs->fmflags & II_eof) && GlobalFlags.research &&
        GlobalFlags.firstpass ) {
        printf( "%s\n", buff2 );
    }
    return( !(input_cbs->fmflags & II_eof) );
}


/***************************************************************************/
/*  output the filenames + lines which were included                       */
/***************************************************************************/

void    show_include_stack( void )
{
    inputcb *   ip;
    char        linestr[MAX_L_AS_STR];
    char        linemac[MAX_L_AS_STR];

    if( inc_level > 1 ) {
        ip = input_cbs;
        while( ip != NULL ) {
            switch( ip->fmflags & II_input ) {
            case    II_file:
                utoa( ip->s.f->lineno, linestr, 10 );
                g_info( err_inf_line_file, linestr, ip->s.f->filename );
                break;
            case    II_tag :
                g_info( err_inf_tag, ip->s.m->tag->name );
                // fallthrough
            case    II_macro :
                utoa( ip->s.m->lineno, linestr, 10 );
                utoa( ip->s.m->mac->lineno, linemac, 10 );
                g_info( err_inf_mac_def, linestr, ip->s.m->mac->name,
                        linemac, ip->s.m->mac->mac_file_name);
                break;
            default:
                g_info( err_inc_unknown );
                break;
            }
            ip = ip->prev;
        }
    }
    return;
}


/***************************************************************************/
/*  increment include level                                                */
/***************************************************************************/

void    inc_inc_level( void )
{
    inc_level++;                        // start new level
    if( inc_level > max_inc_level ) {
        max_inc_level = inc_level;      // record highest level
    }
}


/***************************************************************************/
/* remove leading  .  from input                                           */
/***************************************************************************/

static void remove_indentation( void )
{
    char    *   p;
    char    *   pb;
    int         offset;

    p = buff2;
    while( *p == SCR_char && *(p+1) == ' ' ) {
        while( *++p == ' ' ) /* empty */ ;  // skip blanks
    }
    if( p != buff2 ) {                  // found some blanks now copy buffer

        offset = p - buff2;
        pb = buff2;
        while( *p ) {
            *pb++ = *p++;
        }
        if( offset > 0 ) {
            memset( pb, '\0', offset ); // clear rest
        }
        buff2_lg = strnlen_s( buff2, buf_size );
//        if( GlobalFlags.research && GlobalFlags.firstpass ) {
//            g_info( INF_INDENT_REM, buff2 );
//        }
    }
}


/***************************************************************************/
/*  process the input file                                                 */
/***************************************************************************/

static  void    proc_GML( char * filename )
{
    ifcb    *   ic;
    filecb  *   cb;

    char        attrwork[32];

    ProcFlags.newLevelFile = 1;
    strcpy_s( token_buf, buf_size, filename );

    for( ; ; ) {                        // as long as there is input
        if( ProcFlags.newLevelFile ) {
            ProcFlags.newLevelFile = 0; // start a new include FILE level

            /***************************************************************/
            /*  split off attribute  (f:xxxx)                              */
            /***************************************************************/
            split_attr_file( token_buf, attrwork, sizeof( attrwork ) );

            if( attrwork[0] ) {
                g_warn( wng_fileattr_ignored, attrwork, token_buf );
                wng_count++;
            }
            if( search_file_in_dirs( token_buf, def_ext, alt_ext, ds_doc_spec ) ) {

                if( inc_level >= MAX_INC_DEPTH ) {
                    g_err( err_max_input_nesting, token_buf );
                    err_count++;
                    show_include_stack();
                    continue;           // don't start new include level
                }
            } else {
                g_err( err_input_file_not_found, token_buf );
                err_count++;
                if( inc_level > 0 ) {
                    show_include_stack();
                    continue;           // don't start new include level
                } else {                // masterfile included from cmdline
                    g_info( INF_INCLUDED, "cmdline" );
                    break;              // no input file leave loop
                }
            }
            inc_inc_level();            // record max include level
            add_file_cb_entry();
            cb = input_cbs->s.f;
            cb->flags |= FF_crlf;       // delete crlf at end
            if( attrwork[0] ) {
                strcpy_s( cb->fileattr, sizeof( cb->fileattr ), attrwork );
            } else {
                cb->fileattr[0] = '\0';
            }
            if( GlobalFlags.inclist ) {
                g_info( inf_curr_input, "file", cb->filename );
            }
        } // new include FILE processing

        if( inc_level == 0 ) {
            break;                 // we are done (master document not found)
        }
        //  test
    /*        fb_position( bin_device->x_start, bin_device->y_start+100 ); */


        /*******************************************************************/
        /*  process an input file / macro                                  */
        /*******************************************************************/

        while( !(input_cbs->fmflags & II_eof) ) {
            ic = input_cbs->if_cb;      // .if .th .el controlblock

            if( !ProcFlags.keep_ifstate ) {
                if( ic->if_level > 0 ) {// if .if active
                    if( ic->if_flags[ic->if_level].ifelse // after else
                        && !ic->if_flags[ic->if_level].ifdo ) {// no do group
                        ic->if_level--; // pop .if stack one level
                    }
                }
            }

            if( !get_line() ) {
                if( ProcFlags.goto_active ) {
                    char    linestr[MAX_L_AS_STR];

                    ProcFlags.goto_active = false;
                    err_count++;
                    if( input_cbs->fmflags & II_macro ) {
                        if( gotargetno > 0 ) {
                            utoa( gotargetno, linestr, 10 );
                            g_err( err_goto, linestr,
                                   input_cbs->s.m->mac->name );
                        } else {
                            g_err( err_goto, gotarget,
                                   input_cbs->s.m->mac->name );
                        }
                    } else {
                        g_err( err_goto, gotarget, input_cbs->s.f->filename );
                    }
                    show_include_stack();
                }
                break;                  // eof
            }
            if( !ProcFlags.keep_ifstate ) {
                if( !ic->if_flags[ic->if_level].ifdo ) {  // no do group
                    ic->if_flags[ic->if_level].ifthen = false;// not in then
                    ic->if_flags[ic->if_level].ifelse = false;// not in else
                }
            } else {
                ProcFlags.keep_ifstate = false;
            }

            remove_indentation();       // ".  .  .  .cw"  becomes ".cw"

            if( ProcFlags.goto_active ) {
                if( !gotarget_reached() ) {
                    continue;           // skip processing
                }
                ProcFlags.goto_active = false;
            }
            process_line();             // substitute variables + functions
            scan_line();

            if( ProcFlags.newLevelFile ) {
                break;            // imbed and friends found, start new level
            }
        }
        if( ProcFlags.newLevelFile ) {
            continue;
        }
#if 0
        if( ic->if_level > 0 ) {        // if .if active
            err_count++;
            if( input_cbs->fmflags & II_macro ) {
                out_msg( "ERR_IF_LEVEL nesting\n"
                         "\t\t\tLine %d of macro '%s'\n",
                         input_cbs->s.m->lineno, input_cbs->s.m->mac->name );
            } else {
                out_msg( "ERR_IF_LEVEL nesting\n"
                         "\t\t\tLine %d of file '%s'\n",
                         input_cbs->s.f->lineno, input_cbs->s.f->filename );
            }
            show_include_stack();
        }
#endif
        del_input_cb_entry();           // one level finished
        inc_level--;
        if( inc_level == 0 ) {          // EOF for master document file
            break;
        }
        if( input_cbs->fmflags & II_file ) {
            char    linestr[MAX_L_AS_STR];
            cb = input_cbs->s.f;
            if( GlobalFlags.inclist ) {
                utoa( cb->lineno, linestr, 10 );
                g_info( inf_curr_line, cb->filename, linestr );
            }
        } else {
            if( GlobalFlags.inclist ) {
                g_info( inf_curr_input, "macro", input_cbs->s.m->mac->name );
            }
        }
    }
}


/***************************************************************************/
/*  printStats show statistics at program end                              */
/***************************************************************************/

static  void    print_stats( clock_t duration_ticks )
{
    char        linestr[30];
    ldiv_t      hour_min;
    ldiv_t      sec_frac;

    g_info( inf_stat_1 );

    utoa( max_inc_level, linestr, 10 );
    g_info( inf_stat_2, linestr );

    utoa( err_count, linestr, 10 );
    g_info( inf_stat_3, linestr );

    utoa( wng_count, linestr, 10 );
    g_info( inf_stat_4, linestr );

    utoa( err_count ? 8 : wng_count ? 4 : 0, linestr, 10 );
    g_info( inf_stat_5, linestr );

    // convert duration from clock ticks to HH:MM:SS.hh
    hour_min = ldiv( duration_ticks / CLOCKS_PER_SEC / 60L, 60L );
    sec_frac  = ldiv( duration_ticks, CLOCKS_PER_SEC );
    sprintf_s( linestr, sizeof( linestr ), "%02lu:%02lu:%02lu.%02lu\0",
               hour_min.quot, hour_min.rem, sec_frac.quot % 60, sec_frac.rem / 6 );
    g_info( inf_stat_6, linestr );

}


/***************************************************************************/
/*  initPass                                                               */
/***************************************************************************/
static  void    init_pass( void )
{

    if( pass > 1 ) {
        GlobalFlags.firstpass = 0;

/*
 * design question: free dictionaries or not                            TBD
 *                  setsymbol defines from cmdline must not be deleted
 */

        reset_auto_inc_dict( global_dict );// let auto inc start with 1 again

//      free_dict( &global_dict );      // free dictionaries
//      free_macro_dict( &macro_dict );
        free_tag_dict( &tag_dict );

    } else {
        GlobalFlags.firstpass = 1;
    }
    if( pass < passes ) {
        GlobalFlags.lastpass = 0;
    } else {
        GlobalFlags.lastpass = 1;
    }

    line_from   = 1;                  // processing line range Masterdocument
    line_to     = ULONG_MAX - 1;

    init_tag_att();                     // reset last defined GML tag

}


/***************************************************************************/
/*  main WGML                                                              */
/***************************************************************************/

int main( int argc, char * argv[] )
{
    char    *   cmdline;
    int         cmdlen;
    jmp_buf     env;
    int         tok_count;
    clock_t     start_time;
    clock_t     end_time;

    environment = &env;
    if( setjmp( env ) ) {               // if fatal error has occurred
        my_exit( 16 );
    }

    start_time = clock();               // remember start time

    g_trmem_init();                     // init memory tracker if necessary

    init_global_vars();

    token_buf = mem_alloc( buf_size );

    // out_msg( "define enum %d %d\n", INF_CMDLINE, inf_cmdline );

    init_msgs();                        // init msg resources

    ff_setup();                         // init findfile

    cmdlen = _bgetcmd( NULL, 0 ) + 1;
    cmdline = mem_alloc( cmdlen );
    _bgetcmd( cmdline, cmdlen );

    g_info( INF_CMDLINE, cmdline );

    tok_count = proc_options( cmdline );
    init_sysparm( cmdline, banner1w( "WGML Script/GML", _WGML_VERSION_ )
                  );            // set sysparm and version
    /* don't mem_free cmdline it is used for sysparm variable */
    g_banner();
    if( tok_count < 4 ) {               // file ( device xyz   is minimum
        usage();                        // display usage and exit
    }
    cop_setup();                        // init copfiles



    if( master_fname != NULL ) {        // filename specified
        int     rc;
        symsub  * passnoval;
        symsub  * passofval;

        rc = find_symvar( &sys_dict, "$passof", no_subscript, &passofval );
        rc = find_symvar( &sys_dict, "$passno", no_subscript, &passnoval );
        utoa( passes, passofval->value, 10 );

        set_default_extension( master_fname );// make this extension first choice

        fb_start();                     // START :PAUSE & :INIT processing.

        for( pass = 1; pass <= passes; pass++ ) {

            init_pass();
            utoa( pass, passnoval->value, 10 );

            /* fb_document() needs to be done on the first pass only, but
             * also needs to be done immediately after the :ELAYOUT. tag.
             * This means that it may need to be relocated when layout
             * processing is implemented.
             */

            if( GlobalFlags.firstpass == 1) fb_document();// DOCUMENT :PAUSE & :INIT processing.

//            g_trmem_prt_list();  // all memory freed if no output from call
            g_info( INF_PASS_1, passnoval->value, passofval->value,
                    GlobalFlags.research ? "research" : "normal" );

            proc_GML( master_fname );

//            g_trmem_prt_list();       // show allocated memory at pass end

            if( GlobalFlags.research && (pass < passes) ) {
                print_sym_dict( global_dict );
            }
            g_info( INF_PASS_2, passnoval->value, passofval->value,
                    GlobalFlags.research ? "research" : "normal" );

            if( err_count > 0 ) {
                g_info( inf_error_stop );
                break;                  // errors found stop now
            }
        }

        fb_finish();                    // :FINISH block processing.

    } else {
        g_err( err_missing_mainfilename );
        err_count++;
        usage();
    }
    if( GlobalFlags.research ) {
        print_GML_tags_research();
        free_GML_tags_research();

        print_SCR_tags_research();
        free_SCR_tags_research();

        print_macro_dict( macro_dict, true );

        if( global_dict != NULL ) {
            print_sym_dict( global_dict );
        }
        if( tag_dict != NULL ) {
            print_tag_dict( tag_dict );
        }
        print_sym_dict( sys_dict );
    }

    end_time = clock();                 // get end time
    print_stats( end_time - start_time );

    close_all_pu_files();

    mem_free( cmdline );
    if( token_buf != NULL ) {
        mem_free( token_buf );
    }
    if( alt_ext != NULL ) {
        mem_free( alt_ext );
    }
    if( def_ext != NULL ) {
        mem_free( def_ext );
    }
    if( master_fname != NULL ) {
        mem_free( master_fname );
    }
    if( master_fname_attr != NULL ) {
        mem_free( master_fname_attr );
    }
    if( dev_name != NULL ) {
        mem_free( dev_name );
    }
    if( out_file != NULL ) {
        mem_free( out_file );
    }
    if( out_file_attr != NULL ) {
        mem_free( out_file_attr );
    }
    if( global_dict != NULL ) {
        free_dict( &global_dict );
    }
    if( macro_dict != NULL ) {
        free_macro_dict( &macro_dict );
    }
    if( tag_dict != NULL ) {
        free_tag_dict( &tag_dict );
    }
    if( buff2 != NULL ) {
        mem_free( buff2 );
    }

    ff_teardown();                      // free memory allocated in findfunc
    cop_teardown();                     // free memory allocated in copfiles

    fini_msgs();                        // end of msg resources
                /* no more msgs built from resources after this point */

    g_trmem_prt_list();            // all memory freed if no output from call
    g_trmem_close();


    my_exit( err_count ? 8 : wng_count ? 4 : 0 );
    return( 0 );                    // never reached, but makes compiler happy
}

