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
* Description:  Common type definitions and macros widely used by Open
*               Watcom tools.
*
****************************************************************************/


#ifndef _WATCOM_H_INCLUDED_
#define _WATCOM_H_INCLUDED_

#include <errno.h>
#ifndef __WATCOMC__
#include "clibext.h"
#endif

#if !defined(__sun__) && !defined(sun) && !defined(__sgi) && !defined(__hppa) && !defined(_AIX) && !defined(__alpha) && !defined(_TYPES_H_) && !defined(_SYS_TYPES_H)
    typedef unsigned        uint;
#endif

typedef unsigned char   uint_8;
typedef unsigned short  uint_16;
#if defined (LONG_IS_64BITS)
typedef unsigned int    uint_32;
#else
typedef unsigned long   uint_32;
#endif
typedef unsigned char   unsigned_8;
typedef unsigned short  unsigned_16;
#if defined (LONG_IS_64BITS)
typedef unsigned int    unsigned_32;
#else
typedef unsigned long   unsigned_32;
#endif

typedef signed char     int_8;
typedef signed short    int_16;
#if defined (LONG_IS_64BITS)
typedef signed int      int_32;
#else
typedef signed long     int_32;
#endif
typedef signed char     signed_8;
typedef signed short    signed_16;
#if defined (LONG_IS_64BITS)
typedef signed int      signed_32;
#else
typedef signed long     signed_32;
#endif

typedef struct {
    union {
        unsigned_32     _32[2];
        unsigned_16     _16[4];
        unsigned_8       _8[8];
        struct {
#if defined( __BIG_ENDIAN__ )
            unsigned    v       : 1;
            unsigned            : 15;
            unsigned            : 16;
            unsigned            : 16;
            unsigned            : 16;
#else
            unsigned            : 16;
            unsigned            : 16;
            unsigned            : 16;
            unsigned            : 15;
            unsigned    v       : 1;
#endif
        }       sign;
        #ifdef __WATCOM_INT64__
           unsigned __int64     _64[1];
        #endif
    } u;
} unsigned_64;
typedef unsigned_64     signed_64;

/* for little endian machines */

#if defined( __BIG_ENDIAN__ )
    #define I64LO32     1
    #define I64HI32     0
#else
    #define I64LO32     0
    #define I64HI32     1
#endif

/* Define _crtn for prototypes for external C routines called from C++.
 * Eg. extern _crtn void Foo();
 */
#if !defined( _crtn )
    #if defined( __cplusplus )
        #define _crtn   "C"
    #else
        #define _crtn
    #endif
#endif

/* Macros for little/big endian conversion; These exist to simplify writing
 * code that handles both little and big endian data on either little or big
 * endian host platforms. Some of these macros could be implemented as inline
 * assembler where instructions to byte swap data in registers or read/write
 * memory access with byte swapping is available.
 */

#if defined( __BIG_ENDIAN__ )
    /* Macros to get little endian data */
    #define GET_LE_16(w)    ((((w) & 0xFF) << 8) | (((w) & 0xFF00) >> 8))
    #define GET_LE_32(w)    ((((w) & 0xFF) << 24) | (((w) & 0xFF00) << 8) | (((w) & 0xFF0000) >> 8) | (((w) & 0xFF000000) >> 24))
    /* Macros to get big endian data */
    #define GET_BE_16(w)    (w)
    #define GET_BE_32(w)    (w)

    /* Macros to convert little endian data in place */
    #define CONV_LE_16(w)   (w) = ((((w) & 0xFF) << 8) | (((w) & 0xFF00) >> 8))
    #define CONV_LE_32(w)   (w) = ((((w) & 0xFF) << 24) | (((w) & 0xFF00) << 8) | (((w) & 0xFF0000) >> 8) | (((w) & 0xFF000000) >> 24))
    /* Macros to convert big endian data in place */
    #define CONV_BE_16(w)
    #define CONV_BE_32(w)
#else
    /* Macros to get little endian data */
    #define GET_LE_16(w)    (w)
    #define GET_LE_32(w)    (w)
    /* Macros to get big endian data */
    #define GET_BE_16(w)    ((((w) & 0xFF) << 8) | (((w) & 0xFF00) >> 8))
    #define GET_BE_32(w)    ((((w) & 0xFF) << 24) | (((w) & 0xFF00) << 8) | (((w) & 0xFF0000) >> 8) | (((w) & 0xFF000000) >> 24))
    /* Macros to convert little endian data in place */
    #define CONV_LE_16(w)
    #define CONV_LE_32(w)
    /* Macros to convert big endian data in place */
    #define CONV_BE_16(w)   (w) = ((((w) & 0xFF) << 8) | (((w) & 0xFF00) >> 8))
    #define CONV_BE_32(w)   (w) = ((((w) & 0xFF) << 24) | (((w) & 0xFF00) << 8) | (((w) & 0xFF0000) >> 8) | (((w) & 0xFF000000) >> 24))
#endif

#endif
