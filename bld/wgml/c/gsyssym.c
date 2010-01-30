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
* Description:  Implements predefined system variables SYSxxx and others
*               most are readonly and some are calculated when accessed
*                     incomplete                               TBD
****************************************************************************/

#define __STDC_WANT_LIB_EXT1__  1       /* use safer C library             */

#include <stdarg.h>
#include <errno.h>

#include "wgml.h"
#include "gvars.h"

#define sys(x)  sys##x                  // construct symvar varname
#define sysf(x) sys##x##fun             // construct access function name
#define sys0(x) sys##x##0               // construct subscript 0 name
#define syss(x) sys##x##str             // construct name for string value

#define pica( var, next, flag )    pick( var, next, flag )
#define picc( var, next, flag )    pick( var, next, flag )
#define picl( var, next, flag )    pick( var, next, flag )
#define pics( var, next, flag )    pick( var, next, flag )

/***************************************************************************/
/*  declare dictionary entries for system variables                        */
/***************************************************************************/

#define pick( var, next, flag ) static symvar sys( var );
#include "gsyssym.h"
#undef pick

#define pick( var, next, flag ) static symsub sys0( var );
#include "gsyssym.h"
#undef pick
#undef pica
#undef picc
#undef picl
#undef pics

/***************************************************************************/
/*  declare the access functions for system variables                      */
/***************************************************************************/

#define pica( var, next, flag )
#define pics( var, next, flag )
#define picc( var, next, flag )   picl( var, next, flag )
#define pick( var, next, flag )   picl( var, next, flag )
#define picl( var, next, flag )   \
static void sysf( var )( symvar * entry );
#include "gsyssym.h"
#undef pick
#undef pica
#undef picc
#undef picl
#undef pics

/***************************************************************************/
/*  define char strings to hold the values of some system variables        */
/***************************************************************************/

#define pica( var, next, flag )
#define pick( var, next, flag )
#define picc( var, next, flag )         \
static char syss( var )[2];             // for single char values as string

#define picl( var, next, flag )         \
static char syss( var )[MAX_L_AS_STR];  // for long as string

#define pics( var, next, flag )         \
static char syss( var )[60];            // for special string $docnum
                                        // arbitrary length
#include "gsyssym.h"

#undef pick
#undef pica
#undef picc
#undef picl
#undef pics

/***************************************************************************/
/*  define the dictionary for the system variables                         */
/*  The dictionary is built at compile time                                */
/*  pica:       no access function, no separate string value               */
/*  picc:          access function,    separate string value 2 chars       */
/*  picl:          access function,    separate string value 12 chars      */
/*  pics:       no access function,    separate string value 60 chars      */
/*  pick:          access function, no separate string value               */
/*                                  or 2 predefined values  ON OFF         */
/***************************************************************************/

