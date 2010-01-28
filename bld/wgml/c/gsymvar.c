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
* Description:  Implements symbolic variables (tables and access routines)
*
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */

#include <stdarg.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"



/***************************************************************************/
/*  init_dict      initialize dictionary pointer                           */
/***************************************************************************/

void    init_dict( symvar * * dict )
{

    *dict = NULL;
    return;
}

/***************************************************************************/
/*  free_dict   free all symbol dictionary entries                         */
/***************************************************************************/

void    free_dict( symvar * * dict )
{
    symvar  *   wk;
    symvar  *   wkn;
    symsub  *   ws;
    symsub  *   wsn;

    wk = *dict;
    while( wk != NULL ) {
        ws = wk->subscripts;
        while( ws != NULL ) {
            mem_free( ws->value );
            wsn = ws->next;
            mem_free( ws );
            ws = wsn;
        }
        mem_free( wk->sub_0->value );
        mem_free( wk->sub_0 );
        wkn = wk->next;
        mem_free( wk );
        wk = wkn;
    }
    *dict = NULL;
    return;
}


/***************************************************************************/
/*  search symbol and subscript entry in specified  dictionary             */
/*  fills symsub structure pointer if found                                */
/*                                                                         */
/***************************************************************************/

int find_symvar( symvar * * dict, char * name, sub_index sub, symsub * * symsubval )
{
    symvar  *   wk;
    symsub  *   ws;
    int         rc = 0;

    if( (*name == '$') && (dict != &sys_dict) ) {// for sysxxx try system dict first
        rc = find_symvar( &sys_dict, name, sub, symsubval );// recursion
        if( rc ) {
            return( rc );               // found predefined systemvariable
        }
    }
    wk = *dict;
    *symsubval = NULL;

    while( wk != NULL) {
        if( !strcmp( wk->name, name ) ) {
            if( wk->flags & deleted ) {
                break;                  // symbol name is deleted
            }
            rc = 1;                     // symbol name found
            break;
        }
        wk = wk->next;
    }
    if( rc ) {
        *symsubval = wk->sub_0;         // return at least sub 0
        if( wk->flags & subscripted ) {
            if( (sub == no_subscript) || (sub == 0) ) {
                rc = 2;                 // subscript found
            } else {
                rc = 1;                 // name is found
                ws = wk->subscripts;
                while( ws != NULL ) {
                    if( sub == ws->subscript ) {
                        *symsubval = ws;// subscript found
                        rc = 2;
                        break;
                    }
                    ws = ws->next;
                }
            }
        } else {
            if( (wk->flags & access_fun) && (wk->varfunc != NULL) ) {
                (wk->varfunc)( wk );    // get value via special function
            }
            rc = 2;                     // not subscripted -> all found
        }
    }
    if( *symsubval != NULL ) {
        if( (*symsubval)->value == NULL ) {
            rc = 0;            // temporarily set not found for uninitialized
        }
    }
    return( rc );
}

/***************************************************************************/
/*  search symbol and subscript entry in specified  dictionary             */
/*  fills symsub structure pointer if found                                */
/*  finds deleted variables too internal routine                           */
/***************************************************************************/

static  int find_symvar_del( symvar * * dict, char * name, sub_index sub,
                             symsub * * symsubval, symvar * * delentry )
{
    symvar  *   wk;
    symsub  *   ws;
    int         rc = 0;

    if( (*name == '$') && (dict != &sys_dict) ) {// for sysxxx try system dict first
        rc = find_symvar_del( &sys_dict, name, sub, symsubval, delentry );  // recursion
        if( rc ) {
            return( rc );               // found predefined systemvariable
        }
    }
    *symsubval = NULL;
    wk = *dict;
    while( wk != NULL) {
        if( !strcmp( wk->name, name ) ) {
            if( wk->flags & deleted ) {
                *delentry = wk;
                rc = -1;                // deleted symbol found
            } else {
                rc = 1;                 // symbol name found
            }
            break;
        }
        wk = wk->next;
    }
    if( rc > 0 ) {                      // non deleted symbol found

        *symsubval = wk->sub_0;         // return at least sub 0
        if( wk->flags & subscripted ) {
            if( (sub == no_subscript) || (sub == 0) ) {
                rc = 2;                 // subscript found
            } else {
                rc = 1;                 // name is found
                ws = wk->subscripts;
                while( ws != NULL ) {
                    if( sub == ws->subscript ) {
                        *symsubval = ws;// subscript found
                        rc = 2;
                        break;
                    }
                    ws = ws->next;
                }
            }
        } else {
            rc = 2;                     // not subscripted -> all found
        }
    }
    return( rc );
}

/***************************************************************************/
/*  check subscript for allowed range                                      */
/***************************************************************************/

