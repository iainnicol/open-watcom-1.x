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
#include <stdio.h>
#include <signal.h>
#include <zdos.h>
#include <errno.h>
#include <float.h>
#include "rtdata.h"
#include "sigtab.h"
#include "extfunc.h"
#include "seterrno.h"

#define __SIGLAST       SIGIOVFL

typedef	void sig_func ( );
extern	void __terminate ( );
extern	void ( *__abort )( );

static	void ( __cdecl *OldAlarmVector )( CONTEXT ) = 0;
static	void ( __cdecl *OldBreakVector )( CONTEXT ) = 0;
static	void ( __cdecl *OldFpuVector )( CONTEXT ) = 0;

static void ( *_SignalTable[] )( int ) =
{
	SIG_IGN,        /* unused  */
	SIG_DFL,        /* SIGABRT */
	SIG_IGN,        /* SIGFPE  */
	SIG_DFL,        /* SIGILL  */
	SIG_DFL,        /* SIGINT  */
	SIG_DFL,        /* SIGSEGV */
	SIG_DFL,        /* SIGTERM */
	SIG_DFL,        /* SIGBREAK */
	SIG_IGN,        /* SIGUSR1 */
	SIG_IGN,        /* SIGUSR2 */
	SIG_IGN,        /* SIGUSR3 */
	SIG_DFL,        /* SIGIDIVZ */
	SIG_DFL         /* SIGIOVFL */
};

void __sigabort()
{
   raise ( SIGABRT );
}

static void __cdecl CmosAlarmHandler ( CONTEXT Context )
{
	raise ( SIGINT );
}

static void __cdecl ControlBreakHandler ( CONTEXT Context )
{
	raise ( SIGBREAK );
}

static void __cdecl FpuExceptionHandler ( CONTEXT Context )
{
	raise ( SIGFPE );
}

#pragma aux __sigfpe_handler parm [eax]

_WCRTLINK void __sigfpe_handler ( int fpe_type )
{
	sig_func *func = ( sig_func * ) _SignalTable[SIGFPE];
	if ( func != SIG_IGN  &&  func != SIG_DFL  &&  func != SIG_ERR )
	{
		_SignalTable[SIGFPE] = SIG_DFL;	/* 09-nov-87 FWC */
		if ( OldFpuVector != 0 )
			DosSetVector ( 0x10, OldFpuVector );
		( *func )( SIGFPE, fpe_type );	/* so we can pass 2'nd parm */
	}
}

_WCRTLINK void ( *signal ( int sig, void ( *func )( int ) ) )( int )
{
	void ( *prev_func )( int );

	if ( ( sig < 1 ) || ( sig > __SIGLAST ) )
	{
		__set_errno ( EINVAL );
		return ( SIG_ERR );
	}
	__abort = __sigabort;					/* change the abort rtn address */
	if ( sig == SIGINT )
	{
		if ( func == SIG_DFL )
		{
			if ( OldAlarmVector != 0 )
				DosSetVector ( 0x1f, OldAlarmVector );
		}
		else if ( func != SIG_ERR )
		{
			if ( OldAlarmVector == 0 )
				OldAlarmVector = DosGetVector ( 0x1f );
			DosSetVector ( 0x1f, CmosAlarmHandler );
		}
	}
	else if ( sig == SIGBREAK )
	{
		if ( func == SIG_DFL )
		{
			if ( OldBreakVector != 0 )
				DosSetVector ( 0x1e, OldBreakVector );
		}
		else if ( func != SIG_ERR )
		{
			if ( OldBreakVector == 0 )
				OldBreakVector = DosGetVector ( 0x1e );
			DosSetVector ( 0x1e, ControlBreakHandler );
		}
	}
	else if ( sig == SIGFPE )
	{
		if ( func == SIG_DFL )			/* Restore old vector and turn on exceptions */
		{
			if ( OldFpuVector != 0 )
				DosSetVector ( 0x10, OldFpuVector );
			_control87 ( ~0, 0x002f );
		}
		else if ( func != SIG_ERR )	/* Turn off exceptions and install our vector */
		{
			_control87 ( 0, EM_INVALID | EM_ZERODIVIDE | EM_OVERFLOW | EM_UNDERFLOW );
			if ( OldFpuVector == 0 )
				OldFpuVector = DosGetVector ( 0x10 );
			DosSetVector ( 0x10, FpuExceptionHandler );
		}
	}
	prev_func = _RWD_sigtab[sig];
	_RWD_sigtab[sig] = func;
	return ( prev_func );
}

_WCRTLINK int raise ( int sig )
{
	sig_func *func;

   func = _RWD_sigtab[sig];
   switch ( sig )
   {
      case SIGFPE:
         __sigfpe_handler ( FPE_EXPLICITGEN );
         break;
      case SIGABRT:
         if ( func == SIG_DFL )
            __terminate ();
		case SIGINT:
			if ( func != SIG_IGN  &&  func != SIG_DFL  &&  func != SIG_ERR )
			{
				_RWD_sigtab[sig] = SIG_DFL;      /* 09-nov-87 FWC */
				if ( OldAlarmVector != 0 )
					DosSetVector ( 0x1f, OldAlarmVector );
				(*func)(sig);
			}
			break;
		case SIGBREAK:
			if ( func != SIG_IGN  &&  func != SIG_DFL  &&  func != SIG_ERR )
			{
				_RWD_sigtab[ sig ] = SIG_DFL;      /* 09-nov-87 FWC */
				if ( OldBreakVector != 0 )
					DosSetVector ( 0x1e, OldBreakVector );
				(*func)(sig);
			}
			break;
		case SIGILL:
		case SIGSEGV:
		case SIGTERM:
		case SIGUSR1:
		case SIGUSR2:
		case SIGUSR3:
		case SIGIDIVZ:
		case SIGIOVFL:
			if ( func != SIG_IGN  &&  func != SIG_DFL  &&  func != SIG_ERR )
			{
				_RWD_sigtab[ sig ] = SIG_DFL;      /* 09-nov-87 FWC */
				(*func)(sig);
			}
			break;
		default:
			return ( -1 );
	}
	return ( 0 );
}
