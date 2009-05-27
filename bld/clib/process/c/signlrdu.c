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
* Description:  Win32 signal handling (based on OS exception handling).
*
****************************************************************************/


#include "variety.h"
#include <signal.h>
#include <errno.h>
#include <float.h>
#include <rdos.h>
#include <excpt.h>
#include "rtdata.h"
#include "sigtab.h"
#include "sigfunc.h"
#include "seterrno.h"
#include "signlrdu.h"
#include "rtinit.h"

/* Status codes */
#define STATUS_BREAKPOINT               0x80000003L
#define STATUS_SINGLE_STEP              0x80000004L
#define STATUS_ACCESS_VIOLATION         0xC0000005L
#define STATUS_IN_PAGE_ERROR            0xC0000006L
#define STATUS_INVALID_HANDLE           0xC0000008L
#define STATUS_NO_MEMORY                0xC0000017L
#define STATUS_ILLEGAL_INSTRUCTION      0xC000001DL
#define STATUS_ARRAY_BOUNDS_EXCEEDED    0xC000008CL
#define STATUS_FLOAT_DENORMAL_OPERAND   0xC000008DL
#define STATUS_FLOAT_DIVIDE_BY_ZERO     0xC000008EL
#define STATUS_FLOAT_INEXACT_RESULT     0xC000008FL
#define STATUS_FLOAT_INVALID_OPERATION  0xC0000090L
#define STATUS_FLOAT_OVERFLOW           0xC0000091L
#define STATUS_FLOAT_STACK_CHECK        0xC0000092L
#define STATUS_FLOAT_UNDERFLOW          0xC0000093L
#define STATUS_INTEGER_DIVIDE_BY_ZERO   0xC0000094L
#define STATUS_INTEGER_OVERFLOW         0xC0000095L
#define STATUS_PRIVILEGED_INSTRUCTION   0xC0000096L
#define STATUS_STACK_OVERFLOW           0xC00000FDL
#define STATUS_CONTROL_C_EXIT           0xC000013AL

#define FALSE 0
#define TRUE !FALSE

sigtab  _SignalTable[] = {
    { SIG_IGN, -1 },                                /* unused  */
    { SIG_DFL, -1 },                                /* SIGABRT */
    { SIG_DFL, -1 },                                /* SIGFPE  */
    { SIG_DFL, STATUS_ILLEGAL_INSTRUCTION },        /* SIGILL  */
    { SIG_DFL, STATUS_CONTROL_C_EXIT },             /* SIGINT  */
    { SIG_DFL, STATUS_ACCESS_VIOLATION },           /* SIGSEGV */
    { SIG_DFL, STATUS_CONTROL_C_EXIT },             /* SIGTERM */
    { SIG_DFL, STATUS_CONTROL_C_EXIT },             /* SIGBREAK */
    { SIG_IGN, -1 },                                /* SIGUSR1 */
    { SIG_IGN, -1 },                                /* SIGUSR2 */
    { SIG_IGN, -1 },                                /* SIGUSR3 */
    { SIG_DFL, STATUS_INTEGER_DIVIDE_BY_ZERO },     /* SIGIDIVZ */
    { SIG_DFL, STATUS_INTEGER_OVERFLOW }            /* SIGIOVFL */
};

__sig_func __SetSignalFunc( int sig, __sig_func new_func )
{
    __sig_func  prev_func = NULL;

    if(( sig == SIGBREAK ) || ( sig == SIGINT )) {
        prev_func = _SignalTable[ sig ].func;
        _SignalTable[ sig ].func = new_func;
    } else {
        prev_func = _RWD_sigtab[ sig ].func;
        _RWD_sigtab[ sig ].func = new_func;
    }
    return( prev_func );
}


__sig_func __GetSignalFunc( int sig )
{
    if(( sig == SIGBREAK ) || ( sig == SIGINT ))
        return( _SignalTable[ sig ].func );

    return( _RWD_sigtab[ sig ].func );
}


long __GetSignalOSCode( int sig )
{
    if(( sig == SIGBREAK ) || ( sig == SIGINT ))
        return( _SignalTable[ sig ].os_sig_code );

    return( _RWD_sigtab[ sig ].os_sig_code );
}


__sig_func __CheckSignalExCode( int sig, long code )
{
    if( code == __GetSignalOSCode( sig ) )
        return( __GetSignalFunc( sig ) );

    return( NULL );
}

void __sigabort( void )
{
    raise( SIGABRT );
}

_WCRTLINK int __sigfpe_handler( int fpe )
{
    __sig_func  func;

    func = __GetSignalFunc( SIGFPE );
    if(( func != SIG_IGN ) && ( func != SIG_DFL ) && ( func != SIG_ERR )) {
        __SetSignalFunc( SIGFPE, SIG_DFL );
        (*(__sigfpe_func)func)( SIGFPE, fpe );
        return( 0 );
    } else if( func == SIG_IGN ) {
        return( 0 );
    }
    return( -1 );
}


_WCRTLINK __sig_func signal( int sig, __sig_func func )
{
    __sig_func  prev_func;

    if(( sig < 1 ) || ( sig > __SIGLAST )) {
        __set_errno( EINVAL );
        return( SIG_ERR );
    }

    _RWD_abort = __sigabort;               /* change the abort rtn address */

    prev_func = __GetSignalFunc( sig );
    __SetSignalFunc( sig, func );

    return( prev_func );
}


_WCRTLINK int raise( int sig )
{
    __sig_func  func;

    func = __GetSignalFunc( sig );
    switch( sig ) {
    case SIGFPE:
        __sigfpe_handler( FPE_EXPLICITGEN );
        break;
    case SIGABRT:
        if( func == SIG_DFL ) {
            __terminate();
        }
    case SIGILL:
    case SIGINT:
    case SIGSEGV:
    case SIGTERM:
    case SIGBREAK:
    case SIGUSR1:
    case SIGUSR2:
    case SIGUSR3:
    case SIGIDIVZ:
    case SIGIOVFL:
        if(( func != SIG_IGN ) && ( func != SIG_DFL ) && ( func != SIG_ERR )) {
            __SetSignalFunc( sig, SIG_DFL );
            (*func)( sig );
        }
        /*
         * If the CtrlSignalHandler was needed before we processed the
         * signal but is not needed NOW then we need to remove it since it
         * has just now become unnecessary.
         *
         * NOTE: This MAY be a bad thing to do since raise() might have been
         *       called from within CtrlSignalHandler() in which case we are
         *       removing the handler from within the handler.  Does NT care?
         */
        break;
    default:
        return( -1 );
    }
    return( 0 );
}


void __SigInit( void )
{
#if defined( __SW_BM )
    int         i;

    for( i = 1; i <= __SIGLAST; ++i ) {
        _RWD_sigtab[ i ] = _SignalTable[ i ];
    }
#endif

    __oscode_check_func = __CheckSignalExCode;
    __raise_func        = raise;
}


void __SigFini( void )
{
    /*
     * If there are still SIGINT or SIGBREAK handlers in the sig table,
     * then the CtrlSignalHandler is still loaded and we want to get
     * rid of it.
     */
    __SetSignalFunc( SIGINT, SIG_DFL );
    __SetSignalFunc( SIGBREAK, SIG_DFL );
}



void __sig_init( void )
{
    __sig_init_rtn = __SigInit;
    __sig_fini_rtn = __SigFini;
    _RWD_FPE_handler = (FPEhandler *)__sigfpe_handler;
}


AXI( __sig_init, INIT_PRIORITY_LIBRARY )
