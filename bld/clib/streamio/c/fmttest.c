/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
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
* Description:  Non-exhaustive test of C library formatted I/O functions.
*
****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>

#ifdef __SW_BW
    #include <wdefwin.h>
#endif

/* Test macros */

#define VERIFY( exp )   if( !(exp) ) {                                      \
                           printf( "%s: ***FAILURE*** at line %d of %s.\n", \
                                   ProgramName, __LINE__,                   \
                                   strlwr( __FILE__ ) );                    \
                           NumErrors++;                                     \
                           exit( -1 );                                      \
                       }

char    ProgramName[FILENAME_MAX];      /* executable filename */
int     NumErrors = 0;                  /* number of errors */


/**********************/
/* Main test routines */
/**********************/

int Test_scan( void )
/*******************/
{
    char    buf[64], buf1[64];
    int     number, read;
    float   f, g;
    int     h = 23, m = 59, s = 55;
    char    c;

    strcpy( buf, "" );
    VERIFY( sscanf( buf, "%d", &number ) == EOF );

    VERIFY( sscanf( "123", "%d", &number ) == 1 );
    VERIFY( number == 123 );

    VERIFY( sscanf( "0x123", "%d", &number ) == 1 );
    VERIFY( number == 0 );

    VERIFY( sscanf( "0x123", "%i", &number ) == 1 );
    VERIFY( number == 0x123 );

    VERIFY( sscanf( "456", "%i", &number ) == 1 );
    VERIFY( number == 456 );

    VERIFY( sscanf( "0x409", "%x", &number ) == 1 );
    VERIFY( number == 0x409 );

    VERIFY( sscanf( "0x89a", "%x", &number ) == 1 );
    VERIFY( number == 0x89a );

    VERIFY( sscanf( "0Xefg", "%x", &number ) == 1 );
    VERIFY( number == 0xef );

    VERIFY( sscanf( "-82.25 31.6e-1", "%f%f", &f, &g ) == 2 );
    VERIFY( f == -82.25f );
    VERIFY( g == 3.16f );

    VERIFY( sscanf( " Ye Olde String\n", "%*c%[^\n]", buf ) == 1 );
    VERIFY( !strcmp( buf, "Ye Olde String" ) );

#if 0   // requires specific implementation-defined behaviour
    VERIFY( sscanf( "abcefgdh", "%*[a-cg-e]%c", &c ) == 1 );
    VERIFY( c == 'd' );

    VERIFY( sscanf( "abcefgdh", "%*[a-cd-dg-e]%c", &c ) == 1 );
    VERIFY( c == 'h' );
#endif

    sprintf( buf, "%d:%d:%d", h, m, s );
    VERIFY( sscanf( buf, "%d%n", &number, &read ) == 1 );
    VERIFY( number == h );
    VERIFY( read == 2 );
    VERIFY( sscanf( buf + 2, "%*c%n", &read ) == 0 );
    VERIFY( read == 1 );
    VERIFY( sscanf( buf + 2, ":%d%n", &number, &read ) == 1 );
    VERIFY( number == m );
    VERIFY( read == 3 );

    c = 33;
    VERIFY( sscanf( "@", "%c", &c ) == 1 );
    VERIFY( c == '@' );

    c = 33;
    VERIFY( sscanf( " !", "%c", &c ) == 1 );
    VERIFY( c == ' ' );

    c = 33;
    VERIFY( sscanf( "10:12", "%d:%d%c", &number, &read, &c ) == 2 );
    VERIFY( number == 10 );
    VERIFY( read == 12 );
    VERIFY( c == 33 );

    VERIFY( sscanf( "all   clear", "%s %n%s", buf, &number, buf1 ) == 2 );
    VERIFY( !strcmp( buf, "all" ) );
    VERIFY( !strcmp( buf1, "clear" ) );
    VERIFY( number == 6 );

    return( 1 );
}


int Test_scan_std_xmp( void )
/***************************/
{
    int     i;
    float   x;
    char    name[50];
    int     d1, d2, n1, n2;

    /* Examples from ISO C99 standard */

    VERIFY( sscanf( "25 54.32E-1 thompson", "%d%f%s", &i, &x, name ) == 3 );
    VERIFY( i == 25 );
    VERIFY( x == 5.432f );
    VERIFY( !strcmp( name, "thompson" ) );

    VERIFY( sscanf( "56789 0123 56a72", "%2d%f%*d %[0123456789]", &i, &x, name ) == 3 );
    VERIFY( i == 56 );
    VERIFY( x == 789.0f );
    VERIFY( !strcmp( name, "56" ) );

    d2 = 34;
    VERIFY( sscanf( "123", "%d%n%n%d", &d1, &n1, &n2, &d2 ) == 1 );
    VERIFY( d1 == 123 );
    VERIFY( d2 == 34 );
    VERIFY( n1 == 3 );
    VERIFY( n2 == 3 );

    return( 1 );
}


