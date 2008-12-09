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
* Description:  WGML top level driver module and file I/O.
*               not yet functional
*   some logic / ideas adopted from Watcom Script 3.2 IBM S/360 Assembler
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <io.h>
#include <fcntl.h>
#include <errno.h>

#include "wgml.h"
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
    g_banner();

    out_msg( CRLF "Usage: wgml [options] srcfile [options]" CRLF );
    out_msg( "Options:" CRLF );
    out_msg( "-q\t\tQuiet, don't show product info." CRLF );
    out_msg( "-r\t\tResearch, no formatting, only count GML/SCR keywords" CRLF );
    out_msg( "\t\tand follow .im, .ap, :INCLUDE tags." CRLF );
    out_msg( "\tother options to be done / documented." CRLF );
    my_exit( 4 );
}


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


#if 0
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
        if( (cb = ip->s.f) != NULL ) {  // if file (not macro)
            if( (cb->flags & FF_open) ) {   // and file is open
                rc = fgetpos( cb->fp, &cb->pos );
                if( rc != 0 ) {
                    out_msg( "ERR_FILE_IO %d %s\n", errno, cb->filename );
                    err_count++;
                    g_suicide();
                }
                rc = fclose( cb->fp );
                if( rc != 0 ) {
                    out_msg( "ERR_FILE_IO %d %s\n", errno, cb->filename );
                    err_count++;
                    g_suicide();
                }
                cb->flags &= ~FF_open;
                return( true );
            }
        }
        ip = ip->prev;                  // next higher input level
    }
    return( false );                    // nothing to close
}
#endif

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
                out_msg( "ERR_FILE_IO %d %s\n", errno, cb->filename );
                err_count++;
                g_suicide();
            }
            cb->flags |= FF_open;
        } else {
            out_msg( "ERR_FILE_IO %d %s\n", erc2, cb->filename );
            err_count++;
            g_suicide();
        }
    }
    return;
}

/***************************************************************************/
/*  Set the extension of the Master input file as default extension        */
/***************************************************************************/

void set_default_extension( const char * masterfname )
{
    char        buff[ FILENAME_MAX ];
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
    nip->prev   = NULL;
    nip->hidden_head = NULL;
    nip->hidden_tail = NULL;
    nip->fmflags = II_file;
    nip->s.f    = new;
    init_dict( &nip->local_dict );

    new->lineno  = 0;
    new->linemin = line_from;
    new->linemax = line_to;
    strcpy_s( new->filename, fnlen + 1, try_file_name );
    mem_free( try_file_name );

    if( try_fp ) {
        new->flags = FF_open;
        new->fp    = try_fp;
    } else {
        new->flags = FF_clear;
        new->fp    = NULL;
    }

    if( input_cbs != NULL ) {
        nip->prev = input_cbs;
    }
    input_cbs = nip;
    return;
}


/***************************************************************************/
/*  remove info about file or macro  from LIFO list                        */
/***************************************************************************/

