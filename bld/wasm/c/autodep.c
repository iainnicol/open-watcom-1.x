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
* Description:  Autodependency functions
*
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <sys/stat.h>
#include <time.h>

#include "autodep.h"
#include "asmalloc.h"
#include "bool.h"
#include "watcom.h"

FNAMEPTR FNames = NULL;

enum
{
    TIME_SEC_B  = 0,
    TIME_MIN_B  = 5,
    TIME_HOUR_B = 11,
};

enum
{
    DATE_DAY_B  = 0,
    DATE_MON_B  = 5,
    DATE_YEAR_B = 9,
};

char *FilenameFullPath( char *buff, char const *name, size_t max )
{
    char        *p;

    p = _fullpath( buff, name, max );
    if( p == NULL )
        p = (char *)name;

#ifdef __UNIX__
    if( (p[0] == '/' && p[1] == '/') && (name[0] != '/' || name[1] != '/') ) {
        //
        // if the _fullpath result has a node number and
        // the user didn't specify one, strip the node number
        // off before returning
        //
        p += 2;
        while( *(p++) != '/' ) ;
    }
#endif
    return( p );
}

int SrcFileTime( char const *filename, time_t *mtime )
{
    struct stat statbuf;
#if !defined(__UNIX__)
    struct tm *    ltime;
    unsigned short dos_date;
    unsigned short dos_time;
#endif

    if( stat( filename, &statbuf ) != 0 ) {
        *mtime = 0;
        return( -1 );
    }
    *mtime = statbuf.st_mtime;
#if !defined(__UNIX__)
    // convert time_t to DOS date/time format and put back into time_t
    ltime = localtime( mtime);
    dos_date = (( ltime->tm_year - 80 ) << DATE_YEAR_B )
             | (( ltime->tm_mon + 1 ) << DATE_MON_B )
             | (( ltime->tm_mday ) << DATE_DAY_B );
    dos_time = (( ltime->tm_hour ) << TIME_HOUR_B )
             | (( ltime->tm_min ) << TIME_MIN_B )
             | (( ltime->tm_sec / 2 ) << TIME_SEC_B );
    *mtime = dos_time | ( dos_date << 16 );
#endif
    return( 0 );
}

void AddFlist( char const *filename )
{
    FNAMEPTR    flist;
    FNAMEPTR    last;
    int         index;
    char        *fname;
    char        buff[2*_MAX_PATH];
        
    index = 0;
    last = FNames;
    for( flist = last; flist != NULL; flist = flist->next ) {
        if( strcmp( filename, flist->name ) == 0 ) return;
        index++;
        last = flist;
    }
    fname = FilenameFullPath( buff, filename, sizeof(buff) );
    flist = (FNAMEPTR)AsmAlloc( sizeof( FNAME ) );
    flist->name = (char*)AsmAlloc( strlen( fname ) + 1 );
    strcpy( flist->name, fname );
    SrcFileTime( fname, &flist->mtime );
    flist->next = NULL;
    if( FNames == NULL ) {
        FNames = flist;
    } else {
        last->next = flist;
    }
    return;
}