int Test_print_integer( void )
/****************************/
{
    char    buf[128];

    VERIFY( sprintf( buf, "%lld", (unsigned long long)0xffffffff * 0xffffffff ) == 11 );
    VERIFY( !strcmp( buf, "-8589934591" ) );

    VERIFY( sprintf( buf, "%+8lld", (long long)123 ) == 8 );
    VERIFY( !strcmp( buf, "    +123" ) );

    VERIFY( sprintf( buf, "%+.8lld", (long long)123 ) == 9 );
    VERIFY( !strcmp( buf, "+00000123" ) );

    VERIFY( sprintf( buf, "%+10.8lld", (long long)123 ) == 10 );
    VERIFY( !strcmp( buf, " +00000123" ) );

    VERIFY( sprintf( buf, "%_1lld", (long long)123 ) == 5 );
    VERIFY( !strcmp( buf, "_1lld" ) );

    VERIFY( sprintf( buf, "%-1.5lld", (long long)-123 ) == 6 );
    VERIFY( !strcmp( buf, "-00123" ) );

    VERIFY( sprintf( buf, "%-5lld", (long long)-123 ) == 5 );
    VERIFY( !strcmp( buf, "-123 " ) );

    VERIFY( sprintf( buf, "%-5lld", (long long)123 ) == 5 );
    VERIFY( !strcmp( buf, "123  " ) );

    VERIFY( sprintf( buf, "%5lld", (long long)123 ) == 5 );
    VERIFY( !strcmp( buf, "  123" ) );

    VERIFY( sprintf( buf, "%-.5lld", (long long)123 ) == 5 );
    VERIFY( !strcmp( buf, "00123" ) );

    VERIFY( sprintf( buf, "%-.5lld", (long long)-123 ) == 6 );
    VERIFY( !strcmp( buf, "-00123" ) );

    VERIFY( sprintf( buf, "%-8.5lld", (long long)123 ) == 8 );
    VERIFY( !strcmp( buf, "00123   " ) );

    VERIFY( sprintf( buf, "%-8.5lld", (long long)-123 ) == 8 );
    VERIFY( !strcmp( buf, "-00123  " ) );

    VERIFY( sprintf( buf, "%05lld", (long long)123 ) == 5 );
    VERIFY( !strcmp( buf, "00123" ) );

    VERIFY( sprintf( buf, "%05lld", (long long)-123 ) == 5 );
    VERIFY( !strcmp( buf, "-0123" ) );

    VERIFY( sprintf( buf, "% lld", (long long)123 ) == 4 );
    VERIFY( !strcmp( buf, " 123" ) );

    VERIFY( sprintf( buf, "% lld", (long long)-123 ) == 4 );
    VERIFY( !strcmp( buf, "-123" ) );

    VERIFY( sprintf( buf, "% 5lld", (long long)123 ) == 5 );
    VERIFY( !strcmp( buf, "  123" ) );

    VERIFY( sprintf( buf, "% 5lld", (long long)-123 ) == 5 );
    VERIFY( !strcmp( buf, " -123" ) );

    VERIFY( sprintf( buf, "% .5lld", (long long)123 ) == 6 );
    VERIFY( !strcmp( buf, " 00123" ) );

    VERIFY( sprintf( buf, "% .5lld", (long long)-123 ) == 6 );
    VERIFY( !strcmp( buf, "-00123" ) );

    VERIFY( sprintf( buf, "% 8.5lld", (long long)123 ) == 8 );
    VERIFY( !strcmp( buf, "   00123" ) );

    VERIFY( sprintf( buf, "% 8.5lld", (long long)-123 ) == 8 );
    VERIFY( !strcmp( buf, "  -00123" ) );

    VERIFY( sprintf( buf, "%.0lld", (long long)0 ) == 0 );
    VERIFY( !strcmp( buf, "" ) );

    VERIFY( sprintf( buf, "%.lld", (long long)0 ) == 0 );
    VERIFY( !strcmp( buf, "" ) );

    VERIFY( sprintf( buf, "%#+22.18llx", (long long)-123 ) == 22 );
    VERIFY( !strcmp( buf, "  0x00ffffffffffffff85" ) );

    VERIFY( sprintf( buf, "%#+25.20llX", (long long)-123 ) == 25 );
    VERIFY( !strcmp( buf, "   0X0000FFFFFFFFFFFFFF85" ) );

    VERIFY( sprintf( buf, "%.25llo", (long long)-123 ) == 25 );
    VERIFY( !strcmp( buf, "0001777777777777777777605" ) );

    VERIFY( sprintf( buf, "%#+25.20llo", (long long)-123 ) == 25 );
    VERIFY( !strcmp( buf, "  01777777777777777777605" ) );

    VERIFY( sprintf( buf, "%#+20.25llo", (long long)-123 ) == 25 );
    VERIFY( !strcmp( buf, "0001777777777777777777605" ) );

    VERIFY( sprintf( buf, "%#+25.23llu", (long long)-1 ) == 25 );
    VERIFY( !strcmp( buf, "  00018446744073709551615" ) );

    VERIFY( sprintf( buf, "%+#25.23lld", (long long)-1 ) == 25 );
    VERIFY( !strcmp( buf, " -00000000000000000000001" ) );

    VERIFY( sprintf( buf, "%#-8.5llo", (long long)123 ) == 8 );
    VERIFY( !strcmp( buf, "00173   " ) );

    VERIFY( sprintf( buf, "%#-+ 8.5llo", (long long)123 ) == 8 );
    VERIFY( !strcmp( buf, "00173   " ) );

    VERIFY( sprintf( buf, "%#-+ 08.5lld", (long long)123 ) == 8 );
    VERIFY( !strcmp( buf, "+00123  " ) );

    VERIFY( sprintf( buf, "%I", 1 ) == 1 );
    VERIFY( !strcmp( buf, "I" ) );

    VERIFY( sprintf( buf, "%I63", 1 ) == 3 );
    VERIFY( !strcmp( buf, "I63" ) );

    VERIFY( sprintf( buf, "% d", 7 ) == 2 );
    VERIFY( !strcmp( buf, " 7" ) );

    VERIFY( sprintf( buf, "%+ d", 3 ) == 2 );
    VERIFY( !strcmp( buf, "+3" ) );

    VERIFY( sprintf( buf, "%3d", 1234 ) == 4 );
    VERIFY( !strcmp( buf, "1234" ) );

    VERIFY( sprintf( buf, "%-1d", 9 ) == 1 );
    VERIFY( !strcmp( buf, "9" ) );

    VERIFY( sprintf( buf, "%-i", -3 ) == 2 );
    VERIFY( !strcmp( buf, "-3" ) );

    VERIFY( sprintf( buf, "%-i", 3 ) == 1 );
    VERIFY( !strcmp( buf, "3" ) );

    VERIFY( sprintf( buf, "%+i", 3 ) == 2 );
    VERIFY( !strcmp( buf, "+3" ) );

    VERIFY( sprintf( buf, "%o", 8 ) == 2 );
    VERIFY( !strcmp( buf, "10" ) );

    return( 1 );
}


