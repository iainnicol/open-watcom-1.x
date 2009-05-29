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
* Description:  RDOS main routines for executables and DLLs.
*
****************************************************************************/


#include "variety.h"
#include <rdos.h>

#include <stdio.h>
#include <io.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "iomode.h"
#include "strdup.h"
#include "liballoc.h"
#include "stacklow.h"
#include "sigtab.h"
#include "rtdata.h"
#include "initfini.h"
#include "rtinit.h"
#include "widechar.h"
#include "initarg.h"
#include "thread.h"
#include "mthread.h"
#include "rdosex.h"

extern void __InitThreadData( thread_data *p );
extern void __CMain( void );
#pragma aux __CMain  "*"
#pragma aux __RdosMain  "*"

int __TlsIndex = NO_INDEX;
char *_LpDllName = 0;

_WCRTLINK int *__threadid( void )
{
    return( (int *) &(__THREADDATAPTR->thread_id) );
}

thread_data             *__FirstThreadData = NULL;

static struct thread_data *__SingleThread()
{
    return( __FirstThreadData );
}

static void __NullAccessRtn( int handle )
{
    handle = handle;
}

static void __NullExitRtn() {}

static void __NullAccIOBRtn(void) {}
static void __NullAccHeapRtn(void) {}
static void __NullAccTDListRtn(void) {}

_WCRTDATA struct thread_data    *(*__GetThreadPtr)() = &__SingleThread;
void    (*_AccessFileH)(int)     = &__NullAccessRtn;
void    (*_ReleaseFileH)(int)    = &__NullAccessRtn;
void    (*_AccessIOB)(void)      = &__NullAccIOBRtn;
void    (*_ReleaseIOB)(void)     = &__NullAccIOBRtn;
void    (*_AccessNHeap)(void)    = &__NullAccHeapRtn;
void    (*_AccessFHeap)(void)    = &__NullAccHeapRtn;
void    (*_ReleaseNHeap)(void)   = &__NullAccHeapRtn;
void    (*_ReleaseFHeap)(void)   = &__NullAccHeapRtn;
void    (*_AccessTDList)(void)   = &__NullAccTDListRtn;
void    (*_ReleaseTDList)(void)  = &__NullAccTDListRtn;
void    (*_AccessFList)(void)    = &__NullAccIOBRtn;
void    (*_ReleaseFList)(void)   = &__NullAccIOBRtn;
void    (*_ThreadExitRtn)(void)  = &__NullExitRtn;

void __sig_null_rtn(void) {}
_WCRTLINK void  (*__sig_init_rtn)(void) = __sig_null_rtn;
_WCRTLINK void  (*__sig_fini_rtn)(void) = __sig_null_rtn;

#ifdef _M_IX86
 #pragma aux _end "*"
#endif
extern  char            _end;

extern  char            *_Envptr;

int                     __Is_DLL;       /* TRUE => DLL, else not a DLL */
static char             *_cmd_ptr;
static wchar_t          *_wcmd_ptr;

static char    DllName[_MAX_PATH];

int __RdosInit( int is_dll, thread_data *tdata, int hdll )
{
    int major, minor, release;

    __Is_DLL = is_dll;                                  /* 15-feb-93 */
    __FirstThreadData = tdata;
    RdosGetVersion( &major, &minor, &release );
    _RWD_osmajor = major;
    _RWD_osminor = minor;

    _LpCmdLine = (char *)RdosGetCmdLine();

    if( is_dll ) {
        RdosGetModuleName( hdll, DllName, sizeof( DllName ) );
        _LpDllName = DllName;
    }

    return( 1 );
}

void __RdosMain()
{
    thread_data             *tdata;
    REGISTRATION_RECORD     rr;
 
    __InitRtns( INIT_PRIORITY_THREAD );
    tdata = __alloca( __ThreadDataSize );
    memset( tdata, 0, __ThreadDataSize );
    tdata->__data_size = __ThreadDataSize;

    __InitThreadData( tdata );

    _LpPgmName = (char *)RdosGetExeName();
    __RdosInit( 0, tdata, RdosGetModuleHandle() );
    __NewExceptionFilter( &rr );
    __InitRtns( INIT_PRIORITY_LIBRARY+1 );
    __sig_init_rtn();
    __InitRtns( 255 );
    __CMain();
}

_WCRTLINK void __exit( unsigned ret_code )
{
    if( !__Is_DLL ) {
        __DoneExceptionFilter();
        __FiniRtns( 0, FINI_PRIORITY_EXIT-1 );
        (*_ThreadExitRtn)();
    }
    // Also gets done by __FreeThreadDataList which is activated from FiniSema4s
    // for multi-threaded apps
    __FirstThreadData = NULL;
    RdosUnloadExe( ret_code );
}
