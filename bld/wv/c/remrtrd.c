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
* Description:  Interface for non-blocking thread services
*
****************************************************************************/


#include "dbgdefn.h"
#include "dbgreg.h"
#include "trpcore.h"
#include "trprtrd.h"
#include "dbgio.h"

#define DEFAULT_TID     1

extern trap_shandle     GetSuppId( char * );
extern void             CheckForNewThreads( bool set_exec );
extern void             GetSysConfig( void );
extern void             CheckMADChange( void );

#if defined(__GUI__) && defined(__OS2__)
extern unsigned         OnAnotherThread( unsigned(*)(), unsigned, void *, unsigned, void * );
#else
#define                 OnAnotherThread( a,b,c,d,e ) a( b,c,d,e )
#endif

extern void             InitRunThreadWnd();

extern machine_state    *DbgRegs;
extern system_config    SysConfig;

static trap_shandle     SuppRunThreadId;

bool InitRunThreadSupp( void )
{
    SuppRunThreadId = GetSuppId( RUN_THREAD_SUPP_NAME );
    if( SuppRunThreadId == 0 ) return( FALSE );
    InitRunThreadWnd();
    return( TRUE );
}

bool HaveRemoteRunThread( void )
{
     /* only available on selected hosts for now */
#if defined( __NT__ ) && defined( __GUI__ )
    return( SuppRunThreadId != 0 );
#elif defined( __RDOS__ )
    return( SuppRunThreadId != 0 );
#else
    return( FALSE );
#endif
}

bool RemoteGetRunThreadInfo( int row, char *infotype, int *width, char *header, int maxsize )
{
    mx_entry            in[1];
    mx_entry            out[2];
    run_thread_info_req acc;
    run_thread_info_ret ret;

    if( SuppRunThreadId == 0 ) return( FALSE );

    acc.supp.core_req = REQ_PERFORM_SUPPLEMENTARY_SERVICE;
    acc.supp.id = SuppRunThreadId;
    acc.req = REQ_RUN_THREAD_INFO;
    acc.col = row;
    ret.info = 0;

    in[0].ptr = &acc;
    in[0].len = sizeof( acc );
    out[0].ptr = &ret;
    out[0].len = sizeof( ret );
    out[1].ptr = header;
    out[1].len = maxsize;
    TrapAccess( 1, &in, 2, &out );

    if( ret.info ) {
        *infotype = ret.info;
        *width = ret.width;
        return( TRUE );
    } else
        return( FALSE );
}

dtid_t RemoteGetNextRunThread( dtid_t tid )
{
    run_thread_get_next_req acc;
    run_thread_get_next_ret ret;

    if( SuppRunThreadId == 0 ) return( tid == 0 ? DEFAULT_TID : 0 );

    acc.supp.core_req = REQ_PERFORM_SUPPLEMENTARY_SERVICE;
    acc.supp.id = SuppRunThreadId;
    acc.req = REQ_RUN_THREAD_GET_NEXT;
    acc.thread = tid;
    TrapSimpAccess( sizeof( acc ), &acc, sizeof( ret ), &ret );
    return( ret.thread );
}

void RemotePollRunThread( void )
{
    run_thread_poll_req      acc;
    run_thread_poll_ret      ret;

    if( SuppRunThreadId == 0 ) return;

    acc.supp.core_req = REQ_PERFORM_SUPPLEMENTARY_SERVICE;
    acc.supp.id = SuppRunThreadId;
    acc.req = REQ_RUN_THREAD_POLL;

    OnAnotherThread( TrapSimpAccess, sizeof( acc ), &acc, sizeof( ret ), &ret );
    CONV_LE_16( ret.conditions );

    if( ret.conditions & COND_CONFIG ) {
        GetSysConfig();
        CheckMADChange();
    }
    if( ret.conditions & COND_THREAD ) {
        CheckForNewThreads( TRUE );
    }
}

void RemoteUpdateRunThread( thread_state *thd )
{
    mx_entry                        in[1];
    mx_entry                        out[2];
    run_thread_get_runtime_req      acc;
    run_thread_get_runtime_ret      ret;

    if( SuppRunThreadId == 0 ) return;

    acc.supp.core_req = REQ_PERFORM_SUPPLEMENTARY_SERVICE;
    acc.supp.id = SuppRunThreadId;
    acc.req = REQ_RUN_THREAD_GET_RUNTIME;
    acc.thread = thd->tid;

    in[0].ptr = &acc;
    in[0].len = sizeof( acc );
    out[0].ptr = &ret;
    out[0].len = sizeof( ret );
    out[1].ptr = thd->extra;
    out[1].len = MAX_THD_EXTRA_SIZE;
    TrapAccess( 1, &in, 2, &out );

    thd->state = ret.state;
    thd->cs = ret.cs;
    thd->eip = ret.eip;    
}
