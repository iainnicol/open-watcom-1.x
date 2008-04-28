/****************************************************************************
*
*                            Open Watcom Project
*
*  Copyright (c) 2004-2007 The Open Watcom Contributors. All Rights Reserved.
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
* Description:  wgml utility functions
*
****************************************************************************/
 
#define __STDC_WANT_LIB_EXT1__  1      /* use safer C library              */
 
#include <stdarg.h>
 
#include "wgml.h"
#include "gvars.h"
 
 
char    *skip_to_quote( char *p, char quote )
{
    while( *p && quote != *p ) {
        p++;
    }
    return( p+1 );
}
 
/***************************************************************************/
/*  conversion routines for Horizontal / Vertical space units              */
/*  Accepted formats:                                                      */
/*       1234        assume chars / lines                                  */
/*       8m          Ems                                                   */
/*       22Dv        Device units                                          */
/*                                                                         */
/*       12.34i      inch             (1 inch = 2.54cm)                    */
/*       5C11        Cicero  + points (12 points = 1C = 1/6 inch)          */
/*       6p10        Pica    + points (12 points = 1P = 1/6 inch)          */
/*                                     1C  0.035277... mm                  */
/*                                     1p  0,002939814814... mm            */
/*       5.23cm      centimeter                                            */
/*       6.75mm      millimeter                                            */
/*                                                                         */
/*    the absolute units (the last 5) will be stored as millimeter         */
/*    in 1/10000 millimeter units,                                         */
/*    the relative ones will be stored as is.                              */
/*                                                                         */
/*    returns  filled structure su, returncode TRUE                        */
/*               or  returncode FALSE in case of error                     */
/***************************************************************************/
 