int Test_print_float( void )
/**************************/
{
    char    buf[128];

    VERIFY( sprintf( buf, "%+#22.14e", 123456789.0 ) == 22 );
    VERIFY( !strcmp( buf, " +1.23456789000000e+08" ) );

    VERIFY( sprintf( buf, "%2.4f", 4.5 ) == 6 );
    VERIFY( !strcmp( buf, "4.5000" ) );

    VERIFY( sprintf( buf, "%0f", 0.8 ) == 8 );
    VERIFY( !strcmp( buf, "0.800000" ) );

    VERIFY( sprintf( buf, "%.0f", 0.8 ) == 1 );
    VERIFY( !strcmp( buf, "1" ) );

    VERIFY( sprintf( buf, "%2.4e", 4.5 ) == 10 );
    VERIFY( !strcmp( buf, "4.5000e+00" ) );

    VERIFY( sprintf( buf, "%2.4g", 4.5 ) == 3 );
    VERIFY( !strcmp( buf, "4.5" ) );

#if defined( _NAN ) && defined( _INF )
    /* Test NaN/inf formatting */
    VERIFY( sprintf( buf, "%e", _INF ) == 3 );
    VERIFY( !strcmp( buf, "inf" ) );

    VERIFY( sprintf( buf, "%f", _INF ) == 3 );
    VERIFY( !strcmp( buf, "inf" ) );

    VERIFY( sprintf( buf, "%g", _INF ) == 3 );
    VERIFY( !strcmp( buf, "inf" ) );

    VERIFY( sprintf( buf, "%E", _INF ) == 3 );
    VERIFY( !strcmp( buf, "INF" ) );

    VERIFY( sprintf( buf, "%G", _INF ) == 3 );
    VERIFY( !strcmp( buf, "INF" ) );

    VERIFY( sprintf( buf, "%e", _NAN ) == 3 );
    VERIFY( !strcmp( buf, "nan" ) );

    VERIFY( sprintf( buf, "%f", _NAN ) == 3 );
    VERIFY( !strcmp( buf, "nan" ) );

    VERIFY( sprintf( buf, "%g", _NAN ) == 3 );
    VERIFY( !strcmp( buf, "nan" ) );

    VERIFY( sprintf( buf, "%E", _NAN ) == 3 );
    VERIFY( !strcmp( buf, "NAN" ) );

    VERIFY( sprintf( buf, "%G", _NAN ) == 3 );
    VERIFY( !strcmp( buf, "NAN" ) );

    /* Currently %F is a far pointer modified in some libs, to
     * be changed later. Most libs are ISO C compliant in this regard.
     */
#if !defined( __MSDOS__ ) && !defined( _M_IX86 )
    VERIFY( sprintf( buf, "%F", _INF ) == 3 );
    VERIFY( !strcmp( buf, "INF" ) );

    VERIFY( sprintf( buf, "%F", _NAN ) == 3 );
    VERIFY( !strcmp( buf, "NAN" ) );
#endif
#endif

    return( 0 );
}


