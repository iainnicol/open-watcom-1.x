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
* Description:  Handle based file operations for RDOS.
*
****************************************************************************/


#include "variety.h"
#include "widechar.h"
#include <rdos.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <share.h>
#include <time.h>

_WCRTLINK int unlink( const CHAR_TYPE *filename ) 
{
    __ptr_check( filename, 0 );

    if( RdosDeleteFile( filename ) )
        return( 0 );
    else
        return( -1 );  
}

_WCRTLINK int creat( const CHAR_TYPE *name, mode_t pmode )
{
    __ptr_check( name, 0 );

    return RdosCreateFile( name, 0 );
}

_WCRTLINK int open( const CHAR_TYPE *name, int mode, ... )
{
    int permission;
    va_list args;

    va_start( args, mode );
    permission = va_arg( args, int );
    va_end( args );
    return RdosOpenFile( name, 0 );    
}


_WCRTLINK int sopen( const CHAR_TYPE *name, int mode, int shflag, ... )
{
    va_list             args;

    va_start( args, shflag );
    return RdosOpenFile( name, 0 );    
}

_WCRTLINK int close( int handle )
{
    RdosCloseFile( handle );
    return( 0 );
}

_WCRTLINK int dup( int handle )
{
    return( RdosDuplFile( handle ) );
}

_WCRTLINK int eof( int handle )
{
    if( RdosGetFileSize( handle ) == RdosGetFilePos( handle ) )
        return( 1 );
    else
        return( 0 );        
}

_WCRTLINK long filelength( int handle )
{
    return( RdosGetFileSize( handle ) );
}

_WCRTLINK int chsize( int handle, long size )
{
    RdosSetFileSize( handle, size );
    return( 0 );
}

_WCRTLINK int fstat( int handle, struct stat *buf )
{
    unsigned long       msb;
    unsigned long       lsb;
    int                 ms;
    int                 us;
    struct tm           tm;

    buf->st_dev = RdosIsDevice( handle );
    buf->st_rdev = buf->st_dev;

    buf->st_nlink = 1;
    buf->st_uid = buf->st_gid = 0;
    buf->st_ino = handle;
    buf->st_mode = 0;
    buf->st_mode |= S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;

    if( buf->st_dev ) {
        buf->st_size = 0;
        buf->st_atime = buf->st_ctime = buf->st_mtime = 0;
        buf->st_mode |= S_IFCHR;
    } else {                /* file */
        RdosGetFileTime( handle, &msb, &lsb );
        RdosDecodeMsbTics( msb, 
                           &tm.tm_year, 
                           &tm.tm_mon,
                           &tm.tm_mday,
                           &tm.tm_hour );

        RdosDecodeLsbTics( lsb,
                           &tm.tm_min,
                           &tm.tm_sec,
                           &ms,
                           &us );
                           
        tm.tm_year -= 1900;
        tm.tm_mon--;
        tm.tm_isdst = -1;
        tm.tm_wday = -1;
        tm.tm_yday = -1;

        buf->st_mtime = mktime( &tm );
        buf->st_atime = buf->st_ctime = buf->st_mtime;
        buf->st_size = filelength( handle );
        buf->st_mode |= S_IFREG;
    }
    buf->st_btime = buf->st_mtime;
    buf->st_attr = 0;
    buf->st_archivedID = 0;
    buf->st_updatedID = 0;
    buf->st_inheritedRightsMask = 0;
    buf->st_originatingNameSpace = 0;
    return( 0 );
}

_WCRTLINK int setmode( int handle, int mode )
{
    return( mode );
}

_WCRTLINK int fsync( int handle )
{
    return( -1 );
}

_WCRTLINK int lock( int handle, unsigned long offset, unsigned long nbytes )
{
    return( -1 );
}

_WCRTLINK int unlock( int handle, unsigned long offset, unsigned long nbytes )
{
    return( -1 );
}

_WCRTLINK int (locking)( int handle, int mode, unsigned long nbytes )
{
    return( -1 );
}

_WCRTLINK off_t lseek( int handle, off_t offset, int origin )
{
    off_t pos;
    
    switch( origin ) {
        case SEEK_SET:
            RdosSetFilePos( handle, offset );
            break;
            
        case SEEK_CUR:
            pos = RdosGetFilePos( handle );
            pos += offset;
            RdosSetFilePos( handle, pos );
            break;

        case SEEK_END:
            pos = RdosGetFileSize( handle );
            pos += offset;
            RdosSetFilePos( handle, pos );
            break;
    }
    return( RdosGetFilePos( handle ) );            
}

_WCRTLINK off_t tell( int handle )
{
    return( RdosGetFilePos( handle ) );
}

int __qread( int handle, void *buffer, unsigned len )
{
    return( RdosReadFile( handle, buffer, len ) );
}

int __qwrite( int handle, const void *buffer, unsigned len )
{
    return( RdosWriteFile( handle, buffer, len ) );
}

_WCRTLINK int read( int handle, void *buffer, unsigned len )
{
    return( RdosReadFile( handle, buffer, len ) );
}

_WCRTLINK int write( int handle, const void *buffer, unsigned len )
{
    return( RdosWriteFile( handle, buffer, len ) );
}