static  bool    check_subscript( sub_index sub )
{

    if( sub != no_subscript ) {
        if( (sub < min_subscript) || (sub > max_subscript) ) {
            // SC--076 Subscript index must be between -1000000 and 1000000
            char    linestr[MAX_L_AS_STR];

            ltoa( sub, linestr, 10 );
            g_err( ERR_SUB_OUT_OF_RANGE, linestr );
            show_include_stack();
            err_count++;
            return( false );
        }
    }
    return( true );
}

/***************************************************************************/
/*  add_symvar_sub add value and subscript to base symbol entry            */
/*           the subscripts are added in ascending order                   */
/***************************************************************************/

static bool add_symvar_sub( symvar * var, char * val, sub_index sub )
{
    symsub  *   newsub;
    symsub  *   ws;
    symsub  *   wsv;
//  char        sub_cnt[12];

    if( var->flags & ro ) {             // value readonly
        return( true );                 // pretend success as wgml 4.0 does
    }
    if( sub != no_subscript ) {
        if( !check_subscript( sub ) ) {
            return( false );
        } else {
            var->subscript_used++;
                                             /* update special sub 0 entry */
#if 0
            sprintf( sub_cnt, "%ld", var->subscript_used );
            if( strlen( var->sub_0->value ) < strlen( sub_cnt ) ) {// need more room
                var->sub_0->value = mem_realloc( var->sub_0->value,
                                                 strlen( sub_cnt ) + 1 );
            }
            strcpy_s( var->sub_0->value, strlen( sub_cnt ) + 1, sub_cnt );
#else
            sprintf( var->sub_0->value, "%ld", var->subscript_used );  // TBD
#endif

            var->flags |= subscripted;
            if( (var->flags & auto_inc) && (sub == var->last_auto_inc + 1) ) {
                var->last_auto_inc++;
            }
        }

        newsub            = mem_alloc( sizeof( symsub ) );
        newsub->next      = NULL;
        newsub->base      = var;
        newsub->subscript = sub;
        newsub->value     = mem_alloc( strlen( val ) + 1 );
        strcpy_s( newsub->value, strlen( val ) + 1, val );

/*
 * insert subscript in ascending sort order
 */
        ws  = var->subscripts;
        if( ws == NULL || (sub < ws->subscript) ) {
            newsub->next    = var->subscripts;
            var->subscripts = newsub;
        } else {
            while( (ws != NULL) ) {
                if( sub > ws->subscript ) {
                    wsv = ws;
                    ws  = ws->next;
                } else {
                    break;
                }
            }
            newsub->next = ws;
            wsv->next    = newsub;
        }

    } else {                            // unsubscripted variable
        newsub = var->sub_0;
        if( strlen( newsub->value ) < strlen( val ) ) { // need more room
            newsub->value = mem_realloc( newsub->value, strlen( val ) + 1 );
        }
        strcpy_s( newsub->value, strlen( val ) + 1, val );
    }
    return( true );
}

/***************************************************************************/
/*  add_symsym  add symbol base entry and prepare subscript 0 entry        */
/***************************************************************************/

static void add_symsym( symvar * * dict, char * name, symbol_flags f, symvar * * n )
{
    symvar  *   new;
    symsub  *   newsub;
    int         k;

    new = mem_alloc( sizeof( symvar ) );

    for( k = 0; k < SYM_NAME_LENGTH; k++ ) {
       new->name[k] = name[k];
       if( !name[k] ) {
          break;
       }
    }
    for( ; k <= SYM_NAME_LENGTH; k++ ) {
       new->name[k] = '\0';
    }
    new->next = NULL;
    new->last_auto_inc  = 0;
    new->subscript_used = 0;
    new->subscripts = NULL;
    new->flags = f & ~deleted;

    newsub = mem_alloc( sizeof( symsub ) );
    new->sub_0 = newsub;
    newsub->next      = NULL;
    newsub->base      = new;
    newsub->subscript = 0;
    newsub->value     = mem_alloc( 12 + 1 );// for min subscript as string
                                        // -1000000
    newsub->value[0]  = '0';
    newsub->value[1]  = '\0';

    *n = new;
    new->next = *dict;
    *dict = new;
    return;
}


/***************************************************************************/
/*  add_symvar  add symbol with subscript and value                        */
/***************************************************************************/