int Test_print_character( void )
/******************************/
{
    char    buf[128];
    int     read;

    VERIFY( sprintf( buf, "%4c", '?' ) == 4 );
    VERIFY( !strcmp( buf, "   ?" ) );

    VERIFY( sprintf( buf, "%-4c", 'd' ) == 4 );
    VERIFY( !strcmp( buf, "d   " ) );

    VERIFY( sprintf( buf, "%4s", "tst" ) == 4 );
    VERIFY( !strcmp( buf, " tst" ) );

    VERIFY( sprintf( buf, "%.1s", "tst" ) == 1 );
    VERIFY( !strcmp( buf, "t" ) );

    VERIFY( sprintf( buf, "%.*s", 2, "tst" ) == 2 );
    VERIFY( !strcmp( buf, "ts" ) );

    VERIFY( sprintf( buf, "tst" ) == 3 );
    VERIFY( !strcmp( buf, "tst" ) );

    VERIFY( sprintf( buf, "%S", L"Test" ) == 4 );
    VERIFY( !strcmp( buf, "Test" ) );

    VERIFY( sprintf( buf, "%ws", L"Test" ) == 4 );
    VERIFY( !strcmp( buf, "Test" ) );

    VERIFY( sprintf( buf, "%10ls", L"Test" ) == 10 );
    VERIFY( !strcmp( buf, "      Test" ) );

    VERIFY( sprintf( buf, "%-10ls", L"Test" ) == 10 );
    VERIFY( !strcmp( buf, "Test      " ) );

    VERIFY( sprintf( buf, "%#- +whlls", L"Test" ) == 4 );
    VERIFY( !strcmp( buf, "hlls" ) );

    VERIFY( sprintf( buf, "%w0s", L"Test" ) == 2 );
    VERIFY( !strcmp( buf, "0s" ) );

    VERIFY( sprintf( buf, "%w-s", L"Test" ) == 2 );
    VERIFY( !strcmp( buf, "-s" ) );

    VERIFY( sprintf( buf, "%Ls", "Test" ) == 4 );
    VERIFY( !strcmp( buf, "Test" ) );

    VERIFY( sprintf( buf, "%3h", 33 ) == 0 );
    VERIFY( !strcmp( buf, "" ) );

    VERIFY( sprintf( buf, "pho%ne", &read ) == 4 );
    VERIFY( !strcmp( buf, "phoe" ) );
    VERIFY( read == 3 );

    VERIFY( sprintf( buf, "fo%%ne", &read ) == 5 );
    VERIFY( !strcmp( buf, "fo%ne" ) );

    VERIFY( sprintf( buf, "%s", "%%%" ) == 3 );
    VERIFY( !strcmp( buf, "%%%" ) );

    VERIFY( sprintf( buf, "x%cx", 0x400 + 'X' ) == 3 );
    VERIFY( !strcmp( buf, "xXx" ) );

    /* The following test invokes undefined behaviour according to ISO C */
    VERIFY( sprintf( buf, "%k%m%q%y", 33 ) == 4 );
    VERIFY( !strcmp( buf, "kmqy" ) );

    return( 1 );
}


