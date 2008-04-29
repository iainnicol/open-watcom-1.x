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
* Description:  Mainline for DLL-using build of linker.
*
****************************************************************************/


#include <process.h>
#include "walloca.h"
#include "idedrv.h"


int main( void )
{
    IDEDRV          inf;
    char            *cmdline;
    int             cmdlen;
    IDEDRV_STATUS   status;

    status = IDEDRV_ERR_LOAD;
    IdeDrvInit( &inf, "wlink.dll", NULL );

    cmdline = NULL;
    cmdlen = _bgetcmd( NULL, 0 );
    if( cmdlen != 0 ) {
        cmdlen++;               // add 1 for null char
        cmdline = alloca( cmdlen );
        if( cmdline != NULL ) _bgetcmd( cmdline, cmdlen );
    }
    status = IdeDrvExecDLL( &inf, cmdline );
    if( status != IDEDRV_SUCCESS && status != IDEDRV_ERR_RUN_EXEC
                                 && status != IDEDRV_ERR_RUN_FATAL ) {
        IdeDrvPrintError( &inf );
    }
    IdeDrvUnloadDLL( &inf );
    return status != IDEDRV_SUCCESS;
}
