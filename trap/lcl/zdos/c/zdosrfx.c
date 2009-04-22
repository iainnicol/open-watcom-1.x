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
#include <zdos.h>
#include "trpimp.h"

unsigned ReqRfx_rename()
{
    char            *old_name;
    char            *new_name;
    rfx_rename_ret  *ret;

    old_name = GetInPtr( sizeof( rfx_rename_req ) );
    new_name = GetInPtr( sizeof( rfx_rename_req ) + strlen( old_name ) + 1 );
    ret = GetOutPtr( 0 );
    ret->err = -DosRenameFile( old_name, new_name );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_mkdir()
{
    rfx_mkdir_ret   *ret;

    ret = GetOutPtr( 0 );
    ret->err = -DosCreateDirectory( ( char * ) GetInPtr( sizeof( rfx_mkdir_req ) ) );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_rmdir()
{
    rfx_mkdir_ret   *ret;

    ret = GetOutPtr( 0 );
    ret->err = -DosDeleteDirectory( ( char * ) GetInPtr( sizeof( rfx_rmdir_req ) ) );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_setdrive()
{
    rfx_setdrive_req    *acc;
    rfx_setdrive_ret    *ret;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    DosSetCurrentDrive( acc->drive );
    ret->err = 0;
    return( sizeof( *ret ) );
}

unsigned ReqRfx_getdrive()
{
    rfx_getdrive_ret    *ret;

    ret = GetOutPtr( 0 );
    ret->drive = DosGetCurrentDrive( );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_setcwd()
{
    rfx_setcwd_ret  *ret;

    ret = GetOutPtr( 0 );
    ret->err = -DosSetCurrentDirectory( GetInPtr( sizeof( rfx_setcwd_req ) ) );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_getcwd()
{
    rfx_getcwd_req  *acc;
    rfx_getcwd_ret  *ret;
    char            *cwd;

    acc  = GetInPtr( 0 );
    ret  = GetOutPtr( 0 );
    cwd  = GetOutPtr( sizeof( *ret ) );
    *cwd = '\0';
    ret->err = -DosGetCurrentDirectory( acc->drive, cwd );
    return( sizeof( *ret ) + 1 + strlen( cwd ) );
}

unsigned ReqRfx_setfileattr()
{
    rfx_setfileattr_req *acc;
    rfx_setfileattr_ret *ret;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    ret->err = -DosSetFileAttributes( acc->attribute, GetInPtr( sizeof( *acc ) ) );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_getfileattr()
{
    rfx_getfileattr_ret *ret;

    ret = GetOutPtr( 0 );
    ret->attribute = DosGetFileAttributes( GetInPtr( sizeof( rfx_getfileattr_req ) ) );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_getfreespace()
{
    rfx_getfreespace_req    *acc;
    rfx_getfreespace_ret    *ret;
    DRVSPACE                space;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    if( DosGetDriveFreeSpace( &space, acc->drive ) < 0 )
        ret->size = 0;
    else
        ret->size = space.FreeClusters;
    return( sizeof( *ret ) );
}

unsigned ReqRfx_setdatetime()
{
    rfx_setdatetime_req *acc;
    unsigned            num_yr_since_1970;
    unsigned            num_leap_since_1970;
    unsigned            day, month;
    unsigned            day_since_jan[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
    unsigned            timestamp, date_time;

    acc = GetInPtr( 0 );
    date_time = acc->time;
    num_yr_since_1970 = date_time / 31622400UL;
    num_leap_since_1970 = ( num_yr_since_1970 - 2 ) / 4;
    date_time -= ( ( num_leap_since_1970 * 366 +
                   ( num_yr_since_1970 - num_leap_since_1970 ) * 365 )
                   * 86400 );
    day = ( date_time / 86400 ) + 1;    // Start from Jan 1, not Jan 0
    if( ( ( num_yr_since_1970 - 2 ) % 4 ) == 0 ) {
        //leap
        if( day >= 366 ) {
            day -= 366;
            num_yr_since_1970++;
        }
    } else {
        if( day >= 365 ) {
            day -= 365;
            num_yr_since_1970++;
        }
    }
    if( ( ( num_yr_since_1970 - 2 ) % 4 ) == 0 ) {
        for( month = 2; month <= 12; ++day_since_jan[month], ++month );
    }
    timestamp = ( num_yr_since_1970 - 10 ) << 25;
    for( month = 1;( day > day_since_jan[month] && month <= 12 ); month++ )
        timestamp |= ( month << 21 );
    timestamp |= ( ( day - day_since_jan[month - 1] ) <<  16 );
    date_time %= 86400;
    timestamp |= ( ( date_time / 3600 ) << 11 );
    date_time %= 3600;
    timestamp |= ( ( date_time / 60 ) << 5 );
    timestamp |= ( ( date_time % 60 ) / 2 );
    DosSetFileTimeStamp( acc->handle, timestamp );
    return( 0 );
}

unsigned ReqRfx_getdatetime()
{
    rfx_getdatetime_req *acc;
    rfx_getdatetime_ret *ret;
    unsigned            day_since_jan[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };
    unsigned            num_yr_since_1980;
    unsigned            num_leap_since_1980;
    unsigned            sec, min, hour, day, month, year, timestamp;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    DosGetFileTimeStamp( acc->handle, &timestamp );
    //NYI: Output in local time, but not in GMT time
    sec   = ( timestamp & 0x1f ) * 2;
    min   = ( timestamp >> 5 ) & 0x3f;
    hour  = ( timestamp >> 11 ) & 0x1f;
    day   = ( timestamp >> 16 ) & 0x1f;
    month = ( timestamp >> 21 ) & 0xf;
    year  = ( timestamp >> 25 ) & 0x7f;

    //note that year 2000 is a leap year and I don't think this prog. will still
    //be around in year 2099....
    num_yr_since_1980 = year;
    num_leap_since_1980 = ( num_yr_since_1980 + 3 ) / 4;
    if( ( ( num_yr_since_1980 % 4 ) == 0 ) && ( month > 2 ) ) {
        // is leap year
        day++;
    }
    day += ( num_leap_since_1980 * 366 +
           ( num_yr_since_1980 - num_leap_since_1980 ) * 365 +
           day_since_jan[month-1] - 1 );
    ret->time = ( 315532800UL + day * 86400 + hour * 3600 + min * 60 + sec );
    return( sizeof( *ret ) );
}

unsigned ReqRfx_findfirst()
{
    rfx_findfirst_req   *acc;
    rfx_findfirst_ret   *ret;
    FIND                *find;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );
    find = GetOutPtr( sizeof( *ret ) );
    ret->err = -DosFindFirstFile( acc->attrib,
                                  ( char * ) GetInPtr( sizeof( *acc ) ), find );
    return( sizeof( *ret ) + sizeof( FIND ) );
}

unsigned ReqRfx_findnext()
{
    rfx_findnext_ret    *ret;
    FIND                *find;

    ret = GetOutPtr( 0 );
    find = GetInPtr( sizeof( rfx_findnext_req ) );
    ret->err = -DosFindNextFile( find );
    if( ret->err == 0 )
        memcpy( GetOutPtr( sizeof( *ret ) ), find, sizeof( FIND ) );
    return( sizeof( *ret ) + sizeof( FIND ) );
}

unsigned ReqRfx_findclose()
{
    return( 0 );
}

unsigned ReqRfx_nametocannonical()
{
    rfx_nametocannonical_ret    *ret;
    char                        *name;
    char                        *fullname;
    char                        *p;
    int                         drive;
    int                         level = 0;
    char                        ch;

    name = GetInPtr( sizeof( rfx_nametocannonical_req ) );
    ret = GetOutPtr( 0 );
    fullname = GetOutPtr( sizeof( *ret ) );
    ret->err = 1;
    while( *name == ' ' ) {
        name++;
    }
    if( *( name + 1 ) == ':' ) {
        drive = toupper( *name ) - 'A';
        name += 2;
    } else {
        drive = DosGetCurrentDrive();
    }
    *fullname++ = 'A' + drive;
    *fullname++ = ':';
    if( *name != '\\' ) {
        *fullname++ = '\\';
        DosGetCurrentDirectory( drive + 1, fullname );
        if( *fullname != '\0' ) {
            level++;
            while( *fullname != '\0' ) {
                if( *fullname == '\\' )
                    level++;
                fullname++;
            }
        }
    } else {
        name++;
        if( *name == '\0' )
            *fullname++ = '\\';
        *fullname = '\0';
    }
    p = name;
    for( ; ; ) {
        for( ; ; ) {
            ch = *p++;
            if( ch == '\\' )
                break;
            if( ch == '/' )
                break;
            if( ch == '\0' )
                return( sizeof( *ret ) + strlen( GetOutPtr( 0 ) ) + 1 );
        }
        if( p[0] == '.' ) {
            if( p[1] == '.' ) {
                if( level > 0 ) {
                    while( *fullname != '\\' ) {
                        fullname--;
                    }
                    level--;
                    *fullname = '\0';
                } else {
                    ret->err = 1;
                    break;
                }
            }
        } else {
            *fullname++ = '\\';
            level++;
            do {
                *fullname++ = *p++;
            } while( *p != '\0' );
            *fullname = '\0';
        }
    }
    return( sizeof( *ret ) );
}
