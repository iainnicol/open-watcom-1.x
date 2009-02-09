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


#include <string.h>
#include <ctype.h>
#include <alloca.h>
#include <zdos.h>
#include "trpimp.h"

extern bool             CheckPointMem( unsigned, char * );
extern void             CheckPointRestore( void );
extern long             Fork(char *, unsigned);
extern char             *DOSEnvFind( char * );
extern char             *GetExeExtensions(void);

unsigned ReqFile_get_config( void )
{
   file_get_config_ret  *ret;

   ret = GetOutPtr( 0 );
   ret->file.ext_separator = '.';
   ret->file.path_separator[0] = '\\';
   ret->file.path_separator[1] = '/';
   ret->file.path_separator[2] = ':';
   ret->file.newline[0] = '\r';
   ret->file.newline[1] = '\n';
   return( sizeof( *ret ) );
}

unsigned ReqFile_open( void )
{
   int            rc;
   char           *filename;
   file_open_req  *acc;
   file_open_ret  *ret;
   static int     MapAcc[] = { MODE_READ_ONLY, MODE_WRITE_ONLY, MODE_READ_AND_WRITE };

   acc = GetInPtr( 0 );
   filename = GetInPtr( sizeof( *acc ) );
   ret = GetOutPtr( 0 );
   if( acc->mode & TF_CREATE )
      rc = DosCreateFile( _A_NORMAL, filename );
   else
      rc = DosOpenFile( MapAcc[acc->mode-1] | MODE_LOCAL, filename );
   ret->handle = rc;
   ret->err = -rc;
   return( sizeof( *ret ) );
}

unsigned ReqFile_seek( void )
{
   file_seek_req  *acc;
   file_seek_ret  *ret;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   ret->err = -DosSetFilePosition( acc->mode, acc->pos, acc->handle,
                                   ( unsigned * ) &ret->pos );
   return( sizeof( *ret ) );
}

unsigned ReqFile_read( void )
{
   file_read_req  *acc;
   file_read_ret  *ret;
   char           *buff;
   int            len;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   buff = GetOutPtr( sizeof( *ret ) );
   len = DosReadFile( acc->len, buff, acc->handle );
   if( len < 0 )
   {
      ret->err = -len;
      len      = 0;
   }
   else
      ret->err = 0;
   return( sizeof( *ret ) + len );
}

unsigned ReqFile_write( void )
{
   file_write_req  *acc;
   file_write_ret  *ret;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   ret->len = DosWriteFile( GetTotalSize() - sizeof( *acc ),
                            GetInPtr( sizeof( *acc ) ), acc->handle );
   if( ( int ) ret->len < 0 )
   {
      ret->err = -ret->len;
      ret->len = 0;
   }
   else
      ret->err = 0;
   return( sizeof( *ret ) );
}

unsigned ReqFile_write_console( void )
{
   file_write_console_ret  *ret;

   ret = GetOutPtr( 0 );
   ret->len = DosWriteFile( GetTotalSize() - sizeof( file_write_console_req ),
                            GetInPtr( sizeof( file_write_console_req ) ),
                            STDERR );
   if( ( int ) ret->len < 0 )
   {
      ret->err = -ret->len;
      ret->len = 0;
   }
   else
      ret->err = 0;
   return( sizeof( *ret ) );
}

unsigned ReqFile_close( void )
{
   file_close_req *acc;
   file_close_ret *ret;

   acc = GetInPtr( 0 );
   ret = GetOutPtr( 0 );
   ret->err = -DosCloseFile( acc->handle );
   return( sizeof( *ret ) );
}

unsigned ReqFile_erase( void )
{
   file_erase_ret *ret;

   ret = GetOutPtr( 0 );
   ret->err = -DosDeleteFile( (char *)  GetInPtr( sizeof( file_erase_req ) ) );
   return( sizeof( *ret ) );
}

