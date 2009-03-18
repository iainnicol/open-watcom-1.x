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


#undef __INLINE_FUNCTIONS__
#include "variety.h"
#include <stdio.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <errno.h>
#include "liballoc.h"
#include <zdos.h>
#include "filestr.h"
#include "rtdata.h"
#include "seterrno.h"
#include "msdos.h"

extern int  __cenvarg ( const char* const*, const char* const*, char**,
                        char**, unsigned*, size_t*, int );
extern void __ccmdline ( char *, const char * const *, char *, int );

static int file_exists ( char *filename ) /* 05-apr-91 */
{
   FIND  find_buf;
   if ( DosFindFirstFile ( _A_NORMAL | _A_RDONLY | _A_HIDDEN | _A_SYSTEM,
                           filename, &find_buf ) )
      return ( 0 );
   return ( 1 );
}

static int spawn ( int mode, char  *pgmname, char  *cmdline,
                   char *env, const char * const *argv )
{
   int   retval;

   __ccmdline ( pgmname, argv, cmdline, 0 );
   retval = DosExecuteProcess ( 29, pgmname, env, 0, 0, cmdline );
   if ( retval >= 0 )
   {
      switch ( mode )
      {
         case 0: /* P_WAIT    */
            retval = DosGetChildReturnCode ( retval );
            break;
         case 2: /* P_OVERLAY */
            DosExitProcess ( 0 );
      }
   }
	if ( retval < 0 )
		retval = -1;
   return ( retval );
}

_WCRTLINK int spawnve ( int mode, const char * path,
                        const char * const argv[],
                        const char * const in_envp[] )
{
   const char * const	*envp = (const char * const *) in_envp;
   char               	*envmem;
   char               	*envstrings;
   int						len;
   char               	*np;
   char               	*p;
   char               	*end_of_p;
   int						retval;
   size_t					cmdline_len;
   char						*cmdline_mem;
   char               	*cmdline;
   char               	*drive;
   char               	*dir;
   char               	*fname;
   char               	*ext;
	unsigned					envseg;

   if ( __cenvarg ( argv, envp, &envmem, &envstrings, &envseg,
                    &cmdline_len, 0 ) == -1 )
      return ( -1 );
   len = strlen ( path ) + 7 + _MAX_PATH2;
   np = lib_malloc ( len * sizeof ( char ) );
   if ( np == NULL )
   {
      p = ( char  * ) alloca ( len * sizeof ( char ) );
      if ( p == NULL )
      {
         lib_free ( envmem );
         return ( -1 );
      }
   }
   else
   {
      p = np;
   }
   _splitpath2 ( path, p + ( len - _MAX_PATH2 ), &drive, &dir, &fname, &ext );
   cmdline_mem = lib_malloc ( cmdline_len * sizeof ( char ) );
   if ( cmdline_mem == NULL )
   {
      cmdline = ( char  * ) alloca ( cmdline_len * sizeof ( char ) );
      if ( cmdline == NULL )
      {
         retval = -1;
         __set_errno ( E2BIG );
         __set_doserrno ( E_badenv );
         goto cleanup;
      }
   }
   else
   {
      cmdline = cmdline_mem;
   }
   if ( drive[0] == 0 && dir[0] == 0 )
      dir = ".\\";
   _makepath ( p, drive, dir, fname, ext );
   __set_errno ( ENOENT );
   if ( ext[0] != '\0' )
   {
      if ( stricmp ( ext, ".bat" ) == 0 )
      {
         retval = -1; /* assume file doesn't exist */
         if ( file_exists ( p ) )
            goto spawn_command_com;
      }
      else
      {
         __set_errno( 0 );
         /* user specified an extension, so try it */
         retval = spawn ( mode, p, cmdline, envmem, argv );
      }
   }
   else
   {
      end_of_p = p + strlen ( p );
      strcpy ( end_of_p, ".com" );
      __set_errno ( 0 );
      retval = spawn ( mode, p, cmdline, envmem, argv );
   }
   if ( _RWD_errno == ENOENT || _RWD_errno == EINVAL )
   {
      __set_errno ( 0 );
      strcpy ( end_of_p, ".exe" );
      retval = spawn ( mode, p, cmdline, envmem, argv );
      if ( _RWD_errno == ENOENT || _RWD_errno == EINVAL )
      {
         /* try for a .BAT file */
         __set_errno ( 0 );
         strcpy ( end_of_p, ".bat" );
         if ( file_exists ( p ) )
         {
spawn_command_com:
            /* the environment will have to be reconstructed */
            lib_free( envmem );
            envmem = NULL;
            __ccmdline ( p, argv, cmdline, 1 );
            retval = spawnl ( mode, getenv ( "COMSPEC" ), "COMMAND", "/C", p,
                              cmdline, NULL );
         }
      }
   }
cleanup:
   lib_free ( cmdline_mem );
   lib_free ( np );
   lib_free ( envmem );
   return ( retval );
}
