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
*    governing rights and limitations under the License.*
*  ========================================================================
*
* Description:  Low level lseek() without file extend for Win32.
*
****************************************************************************/


#include "variety.h"
#include "int64.h"
#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include "iomode.h"
#include "rtcheck.h"
#include "seterrno.h"
#include "lseek.h"
#include "handleio.h"

/*
    DWORD SetFilePointer(
      HANDLE hFile,                // handle to file
      LONG lDistanceToMove,        // bytes to move pointer
      PLONG lpDistanceToMoveHigh,  // bytes to move pointer
      DWORD dwMoveMethod           // starting point
    );
 */

#ifndef INVALID_SET_FILE_POINTER
#define INVALID_SET_FILE_POINTER 0xFFFFFFFF
#endif

#ifdef __INT64__

_WCRTLINK __int64 __lseeki64( int hid, __int64 _offset, int origin )
{
    DWORD               rc;
    LONG                loworder, highorder;
    INT_TYPE            offset = GET_INT64(_offset);
    INT_TYPE            minusone;
    INT_TYPE            retval;
    int                 error;

    __handle_check( hid, -1 );

    HIGHWORD(highorder,offset);
    LOWWORD(loworder,offset);
    rc = SetFilePointer( __getOSHandle( hid ), loworder, &highorder, origin );
    if( rc == INVALID_SET_FILE_POINTER ) {  // this might be OK so
        error = GetLastError();             // check for sure JBS 04-nov-99
        if( error != NO_ERROR ) {
            __set_errno_dos( error );
            _clib_I32ToI64( -1L, minusone );
            RETURN_INT64(minusone);
        }
    }
    MAKE_INT64(retval,highorder,rc);
    RETURN_INT64(retval);
}

_WCRTLINK __int64 _lseeki64( int hid, __int64 offset, int origin )
{
    unsigned            iomode_flags;

    __handle_check( hid, -1 );

    /*** Set the _FILEEXT iomode_flags bit if positive offset ***/
    iomode_flags = __GetIOMode( hid );

    if( _clib_I64Positive(offset)  &&  !( iomode_flags & _APPEND ) ) {
        __SetIOMode( hid, iomode_flags | _FILEEXT );
    }
    return( __lseeki64( hid, offset, origin ) );
}

#else

_WCRTLINK long __lseek( int hid, long offset, int origin )
{
    DWORD               rc;

    __handle_check( hid, -1 );

    rc = SetFilePointer( __getOSHandle( hid ), offset, 0, origin );
    if( rc == INVALID_SET_FILE_POINTER ) {
        return( __set_errno_nt() );
    }
    return( rc );
}

#endif