#define picc( var, next, flag )     picl( var, next, flag )
#define picl( var, next, flag )     \
static symvar sys( var ) = {        \
    &sys( next ), "$" #var, 0L, 0L, NULL, &sys0( var ), sysf( var ), flag };\
static symsub sys0( var ) = { NULL, &sys( var ), no_subscript, &syss( var ) };

#define pica( var, next, flag )     \
static symvar sys( var ) = {        \
    &sys( next ), "$" #var, 0L, 0L, NULL, &sys0( var ), NULL, flag };\
static symsub sys0( var ) = { NULL, &sys( var ), no_subscript, NULL };

#define pics( var, next, flag )     \
static symvar sys( var ) = {        \
    &sys( next ), "$" #var, 0L, 0L, NULL, &sys0( var ), NULL, flag };\
static symsub sys0( var ) = { NULL, &sys( var ), no_subscript, &syss( var ) };

#define pick( var, next, flag )     \
static symvar sys( var ) = {        \
    &sys( next ), "$" #var, 0L, 0L, NULL, &sys0( var ), sysf( var ), flag };\
static symsub sys0( var ) = { NULL, &sys( var ), no_subscript, NULL };

#include "gsyssym.h"
#undef pick
#undef pica
#undef picc
#undef picl
#undef pics


/***************************************************************************/
/*  The sequence of the following strings must match the enum ju_enum      */
/***************************************************************************/

static  char    str[][8] = { "OFF", "ON", "HALF", "LEFT", "RIGHT", "CENTER",
                            "INSIDE", "OUTSIDE" };

static  char    dateval[20];
static  char    dayofmval[3];
static  char    dayofwval[2];
static  char    dayofyval[4];
static  char    hourval[3];
static  char    minuteval[3];
static  char    monthval[3];
static  char    pdayofwval[10];
static  char    pmonthval[12];
static  char    pyearval[5];
static  char    timeval[9];

/***************************************************************************/
/*  convert integer to roman digits                                        */
/***************************************************************************/

char * int_to_roman( uint32_t n, char * r, size_t rsize )
{
    static const struct {
        uint32_t    val;
        uint32_t    val49;
        char        ch;
        char        ch49;
    } i_2_r[] =
                {
                    { 1000, 900, 'm', 'c' },
                    {  500, 400, 'd', 'c' },
                    {  100,  90, 'd', 'x' },
                    {   50,  40, 'l', 'x' },
                    {   10,   9, 'x', 'i' },
                    {    5,   4, 'v', 'i' },
                    {    1,   1, 'i', 'i' }
                };

    size_t digit;
    size_t pos;
    char    * p = r;

    *p = '\0';
    if( (n < 1) || (n > 3999) ) {       // invalid out of range
        return( NULL );
    }

    digit = 0;
    pos = 0;
    do {
        while( n >= i_2_r[digit].val ) {
            *p++ = i_2_r[digit].ch;
            if( ++pos >= rsize ) {
                return( NULL );         // result field overflow
            }
            n -= i_2_r[digit].val;
        }
        if( n >= i_2_r[digit].val49 ) {
            *p++ = i_2_r[digit].ch49;
            if( ++pos >= rsize ) {
                return( NULL );         // result field overflow
            }
            *p++ = i_2_r[digit].ch;
            if( ++pos >= rsize ) {
                return( NULL );         // result field overflow
            }
            n -= i_2_r[digit].val49;
        }
        digit++;
    } while( n > 0 );
    *p = '\0';
    return( r );
}

/***************************************************************************/
/*  error routine for referenced, but not yet implemented variables        */
/***************************************************************************/

static void var_wng( char * varname )
{
    if( !ProcFlags.no_var_impl_err ) {  // for full dict print no err msg
        wng_count++;
        g_warn( err_var_not_impl, varname );
        file_mac_info();
    }
    return;
}

/***************************************************************************/
/*  access routines for some system symbols  mostly still dummy   TBD      */
/*  only those with comments are 'real'                                    */
/***************************************************************************/

static void sysadfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysadevenfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysadoddfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysapagefun( symvar * e )   // absolute page
{
    utoa( apage, sysapagestr, 10 );
    return;
};

static void sysbefun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysbfontsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysbmfun( symvar * e )
{
    utoa( bm, sysbmstr, 10 );
    return;
};

static void sysbofun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysbxfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysbxcharfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysccfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syscccfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syscdfun( symvar * e )      // column count
{
    ultoa( g_cd, syscdstr, 10 );
    return;
};

static void syscharsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysclfun( symvar * e )      // column length
{
    ultoa( g_cl, sysclstr, 10 );
    return;
};

static void syscofun( symvar * e )      // .co status
{
    if( ProcFlags.concat ) {
        sysco0.value = str[ju_on];
    } else {
        sysco0.value = str[ju_off];
    }
    return;
};

static void syscontfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syscpfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syscpagesfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syscpcfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syscpifun( symvar * e )     // cpi chars per inch
{
    utoa( CPI, syscpistr, 10 );
    return;
};

static void sysdfontsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysdhsetfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysdpagefun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysduplexfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysenvfun( symvar * e )     // never seen another value TBD
{
    sysenv0.value = "BODY";
    return;
};

static void sysfbfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfbcfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfbffun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfilefun( symvar * e )    // name of current input file/macro
{
    if( input_cbs == NULL ) {
        sysfile0.value = NULL;
    } else {
        if( input_cbs->fmflags & II_file ) {
            sysfile0.value = input_cbs->s.f->filename;
        } else {
            sysfile0.value = input_cbs->s.m->mac->name;
        }
    }
    return;
};

static void sysfkfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfkcfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysflnestfun( symvar * e )  // include level file/macro
{
    utoa( inc_level, sysflneststr, 10 );
    return;
};

static void sysfmfun( symvar * e )
{
    utoa( fm, sysfmstr, 10 );
    return;
};

static void sysfnfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfnamfun( symvar * e )  // name of current input file not macro
{
    inputcb * wk;

    if( input_cbs == NULL ) {
        sysfnam0.value = NULL;
    } else {
        wk = input_cbs;
        while( (wk != NULL) && !(wk->fmflags & II_file) ) {
            wk = wk->prev;
        }
        if( wk == NULL ) {
            sysfnam0.value = NULL;
        } else {
            sysfnam0.value = wk->s.f->filename;
        }
    }
    return;
};

static void sysfncfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfnumfun( symvar * e )// lineno of current input file not macro
{
    inputcb * wk;
    ulong   l = 0;

    if( input_cbs != NULL ) {
        wk = input_cbs;
        while( (wk != NULL) && !(wk->fmflags & II_file) ) {
            wk = wk->prev;
        }
        if( wk != NULL ) {
            l = wk->s.f->lineno;
        }
    }
    ultoa( l, e->sub_0->value, 10 );
    return;
};

static void sysfontsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysfsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysgutterfun( symvar * e )  // gutter
{
    ultoa( g_gutter, sysgutterstr, 10 );
    return;
};

static void syshifun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syshmfun( symvar * e )
{
    utoa( hm, syshmstr, 10 );
    return;
};

static void syshnfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syshncfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syshsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syshyfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syshycfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syshyphfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysinfun( symvar * e )      // .in indent value
{
    ultoa( g_indent * CPI / g_resh, sysinstr, 10 ); // in chars
    return;
};

static void sysinrfun( symvar * e )     // .in indentr indent right value
{
    ltoa( g_ll + g_indentr * CPI / g_resh, sysinrstr, 10 );
    return;
};

static void sysirfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysixjfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysixreffun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysjufun( symvar * e )      // .ju status
{
    sysju0.value = str[ProcFlags.justify];
    return;
};

static void syslayoutfun( symvar * e ) // LAYOUT cmdline option or :LAYOUT tag seen
{
    if( ProcFlags.lay_specified ) {
        syslayout0.value = str[ju_on];
    } else {
        syslayout0.value = str[ju_off];
    }
    return;
};

static void syslcfun( symvar * e )      // remaining linecount on page
{
    utoa( lc, syslcstr, 10 );
    return;
};

static void syslifun( symvar * e )      // SCRIPT control word start char
{
    *syslistr = SCR_char;
    return;
};

static void syslinbfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syslinefun( symvar * e )    // current lineno on page
{
    utoa( line, syslinestr, 10 );
    return;
};

static void sysllfun( symvar * e )
{
    ultoa( g_ll, sysllstr, 10 );
    return;
};

static void syslnumfun( symvar * e )  // lineno of current input file / macro
{
    ulong   l;

    if( input_cbs == NULL ) {
        l = 0;
    } else {
        if( input_cbs->fmflags & II_file ) {
            l = input_cbs->s.f->lineno;
        } else {
            l = input_cbs->s.m->lineno;
        }
    }
    ultoa( l, e->sub_0->value, 10 );
    return;
};

static void syslsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syslstfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysmcfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysmcsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysnodeidfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysoffun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysofflinefun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysonlinefun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysoocfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysoutfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syspagefun( symvar * e )    // pageno in body
{
    utoa( page, syspagestr, 10 );
    return;
};

static void syspagedfun( symvar * e )   // page depth
{
    ultoa( g_page_depth, syspagedstr, 10 );
    return;
};

static void syspagelmfun( symvar * e )  // page left margin
{
    ultoa( lm, syspagelmstr, 10 );
    return;
};

static void syspagermfun( symvar * e )  // page right margin
{
    ultoa( rm, syspagermstr, 10 );
    return;
};

static void syspgnumafun( symvar * e )  // pagenumber
{
    ultoa( page, syspgnumastr, 10 );
    return;
};

static void syspgnumadfun( symvar * e ) // pagenumber.
{
    ultoa( page, syspgnumadstr, 10 );
    strcat( syspgnumadstr, "." );
    return;
};

static void syspgnumcfun( symvar * e )  // roman page no UPPER
{
    int_to_roman( page, syspgnumcstr, sizeof( syspgnumcstr ) );
    strupr( syspgnumcstr );
    return;
};

static void syspgnumcdfun( symvar * e ) // roman page no UPPER.
{
    int_to_roman( page, syspgnumcdstr, sizeof( syspgnumcdstr ) );
    strupr( syspgnumcdstr );
    strcat( syspgnumcdstr, "." );
    return;
};

static void syspgnumrfun( symvar * e ) // roman page no
{
    int_to_roman( page, syspgnumrstr, sizeof( syspgnumrstr ) );
    return;
};

static void syspgnumrdfun( symvar * e ) // roman page no.
{
    int_to_roman( page, syspgnumrdstr, sizeof( syspgnumrdstr ) );
    strcat( syspgnumrdstr, "." );
    return;
};

static void syspifun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syspixfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysplfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysplsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syspnfun( symvar * e )      // page no
{
    ultoa( page, syspnstr, 10 );
    return;
};

static void sysppagefun( symvar * e )   // page no
{
    ultoa( page, sysppagestr, 10 );
    return;
};

static void sysprsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysprtfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syspsfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syspwfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysquietfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysrbfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysrecnofun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysreshfun( symvar * e )    // horiz base units
{
    utoa( g_resh, sysreshstr, 10 );
    return;
};

static void sysresvfun( symvar * e )    // vert base units
{
    utoa( g_resv, sysresvstr, 10 );
    return;
};

static void sysretfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysrmnestfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysscfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysscreenfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysseqnofun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysskcondfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysslfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysspcondfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syssufun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syssysfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void systabfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void systbfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void systermtfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void systisetfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void systmfun( symvar * e )
{
    utoa( tm, systmstr, 10 );
    return;
};

static void sysuseridfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void syswdfun( symvar * e )
{
    var_wng( e->name );
    return;
};

static void sysxtextfun( symvar * e )
{
    var_wng( e->name );
    return;
};

/***************************************************************************/
/*        dummy routines to avoid another picx macro                       */
/*        they deactivate themself at the first call                       */
/***************************************************************************/


static void sysampfun( symvar * e )     // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};

static void sysbcfun( symvar * e )      // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};

static void sysbsfun( symvar * e )      // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};

static void syscwfun( symvar * e )      // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};

static void sysgmlfun( symvar * e )     // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};

static void syspassnofun( symvar * e )  // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};

static void syspassoffun( symvar * e )  // dummy routine not needed
{
    e->varfunc = NULL;
    return;
};


/***************************************************************************/
/*  init_date_time  init several date / time system variables              */
/***************************************************************************/

static  void    init_date_time( void )
{
    time_t  now;
    struct  tm      tmbuf;
    char    *   p;

    now = time( NULL );
    localtime_s( &now, &tmbuf );

    strftime( dateval, sizeof( dateval ), "%B %d, %Y", &tmbuf );

    p = strstr( dateval, " 0" );        // search for leading zero
    if( p != NULL ) {                   // 'September 02, 2009'
        p++;
        *p = ' ';
        while( *p ) {                   // becomes
            *p = *(p + 1);              // 'September 2, 2009'
            p++;
        }
    }
    sysdate0.value = dateval;
    add_symvar( &global_dict, "date", dateval, no_subscript, 0 );

    strftime( dayofmval, sizeof( dayofmval ), "%e", &tmbuf );
    sysdayofm0.value = dayofmval;

    strftime( dayofwval, sizeof( dayofwval ), "%w", &tmbuf );
    dayofwval[0] += 1;                  // make 0-6 sun-sat 1-7
    sysdayofw0.value = dayofwval;

    strftime( dayofyval, sizeof( dayofyval ), "%j", &tmbuf );
    sysdayofy0.value = dayofyval;

    strftime( hourval, sizeof( hourval ), "%H", &tmbuf );
    syshour0.value = hourval;

    strftime( minuteval, sizeof( minuteval ), "%M", &tmbuf );
    sysminute0.value = minuteval;

    strftime( monthval, sizeof( monthval ), "%m", &tmbuf );
    sysmonth0.value = monthval;

    strftime( pdayofwval, sizeof( pdayofwval ), "%A", &tmbuf );
    syspdayofw0.value = pdayofwval;

    strftime( pmonthval, sizeof( pmonthval ), "%B", &tmbuf );
    syspmonth0.value = pmonthval;

    strftime( pyearval, sizeof( pyearval ), "%Y", &tmbuf );
    syspyear0.value = pyearval;
    sysyear0.value = &pyearval[2];      // year without century

    strftime( timeval, sizeof( timeval ), "%T", &tmbuf );
    systime0.value = timeval;
    syssecond0.value = &timeval[6];

    add_symvar( &global_dict, "time", timeval, no_subscript, 0 );

}

/***************************************************************************/
/*  init_predefined_symbols                                                */
/***************************************************************************/

static  void    init_predefined_symbols( void )
{
    char    wkstring[MAX_L_AS_STR];

    add_symvar( &global_dict, "amp", "&", no_subscript,
                predefined + late_subst );

    wkstring[1] = '\0';
    wkstring[0] = GML_CHAR_DEFAULT;
    add_symvar( &global_dict, "gml", wkstring, no_subscript,
                predefined + late_subst );

}

/***************************************************************************/
/*  init_sysparm     this is separate as only known after cmdline          */
/*                   processing                                            */
/***************************************************************************/

void    init_sysparm( char * cmdline, char * banner )
{
    sysparm0.value = cmdline;
    syspdev0.value = dev_name;
    sysversion0.value = banner;
}


/***************************************************************************/
/*  init_sys_dict  initialize dictionary and some entries which do not     */
/*                 change                                                  */
/***************************************************************************/

void    init_sys_dict( symvar * * dict )
{

    *dict           = &sysad;           // fill the dictionary ptr
    sysyear.next    = NULL;             // end of chain

    init_date_time();
    init_predefined_symbols();


    /***********************************************************************/
    /*  commented statements are perhaps  TBD                              */
    /***********************************************************************/

//  *sysadstr  =
//  *sysadevenstr  =
//  *sysadoddstr  =

    *sysampstr = '&';
    *(sysampstr + 1) = 0;
//  *sysauthor =
    *sysbcstr  = 'Y';
    *(sysbcstr + 1)  = 0;
//  *sysbestr  =
    *sysbsstr  = 0x16;
    *(sysbsstr + 1)  = 0;
    *sysbxstr  = 'N';
    *(sysbxstr + 1)  = 0;
//  *sysbxcharstr =
    *sysccstr  = 'N';
    *(sysccstr +1) = 0;
//  *syscccstr =
    syschars0.value = str[ju_off];
    sysco0.value    = str[ju_on];
    *syscpstr  = 'N';
    *(syscpstr + 1) = 0;
//  *syscpagesstr  =
//  *syscpcstr =
//  *syscpistr =
    *syscwstr  = CW_SEP_CHAR_DEFAULT;
    *(syscwstr + 1) = 0;
//  *sysdfontsstr =
//  *sysdhsetstr =
    *sysdocnumstr = 0;
//  *sysdpagestr =
    sysduplex0.value = str[ju_off];
    *sysfbstr = 'N';
    *(sysfbstr + 1) = 0;
//  *sysfbcstr =
//  *sysfbfstr =
    *sysfkstr = 'N';
    *(sysfkstr + 1) = 0;
//  *sysfkcstr =
    *sysfnstr = 'N';
    *(sysfnstr + 1) = 0;
//  *sysfncstr =
//  *sysfontsstr =
//  *sysfsstr =
    *sysgmlstr = GML_CHAR_DEFAULT;
    *(sysgmlstr + 1) = 0;
//  *sysgutterstr =
//  *syshistr =
    *syshnstr = 'N';
    *(syshnstr + 1) = 0;
//  *syshncstr =
//  *syshsstr =
    syshy0.value = str[ju_off];
//  *syshycstr =
    *syshyphstr = 'N';                // hyphenation OFF not implemented  TBD
    *(syshyphstr + 1) = 0;
//  *sysinstr =
//  *sysinrstr =
//  *sysirstr =
    *sysixjstr = '-';
    *(sysixjstr + 1) = 0;
    *sysixrefstr = ',';
    *(sysixrefstr + 1) = ' ';
    *(sysixrefstr + 2) = 0;
    sysju0.value = str[ju_on];
    syslayout0.value = str[ju_off];
    *syslistr = '.';
    *(syslistr + 1) = 0;
    *syslinbstr = ' ';
    *(syslinbstr + 1) = 0;
//  *syslsstr =
//  *syslststr =
    *sysmcstr = 'N';
    *(sysmcstr + 1) = 0;
    *sysmcsstr = '.';
    *(sysmcsstr + 1) = 0;
    sysmember0.value = NULL;            // member is never set
//  *sysnodeidstr =
//  *sysofstr =
    *sysofflinestr = 'N';
    *(sysofflinestr + 1) = 0;
    *sysonlinestr = 'Y';
    *(sysonlinestr + 1) = 0;
//  *sysoocstr =
//  *sysoutstr =
//  *syspagedstr =
//  *syspistr =
    *syspixstr = '*';
    *(syspixstr + 1) = 0;
//  *sysplstr =
    *sysplsstr = ',';
    *(sysplsstr + 1) = 0;
//  *sysppagestr =
    *sysprsstr = '-';
    *(sysprsstr + 1) = 0;
    sysprt0.value = str[ju_on];
    *syspsstr  = '%';
    *(syspsstr + 1) = 0;
//  *syspwstr =
    sysquiet0.value = str[ju_off];
    *sysrbstr    = ' ';
    *(sysrbstr + 1) = 0;
//  *sysrecnostr =
//  *sysretstr  =
//  *sysrmneststr  =
    *sysscstr   = 'N';
    *(sysscstr + 1) = 0;
    *sysscreenstr   = 'N';
    *(sysscreenstr + 1) = 0;
//  *sysseqnostr =
//  *sysskcondstr =
//  *sysslstr =
//  *sysspcondstr =
//  *sysstitlestr =
    syssu0.value = str[ju_on];
    syssys0.value = "DOS";
    *systabstr       = *systbstr       = ' ';
    *(systabstr + 1) = *(systbstr + 1) = 0;
//  *systermtstr =
//  *systisetstr =
//  *systitlestr =
//  *sysuseridstr =
//  *syswdstr =
//  *sysxtextstr =

    return;
}