int Test_jzthh( void )
/********************/
{
    char            buf[128];
    signed char     sc, sc1, sc2;
    unsigned char   uc, uc1, uc2;
    intmax_t        im, im1, im2;
    uintmax_t       um, um1, um2;
    size_t          sz, sz1, sz2;
    ptrdiff_t       pd, pd1, pd2;

    /* C99 'j', 'z', 't', and 'hh' modifiers */

    sc = -123; sc2 = -1;
    VERIFY( sprintf( buf, "%hhd%hhn", sc, &sc2 ) == 4 );
    VERIFY( sc2 == 4 );
    VERIFY( !strcmp( buf, "-123" ) );
    sc1 = sc2 = -1;
    VERIFY( sscanf( buf, "%hhi%hhn", &sc1, &sc2 ) == 1 );
    VERIFY( sc1 == sc );
    VERIFY( sc2 == 4 );

    uc = 222; uc2 = -1;
    VERIFY( sprintf( buf, "%hhu%hhn", uc, &uc2 ) == 3 );
    VERIFY( uc2 == 3 );
    VERIFY( !strcmp( buf, "222" ) );
    uc1 = uc2 = -1;
    VERIFY( sscanf( buf, "%hhi%hhn", &uc1, &uc2 ) == 1 );
    VERIFY( uc1 == uc );
    VERIFY( uc2 == 3 );

    im = 1234; im2 = -1;
    VERIFY( sprintf( buf, "%jd%jn", im, &im2 ) == 4 );
    VERIFY( im2 == 4 );
    VERIFY( !strcmp( buf, "1234" ) );
    im1 = im2 = -1;
    VERIFY( sscanf( buf, "%jd%jn", &im1, &im2 ) == 1 );
    VERIFY( im1 == im );
    VERIFY( im2 == 4 );

    um = 67890123456; um2 = -1;
    VERIFY( sprintf( buf, "%ju%jn", um, &um2 ) == 11 );
    VERIFY( um2 == 11 );
    VERIFY( !strcmp( buf, "67890123456" ) );
    um1 = um2 = -1;
    VERIFY( sscanf( buf, "%jd%jn", &um1, &um2 ) == 1 );
    VERIFY( um1 == um );
    VERIFY( um2 == 11 );

    sz = 345; sz2 = -1;
    VERIFY( sprintf( buf, "%zu%zn", sz, &sz2 ) == 3 );
    VERIFY( sz2 == 3 );
    VERIFY( !strcmp( buf, "345" ) );
    sz1 = sz2 = -1;
    VERIFY( sscanf( buf, "%zd%zn", &sz1, &sz2 ) == 1 );
    VERIFY( sz1 == sz );
    VERIFY( sz2 == 3 );

    pd = -666; pd2 = -1;
    VERIFY( sprintf( buf, "%td%tn", pd, &pd2 ) == 4 );
    VERIFY( pd2 == 4 );
    VERIFY( !strcmp( buf, "-666" ) );
    pd1 = pd2 = -1;
    VERIFY( sscanf( buf, "%td%tn", &pd1, &pd2 ) == 1 );
    VERIFY( pd1 == pd );
    VERIFY( pd2 == 4 );

    return( 1 );
}

int main( int argc, char *argv[] )
/********************************/
{
#ifdef __SW_BW
    FILE    *my_stdout;

    my_stdout = freopen( "tmp.log", "a", stdout );
    if( my_stdout == NULL ) {
        fprintf( stderr, "Unable to redirect stdout\n" );
        exit( -1 );
    }
#endif
    /*** Initialize ***/
    strcpy( ProgramName, strlwr( argv[0] ) );   /* store filename */

    /******************/
    /* Start of tests */
    /******************/

    Test_scan();
    Test_scan_std_xmp();
    Test_print_integer();
    Test_print_float();
    Test_print_character();
    Test_jzthh();

    /****************/
    /* End of tests */
    /****************/

    /*** Print a pass/fail message and quit ***/
    if( NumErrors != 0 ) {
        printf( "%s: FAILURE (%d errors).\n", ProgramName, NumErrors );
        return( EXIT_FAILURE );
    }
    printf( "Tests completed (%s).\n", strlwr( argv[0] ) );
#ifdef __SW_BW
    fprintf( stderr, "Tests completed (%s).\n", strlwr( argv[0] ) );
    fclose( my_stdout );
    _dwShutDown();
#endif

    return( 0 );
}
