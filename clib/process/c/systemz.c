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
#include "widechar.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <process.h>
#include <errno.h>
#include "rtdata.h"
#include "seterrno.h"

_WCRTLINK int system ( const CHAR_TYPE *cmd )
{
   register CHAR_TYPE   *name;

   name = getenv ( "COMSPEC" );
   if ( cmd == NULL )
   {
      if ( name != NULL )
      {
         if ( access ( name, 0 ) == 0 )
            return ( 1 );     /* COMMAND.COM/COMMAND.EXE is available */
         name = NULL;
      }
   }
   if ( name == NULL )
   {
      __set_errno ( ENOENT ); /* Set errno */
      return ( 0 );           /* COMMAND.COM/COMMAND.EXE not available */
   }
   return ( spawnlp ( P_WAIT, "COMMAND", "COMMAND", "/C", cmd, NULL ) );
}
