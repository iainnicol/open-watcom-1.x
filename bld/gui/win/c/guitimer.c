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
* Description:  GUI library timer callbacks
*
****************************************************************************/


#include "guiwind.h"
#include <stdlib.h>
#include <stdio.h>
#include "guixutil.h"

/* include from the app */
extern void GUITimer( void );

#if defined(__NT__) || defined(WILLOWS)
VOID CALLBACK GUITimerProc( HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
    gui_window *wnd;
    gui_timer_event timer;

    uMsg = uMsg; dwTime = dwTime;
    wnd = GUIGetWindow( hwnd );
    if( wnd == NULL ) {
        GUITimer();
    } else {
        timer.id = idEvent;
        GUIEVENTWND( wnd, GUI_TIMER_EVENT, &timer );
    }
}

void GUIStartTimer( gui_window *wnd, int id, int msec )
{
    if( wnd )
        SetTimer( wnd->hwnd, id, msec, GUITimerProc );
    else
        SetTimer( 0, id, msec, GUITimerProc );
}

void GUIStopTimer( gui_window *wnd, int id )
{
    if( wnd )
        KillTimer( wnd->hwnd, id );
    else
        KillTimer( 0, id );
}
#endif
