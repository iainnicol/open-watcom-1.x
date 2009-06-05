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
* Description:  Win32 DLL startup code.
*
****************************************************************************/


#include "variety.h"
#include <rdos.h>
#include <process.h>
#include <stdlib.h>
#include "initfini.h"
#include "osthread.h"
#include "widechar.h"
#include "initarg.h"
#include "sigtab.h"

extern int __stdcall LibMain( int, int, void * );
extern void __CommonInit( void );

static int  processes;

#define DLL_PROCESS_DETACH  0
#define DLL_PROCESS_ATTACH  1
#define DLL_THREAD_ATTACH   2
#define DLL_THREAD_DETACH   3

static char    DllName[_MAX_PATH];

int __stdcall _LibMain( int hdll, int reason, void *reserved )
{
    int rc;

    switch( reason ) {
    case DLL_THREAD_ATTACH:
        rc = LibMain( hdll, reason, reserved );
        break;
    case DLL_PROCESS_ATTACH:
        __Is_DLL = 1;
        __InitRtns( 255 );
        RdosGetModuleName( hdll, DllName, sizeof( DllName ) );
        _LpDllName = DllName;
        __CommonInit();
        __sig_init_rtn();
        rc = LibMain( hdll, reason, reserved );
        if( !rc ) {
            __FiniRtns( 0, 255 );
        }
        break;
    case DLL_THREAD_DETACH:
        rc = LibMain( hdll, reason, reserved );
        break;
    case DLL_PROCESS_DETACH:
        rc = LibMain( hdll, reason, reserved );
        __FiniRtns( 0, 255 );
        break;
    }
    return( rc );
}
