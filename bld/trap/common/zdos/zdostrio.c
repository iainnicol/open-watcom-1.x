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
* Description:  ZDOS specific trap I/O.
*
****************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <zbios.h>
#include <zdos.h>
#include "bool.h"

extern char RWBuff[];

void StartupErr( char *err )
{
   Output( err );
   Output( "\r\n" );
   SayGNiteGracey( 1 );
}

void Output( char *str )
{
   DosWriteFile( strlen( str), str, STDERR );
}

void SayGNiteGracey( int return_code )
{
   DosExitProcess( return_code );
}

int KeyPress( void )
{
   if( BiosFullKeyboardStatus( ) )
      return( 1 );
   return( 0 );
}

int KeyGet( void )
{
   return( BiosFullKeyboardWait( ) );
}

int PathOpen( char *name, unsigned name_len, char *exts )
{
   bool  has_ext;
   bool  has_path;
   char  *ptr;
   char  *endptr;
   char  trpfile[256];
   int   handle;

   has_ext = FALSE;
   has_path = FALSE;
   endptr = name + name_len;
   for( ptr = name; ptr != endptr; ++ptr )
   {
      switch( *ptr )
      {
         case '.':
            has_ext = TRUE;
            break;
         case '/':
         case '\\':
            has_ext = FALSE;
            /* fall through */
         case ':':
            has_path = TRUE;
            break;
      }
   }
   memcpy( trpfile, name, name_len );
   if( has_ext )
   {
      trpfile[name_len] = '\0';
   }
   else
   {
      trpfile[ name_len++ ] = '.';
      memcpy( trpfile + name_len, exts, strlen( exts ) + 1 );
   }
   if( has_path )
   {
      handle = DosOpenFile( MODE_READ_ONLY, trpfile );
   }
   else
   {
      _searchenv( trpfile, "PATH", RWBuff );
      handle = DosOpenFile( MODE_READ_ONLY, RWBuff );
   }
   return( ( handle < 0 ) ? ( -1 ) : handle );
}

int WantUsage( char *ptr )
{
   if( (*ptr == '-') || (*ptr == '/') )
      ++ptr;
   return( *ptr == '?' );
}