int add_symvar( symvar * * dict, char * name, char * val, sub_index subscript, symbol_flags f )
{
    symvar  *   new = NULL;
    symsub  *   newsub = NULL;
    int     rc;
    bool    ok;

    if( !check_subscript( subscript ) ) {
        rc = 3;
    } else {
        rc = find_symvar_del( dict, name, subscript, &newsub, &new );
        switch ( rc ) {
        case -1 :                       // deleted symbol found
            new->flags &= ~deleted;     // reset deleted switch
            ok = add_symvar_sub( new, val, subscript );
            if( !ok ) {
                rc = 3;
            }
            break;
        case 0 :                        // nothing found
            add_symsym( dict, name, f, &new );
            ok = add_symvar_sub( new, val, subscript );
            if( !ok ) {
                rc = 3;
            }
            break;
        case 1 :                        // symbol found, but not subscript
            newsub->base->flags &= ~deleted;// reset deleted switch
            ok = add_symvar_sub( newsub->base, val, subscript );
            if( !ok ) {
                rc = 3;
            }
            break;
        case 2 :              // symbol + subscript found, or not subscripted
            newsub->base->flags &= ~deleted;// reset deleted switch
            if( (newsub->base->flags & ro) || !strcmp( newsub->value, val ) ) {
                ;             // do nothing var is readonly or value is unchanged
            } else {
                if( strlen( newsub->value ) < strlen( val ) ) { // need more room
                    newsub->value = mem_realloc( newsub->value, strlen( val ) + 1 );
                }
                strcpy_s( newsub->value, strlen( val ) + 1, val );
            }
            break;
        default:
            g_err( ERR_LOGIC_ERR, __FILE__ );
            show_include_stack();
            err_count++;
            g_suicide();
            break;
        }
    }
    return( rc );
}

/***************************************************************************/
/*  reset_auto_inc_dict  reset auto_inc value for passes 2 - n             */
/*  and set variable as deleted                                            */
/***************************************************************************/

void    reset_auto_inc_dict( symvar * dict )
{
    symvar  *   wk;
    symsub  *   ws;

    wk = dict;
    while( wk != NULL ) {


        if( wk->flags & auto_inc ) {

            wk->sub_0->value[0] = '0';
            wk->sub_0->value[1] = '\0';

            wk->flags |= deleted;
            wk->subscript_used = 0;
            while( (ws = wk->subscripts) != NULL ) {
                wk->subscripts = ws->next;
                mem_free( ws->value );
                mem_free( ws );
            }
        }
        wk->last_auto_inc = 0;
        wk = wk->next;
    }
    return;
}

/***************************************************************************/
/*  print_sym_dict  output all of the symbol dictionary                    */
/***************************************************************************/

void    print_sym_dict( symvar * dict )
{
    symvar          *   wk;
    symsub          *   ws;
    int                 symcnt;
    int                 symsubcnt;
    int                 len;
    bool                saveflag;
    char            *   lgs;
    static const char   fill[11] = "          ";

    symcnt      = 0;
    symsubcnt   = 0;
    wk          = dict;
    saveflag    = ProcFlags.no_var_impl_err;
    ProcFlags.no_var_impl_err = true;   // suppress err msg

    if( dict == sys_dict ) {
        lgs = "System";
    } else if( dict == global_dict ) {
        lgs = "Global";
    } else {
        lgs = "Local";
    }
    out_msg( "\n%s list of symbolic variables:\n", lgs );
    while( wk != NULL ) {
        len = strlen( wk->name );
        if( wk->subscript_used > 0 ) {
            out_msg( "Variable='%s'%s flags=%s%s%s%s%s%s%s%s "
                     "subscript_used=%d", wk->name, &fill[len],
                     wk->flags & deleted ? "deleted " : "",
                     wk->flags & local_var ? "local " : "",
                     wk->flags & auto_inc ? "auto_inc " : "",
                     wk->flags & predefined ? "predefined " : "",
                     wk->flags & late_subst ? "late_subst " : "",
                     wk->flags & ro ? "RO " : "",
                     wk->flags & no_free ? "no_free " : "",
                     wk->flags & access_fun ? "access_fun " : "",
                     wk->subscript_used );
        } else {
            out_msg( "Variable='%s'%s flags=%s%s%s%s%s%s%s%s ",
                     wk->name, &fill[len],
                     wk->flags & deleted ? "deleted " : "",
                     wk->flags & local_var ? "local " : "",
                     wk->flags & auto_inc ? "auto_inc " : "",
                     wk->flags & predefined ? "predefined " : "",
                     wk->flags & late_subst ? "late_subst " : "",
                     wk->flags & ro ? "RO " : "",
                     wk->flags & no_free ? "no_free " : "",
                     wk->flags & access_fun ? "access_fun " : "");
        }
        ws = wk->subscripts;
        if( wk->flags & subscripted ) {
            symsubcnt++;
            out_msg( "\n" );
        } else {
            if( (wk->flags & access_fun) && (wk->varfunc != NULL) ) {
                (wk->varfunc)( wk );    // get current value
            }
            if( wk->sub_0->value == NULL) { // oops not initialized
                out_msg( "\n" );
            } else {
                out_msg("value='%s'\n", wk->sub_0->value );
            }
            symcnt++;
        }
       if( wk->flags & subscripted ) {
            while( ws != NULL ) {
                out_msg( "   subscript= %8ld value='%s'\n",
                        ws->subscript, ws->value );
                ws = ws->next;
            }
        }
        wk = wk->next;
    }
    out_msg( "\nUnsubscripted symbols defined: %d\n", symcnt );
    out_msg( "Subscripted   symbols defined: %d\n", symsubcnt );
    ProcFlags.no_var_impl_err = saveflag;
    return;
}

