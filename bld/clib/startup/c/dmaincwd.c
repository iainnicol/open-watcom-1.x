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
* Description:  CauseWay DLL initialization and termination.
*
****************************************************************************/


#include "variety.h"
#include "initfini.h"
#include "rtdata.h"
#include <malloc.h>
#include <i86.h>

extern  int     DllMain( int termination, void *reserved );
extern  void    __CommonInit( void );

/* Perhaps this should be abstracted out of exit.c? */
void    __null_int23_exit( void ) {}              /* SIGNAL needs it */
void    (*__int23_exit)( void ) = __null_int23_exit;

void __CommonTerm( void )
{
    struct _heapinfo    hinfo;
    void _WCNEAR        *moffs;

    /* Run the normal termination first. */
    (*__int23_exit)();
    __FiniRtns( FINI_PRIORITY_EXIT, 255 );
    (*__int23_exit)();
    __FiniRtns( 0, FINI_PRIORITY_EXIT-1 );
    /* Now try to free "forgotten" memory. */
    hinfo._pentry = NULL;
    for( ;; ) {
        if( _heapwalk( &hinfo ) != _HEAPOK )
            break;
        if( hinfo._useflag ) {
            moffs = (void _WCNEAR *)FP_OFF( hinfo._pentry );
            free( (char *)moffs + sizeof( void * ) );
        }
    }
    /* Return freed memory back to the OS. */
    _heapshrink();
}

/* So that assembly caller doesn't depend on stack/register convention. */
#ifdef __386__
    #pragma aux __LibMain "*" parm caller []
#endif

unsigned __LibMain( int termination )
/***********************************/
{
    unsigned    rc;

    if( termination ) {
        rc = DllMain( termination, NULL );
        __CommonTerm();
        return( rc );
    }
    __InitRtns( 255 );  /* Run all initializers. */
    __CommonInit();
    return( DllMain( termination, NULL ) );
}