int TryPath( char *name, char *end, char *ext_list )
{
   int      rc, done;
   char     *p;

   done = 0;
   do
   {
      if( *ext_list == '\0' )
         done = 1;
      for( p = end; *p = *ext_list; ++p, ++ext_list );
      rc = -DosOpenFile( MODE_READ_ONLY, name );
      if( rc > 0 )
      {
         DosCloseFile( rc );
         return( rc );
      }
      ++ext_list;
   } while( !done );
   return( rc );
}

int FindFilePath( char *pgm, char *buffer, char *ext_list )
{
   char        *p, *p2, *p3;
   int         rc, have_ext, have_path, size;

   have_ext = 0;
   have_path = 0;
   for( p = pgm, p2 = buffer; *p2 = *p; ++p, ++p2 )
   {
      switch( *p )
      {
         case '\\':
         case '/':
         case ':':
            have_path = 1;
            have_ext = 0;
            break;
         case '.':
            have_ext = 1;
            break;
      }
   }
   if( have_ext )
      ext_list = "";
   rc = TryPath( buffer, p2, ext_list );
   if( ( rc > 0 ) || have_path )
      return( rc );
   size = DosEnvVariableLength( "PATH" );
   if( size <= 0 )
      return( rc );
   p = ( char * ) alloca( size );
   if( p == NULL )
      return( rc );
   if( DosGetEnvVariable( "PATH", p ) <= 0 )
      return( rc );
   for( ;; )
   {
      if( *p == '\0' )
         break;
      p2 = buffer;
      while( *p )
      {
         if( *p == ';' )
            break;
         *p2++ = *p++;
      }
      if( p2[-1] != '\\' && p2[-1] != '/' )
      {
         *p2++ = '\\';
      }
      for( p3 = pgm; *p2 = *p3; ++p2, ++p3 );
      rc = TryPath( buffer, p2, ext_list );
      if( rc > 0 )
         break;
      if( *p == '\0' )
         break;
      ++p;
   }
   return( rc );
}

unsigned ReqFile_string_to_fullpath( void )
{
   char                          *name;
   char                          *fullname;
   char                          *ext_list;
   file_string_to_fullpath_req   *acc;
   file_string_to_fullpath_ret   *ret;

   acc = GetInPtr( 0 );
   name = GetInPtr( sizeof( *acc ) );
   ret = GetOutPtr( 0 );
   fullname = GetOutPtr( sizeof( *ret ) );
   if( acc->file_type == TF_TYPE_EXE )
      ext_list = ".com\0.exe\0";
   else
      ext_list = "";
   ret->err = FindFilePath( name, fullname, ext_list );
   if( ( int ) ret->err <= 0 )
      *fullname = '\0';
   else
      ret->err = 0;
   return( sizeof( *ret ) + 1 + strlen( fullname ) );
}

unsigned ReqFile_run_cmd( void )
{
   file_run_cmd_ret  *ret;
   file_run_cmd_req  *acc;
   int               i, len, pid;
   char              ch, *p, *path, cmdline[256];

   acc  = GetInPtr( 0 );
   p = path = GetInPtr( sizeof( file_run_cmd_req ) );
   ret = GetOutPtr( 0 );
   while( *p != '\0' )
      ++p;
   ++p;
   len = GetTotalSize( ) - ( p - path ) - sizeof( file_run_cmd_req );
   for( i = 0; i < len; i++ )
   {
      if( i == 255 )
         break;
      ch = *p;
      if( ch == '\0' )
         ch = ' ';
      cmdline[i++] = ch;
      p++;
   }
   cmdline[i] = '\0';
   pid = DosExecuteProcess( PRIORITY_DEFAULT, path, 0, PROCESS_FORGROUND,
                            PROCESS_TRACE_OFF, cmdline );
   if( pid < 0 )
      ret->err = -pid;
   else
   {
      i = DosGetChildReturnCode( pid); /* wait for process to terminate */
      ret->err = 0;
   }
   return( sizeof( *ret ) );
}
