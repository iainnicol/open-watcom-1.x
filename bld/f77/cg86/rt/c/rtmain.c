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


//
// RTMAIN       : FORTRAN 77 run-time mainline
//

#include "ftnstd.h"
#include "rtenv.h"
#include "rundat.h"
#include "xfflags.h"
#include "errcod.h"
#include "fthread.h"

#include <stdlib.h>

extern  int             Spawn(void (*)());

// FORTRAN 77 run-time system must be initialized before we call
// user's program. Part of the run-time initialization includes
// floating-point exception handling which must be done before any
// floating-point code is executed by the user's program.
// If a FORTRAN 77 subprogram is called by a C or C++ mainline, an
// explicit call to RTSysInit() must be made by the caller.
extern  void            RTSysInit(void);

#if _OPSYS == _PENPOINT

#pragma aux __ASTACKSIZ "*"
#pragma aux __ASTACKPTR "*"

unsigned                __ASTACKSIZ = 0;        // alternate stack size
char                    *__ASTACKPTR = NULL;    // alternate stack pointer

#include "go.h"

extern  void            FMAIN(void);


U32     CDECL main( S32 argc, CHAR* argv[], U32 instance ) {
//==========================================================

// Call user's program.

    argc = argc; argv = argv; instance = instance;
    // allocate alternate stack for F77
    __ASTACKPTR = (char *)alloca( __ASTACKSIZ ) + __ASTACKSIZ;
    RTSysInit();
    Spawn( &FMAIN );
    exit( EXIT_SUCCESS );
    return( 0 );
}

#elif defined( __WINDOWS__ )

#include "fapptype.h"

#include <win386.h>

extern  int     PASCAL  DefaultWinMain(HANDLE,HANDLE,LPSTR,int,int(*)(int,char**));
extern  int             Spawn(void (*)());
extern  void            FMAIN();
extern  int             main(int,char **);

extern  char            __FAppType;


intstar4        FWINMAIN( HANDLE thishandle, HANDLE prevhandle, LPSTR cmdline,
                          int cmdshow ) {
//============================================================================

    __FAppType = FAPP_DEFAULT_GUI;
    DefaultWinMain( thishandle, prevhandle, cmdline, cmdshow, &main );
    return( 1 );
}


int     main( int argc, char *argv[] ) {
//======================================

    argc = argc; argv = argv;
    Spawn( &FMAIN );
    return( 0 );
}

#else

extern  void            FMAIN(void);


int     main( int argc, char *argv[] ) {
//======================================

// Call user's program.

    argc = argc; argv = argv;
    RTSysInit();
    Spawn( &FMAIN );
    return( 0 );
}

#endif
