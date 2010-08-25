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


#include <stdio.h>
#include <stdarg.h>

#include "errprt.h"

// these functions are in rcdll.c for the DLL version
int RcMsgFprintf( FILE *fp, OutPutInfo *info, const char *format, ... )
{
    int         err;
    int         rc = 0;
    va_list     args;
    char        *fmt;

    if( info->flags & OUTFLAG_FILE ) {
        err = fprintf( fp, "%s(%d): ", info->file, info->lineno );
        if( err < 0 ) {
            return( err );
        }
        rc += err;
    }
    switch( info->severity ) {
    case SEV_WARNING:
        fmt = "Warning! %d: ";
        break;
    case SEV_ERROR:
        fmt = "Error! %d: ";
        break;
    case SEV_FATAL_ERR:
        fmt = "Fatal Error! %d: ";
        break;
    default:
        fmt = "%d: ";
        break;
    }
    err = fprintf( fp, fmt, info->errid );
    if( err < 0 )
        return( err );
    rc += err;
    va_start( args, format );
    err = vfprintf( fp, format, args );
    va_end( args );
    if( err < 0 )
        return( err );
    return( rc + err );
}

void InitOutPutInfo( OutPutInfo *info ) {
    info->flags = 0;
}