bool    to_internal_SU( char **scanp, su *converted )
{
    bool    converterror = true;
    char    *p;
    char    *ps;
    ldiv_t          div;
    su              *s;
    long            wh;
    long            wd;
    char            *pp;               // ptr to decimal point or embedded unit
    char            *pu;               // ptr to trailing unit
    char            *pd1;              // ptr to 0.1 decimal
    char            *pdn;              // ptr to last digit +1
    char            unit[ 4 ];
    char            quote;
    int             k;
    char            sign;
 
    unit[ 3 ] = '\0';
    unit[ 2 ] = '\0';
    unit[ 1 ] = '\0';
    s = converted;
    p = *scanp;
    ps = s->su_txt;
    *ps = '\0';
    wh = 0;
    wd = 0;
    pp = NULL;
    quote = '\0';
 
    s->su_u = SU_undefined;
    if( *p == '\'' || *p == '"' ) {     // ignore but remember quote
        quote = *p++;
    }
    if( *p == '+' || *p == '-' ) {
        sign = *p;
        *ps++ = *p++;
        s->su_relative = true;  // value is added / subtracted from old value
    } else {
        sign = '+';
        s->su_relative = false;         // value replaces old value
    }
    while( *p >= '0' && *p <= '9' ) {   // whole part
        wh = 10 * wh + *p - '0';
        *ps++ = *p++;
        if( ps >= s->su_txt + sizeof( s->su_txt ) ) {
            if( quote ) {
                p = skip_to_quote( p, quote );
            }
            *scanp = p;
            return( converterror );
        }
    }
    pp = p;
    k = 0;
    while( *p && isalpha( *p ) ) {
        unit[ k++ ] = tolower( *p );    // save Unit
        *ps++ = *p++;
        if( ps >= s->su_txt + sizeof( s->su_txt ) || k > 2 ) {
            if( quote ) {
                p = skip_to_quote( p, quote );
            }
            *scanp = p;
            return( converterror );
        }
    }
    if( p > pp + 2 ) {
         if( quote ) {
             p = skip_to_quote( p, quote );
         }
         *scanp = p;
         return( converterror );        // no unit has more than 2 chars
    }
    pd1 = NULL;
    pdn = NULL;
 
    if( p == pp && *p == '.' ) {        // no unit found, try dec point
        *ps++ = *p++;
        pd1 = p;                        // remember start of decimals
        if( ps >= s->su_txt + sizeof( s->su_txt ) ) {
            if( quote ) {
                p = skip_to_quote( p, quote );
            }
            *scanp = p;
            return( converterror );
        }
        while( *p >= '0' && *p <= '9' ) {   // try decimal part
            wd = 10 * wd + *p - '0';
            *ps++ = *p++;
            if( ps >= s->su_txt + sizeof( s->su_txt ) ) {
                if( quote ) {
                    p = skip_to_quote( p, quote );
                }
                *scanp = p;
                return( converterror );
            }
            if( wd > 99 ) {             // more than two digits
                if( quote ) {
                    p = skip_to_quote( p, quote );
                }
                *scanp = p;
                return( converterror );
            }
        }
        pdn = p;
    } else {
        if( k ) {                       // unit found
            pd1 = p;
            if( ps >= s->su_txt + sizeof( s->su_txt ) ) {
                if( quote ) {
                    p = skip_to_quote( p, quote );
                }
                *scanp = p;
                return( converterror );
            }
            while( *p >= '0' && *p <= '9' ) {   // try decimal part
                wd = 10 * wd + *p - '0';
                *ps++ = *p++;
                if( ps >= s->su_txt + sizeof( s->su_txt ) ) {
                    if( quote ) {
                        p = skip_to_quote( p, quote );
                    }
                    *scanp = p;
                    return( converterror );
                }
                if( wd > 99 ) {         // more than two digits
                    if( quote ) {
                        p = skip_to_quote( p, quote );
                    }
                    *scanp = p;
                    return( converterror );
                }
            }
            pdn = p;
        }
    }
    k = 0;
    pu = p;
    if( *p ) {                          // not yet at end
        while( *p && isalpha( *p ) ) {  // try trailing unit
            unit[ k++ ] = tolower( *p );
            *ps++ = *p++;
            if( ps >= s->su_txt + sizeof( s->su_txt ) || k > 2 ) {
                if( quote ) {
                    p = skip_to_quote( p, quote );
                }
                *scanp = p;
                return( converterror );
            }
        }
    }
 
    *ps = '\0';
 
    s->su_whole = wh;
    s->su_dec   = wd;
 
    if( (quote && *p != quote ) || (!quote && *p == '\'') ) {
        if( quote ) {
            p = skip_to_quote( p, quote );
        }
        *scanp = p;
        return( converterror );
    }
    if( quote ) {
        p++;                            // over quote
    }
 
    *scanp = p;                         // report back scan position
 
    if( k == 0 ) {                      // no trailing unit
        pu = NULL;
    } else {
        if( pu == pp ) {                // no decimals, no unit
            pu = NULL;
        }
    }
    if( *pp == '.' ) {                  // dec point found
        if( pu == NULL ) {              // need trailing unit
            return( converterror );
        }
    } else {                            // no decimals
        if( pu != NULL ) {              // but unit specified twice?
            return( converterror );
        }
    }
 
    /***********************************************************************/
    /*  check for valid unit                                               */
    /***********************************************************************/
    if( unit[ 1 ] == '\0' ) {           // single letter unit
        switch( unit[ 0 ] ) {
        case 'i' :
            s->su_u = SU_inch;
            break;
        case 'd' :
            s->su_u = SU_dv;
            break;
        case 'm' :
            s->su_u = SU_ems;
            break;
        case 'c' :
            s->su_u = SU_cicero;
            break;
        case 'p' :
            s->su_u = SU_pica;
            break;
        case '\0' :                     // no unit is characters or lines
            s->su_u = SU_chars_lines;
            break;
        default:
            return( converterror );
            break;
        }
    } else {                            // two letter unit
        if( unit[ 1 ] == 'm' ) {        // cm, mm ?
            if( unit[ 0 ] == 'c' ) {
                s->su_u = SU_cm;
            } else if( unit[ 0 ] == 'm' ) {
                s->su_u = SU_mm;
            } else {                    // invalid unit
                return( converterror );
            }
        } else {                        // invalid unit
            return( converterror );
        }
    }
 
    s->su_conv = 0;
    k = 1;
    switch( s->su_u ) {
    case SU_chars_lines :
    case SU_dv :
    case SU_ems :
        if( wd != 0 ) {                 // no decimals allowed
            return( converterror );
        }
        break;
    case SU_inch :                      // inch, cm, mm valid with decimals
        if( pd1 != NULL ) {
            if( pdn - pd1 == 1 ) {
                k = 10;                // only 0.1 digit
            }
        }
        s->su_conv = (wh * 100 + wd * k) * 25400L;
        break;
    case SU_cm :
        if( pd1 != NULL ) {
            if( pdn - pd1 == 1 ) {
                k = 10;                // only 0.1 digit
            }
        }
        s->su_conv = (wh * 100 + wd * k) * 10000L;
        break;
    case SU_mm :
        if( pd1 != NULL ) {
            if( pdn - pd1 == 1 ) {
                k = 10;                // only 0.1 digit
            }
        }
        s->su_conv = (wh * 100 + wd * k) * 1000L;
        break;
    case SU_cicero :
        if( wd > 12 ) {
            div = ldiv( wd, 12 );
            wh += div.quot;
            wd = div.rem;
        }
        s->su_conv = wh * 2540000L / 5L + wd * 2540000L / 60L;
        break;
   case SU_pica :                      // pica / Cicero
        if( wd > 12 ) {
            div = ldiv( wd, 12 );
            wh += div.quot;
            wd = div.rem;
        }
        s->su_conv = wh * 2540000L / 6L + wd * 2540000L / 72L;
        break;
    default:
        break;
    }
    if( sign == '-' ) {
        s->su_conv  = -s->su_conv;
        s->su_whole = -s->su_whole;
    }
    converterror = false;
    return( converterror );
}
#if 0
int main( int argc, char *argv[] )
{
    bool    error;
    su      aus;
//    char    ein1[] = "1.2I";
    char    *ein1 = "'6p11'";
    char   *p = ein1;
 
    error = to_internal_SU( &p, &aus );
 
 
    return(0);
}
#endif
 
 
