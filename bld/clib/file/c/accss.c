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
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
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

extern  int           _dosret0(unsigned,unsigned);


_WCRTLINK int __F_NAME(access,_waccess)( const CHAR_TYPE *pathname, int pmode )
    {
        unsigned long   rc;
        unsigned        ax, dx;
#ifdef __WIDECHAR__
        char            mbPath[MB_CUR_MAX*_MAX_PATH]; /* single-byte char */
#endif

        #ifdef __WIDECHAR__
            __filename_from_wide( mbPath, pathname );
            rc = TinyAccess( mbPath, pmode );
        #else
            rc = TinyAccess( pathname, pmode );
        #endif

        ax = rc & 0xffff;
        dx = rc >> 16;
        return _dosret0( ax, dx );
    }
