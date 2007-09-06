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
* Description:  DOS implementation of access().
*
****************************************************************************/


#include "variety.h"
#include "widechar.h"
#include <io.h>
#include <dos.h>
#include "tinyio.h"
#ifdef __WIDECHAR__
    #include <mbstring.h>
    #include <stdlib.h>
    #include "mbwcconv.h"
#endif

#ifdef __WATCOM_LFN__
static int CTinyAccess( const char *path, int mode )
{
    unsigned    attrs;

    if( _dos_getfileattr( path, &attrs ) != 0 ) return( -1 );
    return( ( attrs & _A_RDONLY && mode == W_OK ) ? -1 : 0 );
}

#undef  TinyAccess
#define TinyAccess   CTinyAccess
#else

extern  int           _dosret0(unsigned,unsigned);
#endif


_WCRTLINK int __F_NAME(access,_waccess)( const CHAR_TYPE *pathname, int pmode )
{
#ifndef __WATCOM_LFN__
    unsigned long   rc;
    unsigned        ax, dx;
#endif
#ifdef __WIDECHAR__
    char            mbPath[MB_CUR_MAX*_MAX_PATH]; /* single-byte char */
#endif

#ifdef __WATCOM_LFN__
    #ifdef __WIDECHAR__
        __filename_from_wide( mbPath, pathname );
        return( TinyAccess( mbPath, pmode ) );
    #else
        return( TinyAccess( pathname, pmode ) );
    #endif
#else
    #ifdef __WIDECHAR__
        __filename_from_wide( mbPath, pathname );
        rc = TinyAccess( mbPath, pmode );
    #else
        rc = TinyAccess( pathname, pmode );
    #endif

    ax = rc & 0xffff;
    dx = rc >> 16;
    return( _dosret0( ax, dx ) );
#endif
}