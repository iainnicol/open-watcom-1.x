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
* Description: ZDOS trap file loading.
*
****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <zdos.h>
#include "trpimp.h"
#include "tcerr.h"
#include "exezdos.h"

typedef struct
{
   unsigned int   signature;
   trap_version   ( TRAPENTRY *init )( );
   unsigned int   ( TRAPENTRY *request ) ( );
   void           ( TRAPENTRY *fini ) ( );
} trap_header;

trap_header          *header;
extern unsigned      ( TRAPENTRY *ReqFunc )( unsigned, mx_entry *,
                                             unsigned, mx_entry * );
extern  int          PathOpen( char *, unsigned, char * );
extern trap_version  TrapVer;

void KillTrap( void )
{
   void ( TRAPENTRY *fini )( ) = header->fini;

   fini( );
   ReqFunc = NULL;
   free( header );
}

char *ReadInTrap( int handle )
{
   char              buffer[512];
   zdos_exe_header   *hdr;
   unsigned int      **relocation, base;
   int               count, index;
   unsigned          position;

   if( DosReadFile( sizeof( hdr ), buffer, handle ) != sizeof( hdr ) )
      return( TC_ERR_BAD_TRAP_FILE );
   hdr = ( zdos_exe_header * ) buffer;
   if( hdr->signature != ZDOS_SIGNATURE )
      return( TC_ERR_BAD_TRAP_FILE );
   header = malloc( hdr->image_size + hdr->extra_size );
   if( header == NULL )
      return( TC_ERR_OUT_OF_DOS_MEMORY );
   /* read the image */
   DosSetFilePosition( SEEK_FROM_START, hdr->image_offset, handle, &position );
   if( DosReadFile( hdr->image_size, header, handle ) != hdr->image_size )
      return( TC_ERR_BAD_TRAP_FILE );
   /* relocate the image */
   DosSetFilePosition( SEEK_FROM_START, hdr->reloc_offset, handle, &position );
   base  = (unsigned int ) header - hdr->reloc_base;
   count = hdr->num_relocs;
   index = 0;
   while( count )
   {
      if( index == 0 )
      {
         if( DosReadFile( 512, buffer, handle ) < 0 )
            return( TC_ERR_BAD_TRAP_FILE );
         relocation = ( unsigned int ** ) buffer;
      }
      *relocation[index] += base;
      if( ++index == 128 )
         index = 0;
      count--;
   }
   return( NULL );
}

char *LoadTrap( char *trapbuff, char *buff, trap_version *trap_ver )
{
   char           init_error[256];
   int            handle;
   char           *ptr;
   char           *parm;
   trap_version   ( TRAPENTRY *init )( void *, void *, unsigned_8 );

   if( trapbuff == NULL )
      trapbuff = "std";
   for( ptr = trapbuff; *ptr != '\0' && *ptr != ';'; ++ptr );
   parm = (*ptr != '\0') ? ptr + 1 : ptr;
   handle = PathOpen( trapbuff, ptr - trapbuff, "trp" );
   if( handle <= 0 )
   {
      sprintf( buff, TC_ERR_CANT_LOAD_TRAP, trapbuff );
      return( buff );
   }
   strcpy( buff, TC_ERR_WRONG_TRAP_VERSION );
   ptr = ReadInTrap( handle );
   DosCloseFile( handle );
   if( ptr != NULL )
      return( ptr );
   if( header->signature != 'PART' )
      return( buff );
   init = header->init;
   *trap_ver = init( parm, init_error, trap_ver->remote );
   if( init_error[0] != '\0' )
   {
      strcpy( buff, init_error );
      return( buff );
   }
   if( !TrapVersionOK( *trap_ver ) )
   {
      KillTrap();
      return( buff );
   }
   TrapVer = *trap_ver;
   ReqFunc = header->request;
   return( NULL );
}