static  void    del_input_cb_entry( void )
{
    inputcb     *   wk;

    wk = input_cbs;
    if( wk == NULL ) {
        return;
    }
    free_lines( wk->hidden_head );

/*
 *  The macrolines in s.m don't need to be freed, as these point to
 *  mac_entry, and freeing is done with macro_dict
 */
    if( wk->fmflags & II_macro ) {
        free_lines( wk->s.m->mparms.starx );// free macro call parms
        if( wk->s.m->mparms.star != NULL ) {
            mem_free( wk->s.m->mparms.star );   // free macro parameter
        }
        mem_free( wk->s.m );
    } else {
        if( wk->s.f->flags & FF_open ) {// close file if neccessary
            fclose( wk->s.f->fp );
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

    cb = input_cbs->s.m;

    if( cb->macline == NULL ) {         // no more macrolines
        input_cbs->fmflags |= II_eof;
        cb->flags          |= FF_eof;
        cb->flags          &= ~FF_startofline;
        *buff2              = '\0';
    } else {
        cb->lineno++;
        cb->flags          |= FF_startofline;
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
        if( input_cbs->fmflags == II_macro ) {
            get_macro_line();           // input from macro line
        } else {
            cb = input_cbs->s.f;        // input from file
            if( !(cb->flags & FF_open) ) {
                reopen_inc_fp( cb );
            }
            do {
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

                    if( cb->flags & FF_crlf ) { // try to delete CRLF at end
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
                        out_msg( "ERR_FILE_IO %d %s\n", errno, cb->filename );
                        err_count++;
                        g_suicide();
                    }
                }
            } while( cb->lineno < cb->linemin );
        }
    }

    buff2_lg = strnlen_s( buff2, buf_size );
    if( input_cbs->fmflags & II_file ) {
        input_cbs->s.f->usedlen = buff2_lg;
    }

    if( !(input_cbs->fmflags & II_eof) && GlobalFlags.research &&
        GlobalFlags.firstpass ) {
        printf( "%s\n", buff2 );
    }
    return( !(input_cbs->fmflags & II_eof) );
}


void    show_include_stack( void )
{
    inputcb *   ip;

    ip = input_cbs;
    while( ip != NULL ) {
        switch( ip->fmflags ) {
        case    II_file:
            out_msg( "\tIncluded from line %d of file '%s'\n",
                     ip->s.f->lineno,
                     ip->s.f->filename );
            break;
        case    II_macro :
            out_msg( "\tLine %d of macro '%s' defined at line %d of file '%s'\n",
                     ip->s.m->lineno,
                     ip->s.m->mac->name,
                     ip->s.m->mac->lineno,
                     ip->s.m->mac->mac_file_name);
            break;
        default:
            out_msg( "\tERR Included from unknown\n" );
            break;
        }
        ip = ip->prev;
    }
    return;
}

void    inc_inc_level( void )
{
    inc_level++;                        // start new level
    if( inc_level > max_inc_level ) {
        max_inc_level = inc_level;      // record highest level
    }
}

/***************************************************************************/
/*  process the input file                                                 */
/***************************************************************************/

static  void    proc_GML( char * filename )
{
    filecb  *   cb;
    char        attrwork[ 32 ];

    ProcFlags.newLevelFile = 1;
    strcpy_s( token_buf, buf_size, filename );

    for( ; ; ) {                        // as long as there is more input
        if( ProcFlags.newLevelFile ) {
            ProcFlags.newLevelFile = 0; // start a new include FILE level

            /***************************************************************/
            /*  split off attribute  (f:xxxx)                              */
            /***************************************************************/
            split_attr_file( token_buf, attrwork, sizeof( attrwork ) );

            if( attrwork[ 0 ] ) {
                out_msg( "WNG_FILEATTR_IGNORED (%s) %s\n", attrwork, token_buf );
                wng_count++;
            }
            if( search_file_in_dirs( token_buf, def_ext, alt_ext,
                                     DS_cur_inc_lib_path ) ) {

                if( inc_level >= MAX_INC_DEPTH ) {
                    out_msg( "ERR_MAX_INPUT_NESTING %s\n", token_buf );
                    err_count++;
                    show_include_stack();
                    continue;           // don't start new include level
                }
            } else {
                out_msg( "ERR_INPUT_FILE_NOT_FOUND %s\n\n\n", token_buf );
                err_count++;
                if( inc_level > 0 ) {
                    show_include_stack();
                    continue;           // don't start new include level
                } else {                // masterfile included from cmdline
                    out_msg( "\tIncluded from %s\n", "cmdline" );
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
                cb->fileattr[ 0 ] = '\0';
            }
            if( GlobalFlags.inclist ) {
                out_msg( "\nCurrent file is '%s'\n", cb->filename );
            }
        } // new include FILE processing

        if( inc_level == 0 ) {
            break;                 // we are done (master document not found)
        }

        /*******************************************************************/
        /*  process an input file / macro                                  */
        /*******************************************************************/

        while( !(input_cbs->fmflags & II_eof) ) {

            if( !get_line() ) {
                break;                  // eof
            }

            process_line();
            scan_line();

            if( ProcFlags.newLevelFile || ProcFlags.newLevelMacro ) {
                break;             // imbed and friends found start new level
            }
        }
        if( ProcFlags.newLevelFile || ProcFlags.newLevelMacro ) {
            continue;
        }

        del_input_cb_entry();           // one level finished
        inc_level--;
        if( inc_level == 0 ) {          // EOF master document file
            break;
        }
        if( input_cbs->fmflags & II_file ) {
            cb = input_cbs->s.f;
            if( GlobalFlags.inclist ) {
                out_msg( "Current file is '%s'(%d)\n", cb->filename, cb->lineno );
            }
        } else {
            if( GlobalFlags.inclist ) {
                out_msg( "Current macro is '%s'\n", input_cbs->s.m->mac->name );
            }
        }
    }
}

/***************************************************************************/
/*  printStats show statistics at program end                              */
/***************************************************************************/

static  void    print_stats( void )
{
    out_msg( "\nStatistics:\n" );
    out_msg( "Max inc level: %6ld\n", max_inc_level );
    out_msg( "  Error count: %6ld\n", err_count );
    out_msg( "Warning count: %6ld\n", wng_count );
    out_msg( "   Returncode: %6d\n",  err_count ? 8 : wng_count ? 4 : 0 );

}

/***************************************************************************/
/*  initPass                                                               */
/***************************************************************************/
static  void    init_pass( void )
{

    if( pass > 1 ) {
        GlobalFlags.firstpass = 0;
        free_dict( &global_dict );      // free dictionaries
        free_macro_dict( &macro_dict );
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

}

/***************************************************************************/
/*  main WGML                                                              */
/***************************************************************************/

int main( int argc, char * argv[] )
{
    char    *   cmdline;
    int         cmdlen;
    jmp_buf     env;

    environment = &env;
    if( setjmp( env ) ) {               // if fatal error has occurred
        my_exit( 16 );
    }

    g_trmem_init();                     // init memory tracker if necessary

    init_global_vars();

    token_buf = mem_alloc( buf_size );
    get_env_vars();

    cmdlen = _bgetcmd( NULL, 0 ) + 1;
    cmdline = mem_alloc( cmdlen );
    _bgetcmd( cmdline, cmdlen );

    out_msg( "cmdline=%s\n", cmdline );

    proc_options( cmdline );
    g_banner();

    if( master_fname != NULL ) {        // filename specified
        set_default_extension( master_fname );// make this extension first choice

        for( pass = 1; pass <= passes; pass++ ) {

            init_pass();
//            g_trmem_prt_list();    // all memory freed if no output from call

            out_msg( "\nStarting pass %d of %d ( %s mode ) \n", pass, passes,
                     GlobalFlags.research ? "research" : "normal" );

            proc_GML( master_fname );

//            g_trmem_prt_list();         // show allocated memory at pass end

            out_msg( "\n  End of pass %d of %d ( %s mode ) \n", pass, passes,
                     GlobalFlags.research ? "research" : "normal" );
        }
    } else {
        out_msg( "ERR_MISSING_MAINFILENAME\n");
        err_count++;
        usage();
    }
    if( GlobalFlags.research ) {
        print_GML_tags_research();
        free_GML_tags_research();

        print_SCR_tags_research();
        free_SCR_tags_research();

        print_macro_dict( macro_dict );

        if( global_dict != NULL ) {
            print_sym_dict( global_dict );
        }
    }

    print_stats();

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
    if( buff1 != NULL ) {
        mem_free( buff1 );
    }
    if( buff2 != NULL ) {
        mem_free( buff2 );
    }

    ff_teardown();                  // free memory allocated in findfunc

    g_trmem_prt_list();             // all memory freed if no output from call
    g_trmem_close();

    my_exit( err_count ? 8 : wng_count ? 4 : 0 );
    return( 0 );                    // never reached, but makes compiler happy
}

