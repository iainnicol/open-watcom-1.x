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
* Description:  Directory support for RDOS
*
****************************************************************************/

#include "variety.h"
#include "widechar.h"
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include "liballoc.h"
#include <rdos.h>

_WCRTLINK int chdir( const CHAR_TYPE *path )
{
    if ( RdosSetCurDir( path ))
        return 0;
    else
        return 1;
}

_WCRTLINK CHAR_TYPE *getcwd( CHAR_TYPE *buf, size_t size )
{
    int drive;
    char cwd[256];

    if( buf == NULL )
        return( NULL );

    drive = RdosGetCurDrive();

    cwd[0] = drive + 'A';
    cwd[1] = ':';
    cwd[2] = '\\';

    if( RdosGetCurDir( drive, &cwd[3] ) )
        return( strncpy( buf, cwd, size ) );
    else
        return( NULL );
}

_WCRTLINK int _chdrive( int drive )
{
    int    dnum;

    RdosSetCurDrive( drive );
    dnum = RdosGetCurDrive();
    return( dnum == drive ? 0 : -1 );
}

_WCRTLINK unsigned _getdrive( void ) 
{
    int    dnum;

    dnum = RdosGetCurDrive();
    return( dnum );
}

_WCRTLINK unsigned _getdiskfree( unsigned dnum, struct diskfree_t *df )
{
    unsigned stat;
    long free_units;
    int bytes_per_unit;
    long total_units;
    int disc;
    long start_sector;
    long total_sectors;
    int sector_size;
    int bios_sectors_per_cyl;
    int bios_heads;

    stat = RdosGetDriveInfo( dnum, 
                             &free_units, 
                             &bytes_per_unit, 
                             &total_units );

    if( stat ) {
        stat = RdosGetDriveDiscParam(  dnum,
                                       &disc,
                                       &start_sector,
                                       &total_sectors );
    }

    if( stat ) {
        stat = RdosGetDiscInfo(  disc,
                                 &sector_size,
                                 &total_sectors,
                                 &bios_sectors_per_cyl,
                                 &bios_heads );
    }

    if( stat ) {
        df->total_clusters = total_units;
        df->avail_clusters = free_units;
        df->sectors_per_cluster = bytes_per_unit;
        df->bytes_per_sector = sector_size;                             
    }

    if( stat ) 
        return( 0 );
    else
        return( -1 );
}

_WCRTLINK struct dirent *opendir( const char *name )
{
    struct dirent   *parent;
    int             handle;

    handle = RdosOpenDir( name );

    if( handle == 0)
        return( NULL );
    
    parent = lib_malloc( sizeof( *parent ) );
    if( parent == NULL )
        return( parent );

    parent->d_handle = handle;
    parent->d_entry_nr = 0;

    if (RdosReadDir( handle, 
                     0, 
                     NAME_MAX, 
                     parent->d_name,
                     &parent->d_size, 
                     &parent->d_attr,
                     &parent->d_msb_time,
                     &parent->d_lsb_time ))
        return( parent );
    else {
        RdosCloseDir( handle );
        lib_free( parent );
        return( NULL );
    }
}


_WCRTLINK struct dirent *readdir( struct dirent *parent )
{
    if( parent == NULL )
        return( NULL );

    parent->d_entry_nr++;

    if (RdosReadDir( parent->d_handle, 
                     parent->d_entry_nr, 
                     NAME_MAX,
                     parent->d_name,
                     &parent->d_size, 
                     &parent->d_attr,
                     &parent->d_msb_time, 
                     &parent->d_lsb_time ))
        return( parent );
    else
        return( NULL );
}


_WCRTLINK int closedir( struct dirent *dirp )
{
    if( dirp == NULL )
        return( 1 );

    RdosCloseDir( dirp->d_handle );
    lib_free( dirp );
    return( 0 );
}

_WCRTLINK int mkdir( const CHAR_TYPE *path )
{
    if( RdosMakeDir( path ))
        return 0;
    else
        return 1;
}

_WCRTLINK int rmdir( const CHAR_TYPE *path )
{
    if( RdosRemoveDir( path ))
        return 0;
    else
        return 1;
}
