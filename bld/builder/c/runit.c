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
* Description:  Built-in builder commands.
*
****************************************************************************/


#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef __UNIX__
#include <unistd.h>
#include <dirent.h>
#else
#include <direct.h>
#include <dos.h>
#endif
#if defined(__WATCOMC__) || !defined(__UNIX__)
#include <env.h>
#endif
#include "watcom.h"
#include "builder.h"

#define BSIZE   256
#define SCREEN  79
const char Equals[] =   "========================================"\
                        "========================================";

extern bool Quiet;

#ifdef __UNIX__

int __fnmatch(const char *pattern, const char *string) {

    if( *string == 0 ) {
        while( *pattern == '*' ) ++pattern;
        return(( *pattern == 0 ) ? 1 : 0 );
    }
    switch( *pattern ) {
    case '*':
        if( *string == '.' ) {
            return( __fnmatch( pattern + 1, string ));
        } else if( __fnmatch( pattern + 1, string )) {
            return( 1 );
        } else {
            return( __fnmatch( pattern, string + 1 ));
        }
    case '?':
        if(( *string == 0 ) || ( *string == '.' )) {
            return( 0 );
        } else {
            return( __fnmatch( pattern + 1, string + 1 ));
        }
    case 0:
        return( *string == 0 );
    default:
        if( *pattern != *string ) {
            return( 0 );
        } else {
            return( __fnmatch( pattern + 1, string + 1 ));
        }
    }
}

#endif

static void LogDir( char *dir )
{
    char        tbuff[BSIZE];
    int         equals;
    int         bufflen;
    const char  *eq;
    struct tm   *tm;
    time_t      ttime;

    ttime = time( NULL );
    tm = localtime( &ttime );
    strftime( tbuff, BSIZE, "%H:%M:%S", tm );
    strcat( tbuff, " " );
    strcat( tbuff, dir );
    equals = ( SCREEN - ( bufflen = strlen( tbuff ) ) ) / 2 - 2;
    if( equals < 0 ) equals = 0;
    eq = &Equals[ (sizeof( Equals )-1) - equals ];
    Log( FALSE, "%s %s %s%s\n", eq, tbuff, eq, ( bufflen & 1 ) ? "" : "=" );
}

static unsigned ProcSet( char *cmd )
{
    char        *var;
    char        *rep;
    var = cmd;
    rep = strchr( cmd, '=' );
    if( rep == NULL ) return( 1 );
    *rep++ = '\0';
    if( *rep == '\0' ) {
        rep = NULL;             // get rid of the variable! Needed by Optima!
    }
    return( setenv( var, rep, 1 ) );
}

void ResetArchives( copy_entry *list )
{
    copy_entry  *next;
#ifndef __UNIX__
    unsigned    attr;
#endif

    while( list != NULL ) {
        next = list->next;
#ifndef __UNIX__
        if( _dos_getfileattr( list->src, &attr ) == 0 ) {
            _dos_setfileattr( list->src, attr & ~_A_ARCH );
        }
#endif
        free( list );
        list = next;
    }
}

static copy_entry *BuildList( char *src, char *dst, bool test_abit )
{
    copy_entry  *head;
    copy_entry  *curr;
    copy_entry  **owner;
    char        *end;
    char        buff[_MAX_PATH2];
    char        full[_MAX_PATH];
    char        srcdir[_MAX_PATH];
    char        *drive;
    char        *dir;
    char        *fn;
    char        *ext;
    DIR                 *directory;
    struct dirent       *dent;
#ifndef __UNIX__
    FILE        *fp;
    unsigned    attr;
#else
    char        pattern[_MAX_PATH];
#endif

    strcpy( srcdir, src );
    end = &dst[strlen(dst)-1];
    while( end[0] == ' ' || end[0] == '\t' ) {
        --end;
    }
    end[1] = '\0';
    if( strchr( srcdir, '*' ) == NULL && strchr( srcdir, '?' ) == NULL ) {
        /* no wild cards */
        head = Alloc( sizeof( *head ) );
        head->next = NULL;
        _fullpath( head->src, srcdir, sizeof( head->src ) );
        switch( *end ) {
        case '\\':
        case '/':
            /* need to append source file name */
            _splitpath2( srcdir, buff, &drive, &dir, &fn, &ext );
            _makepath( full, NULL, dst, fn, ext );
            _fullpath( head->dst, full, sizeof( head->dst ) );
            break;
        default:
            _fullpath( head->dst, dst, sizeof( head->dst ) );
            break;
        }
#ifndef __UNIX__
        if( test_abit ) {
            fp = fopen( head->dst, "rb" );
            if( fp != NULL ) fclose( fp );
            _dos_getfileattr( head->src, &attr );
            if( !(attr & _A_ARCH) && fp != NULL ) {
                /* file hasn't changed */
                free( head );
                head = NULL;
            }
        }
#endif
        return( head );
    }
#ifdef __UNIX__
    _splitpath2( srcdir, buff, &drive, &dir, &fn, &ext );
    _makepath( srcdir, drive, dir, NULL, NULL );
    _makepath( pattern, NULL, NULL, fn, ext );
#endif
    directory = opendir( srcdir );
    if( directory == NULL ) {
        Log( FALSE, "Can not open source directory '%s': %s\n", srcdir, strerror( errno ) );
        return( NULL );
    }
    head = NULL;
    owner = &head;
    for( ;; ) {
        dent = readdir( directory );
        if( dent == NULL ) break;
#ifdef __UNIX__
        {
            struct stat buf;
            size_t len = strlen( srcdir );

            if( __fnmatch(pattern, dent->d_name) == 0 )
                continue;

            strcat( srcdir, dent->d_name );
            stat( srcdir, &buf );
            srcdir[len] = '\0';
            if ( S_ISDIR( buf.st_mode ) )
                continue;
        }
#else
        if( dent->d_attr & (_A_SUBDIR|_A_VOLID) )
            continue;
#endif
        curr = Alloc( sizeof( *curr ) );
        curr->next = NULL;
        _splitpath2( srcdir, buff, &drive, &dir, &fn, &ext );
        _makepath( full, drive, dir, dent->d_name, NULL );
        _fullpath( curr->src, full, sizeof( curr->src ) );
        strcpy( full, dst );
        switch( *end ) {
        case '\\':
        case '/':
            strcat( full, dent->d_name );
            break;
        }
        _fullpath( curr->dst, full, sizeof( curr->dst ) );
#ifndef __UNIX__
        if( test_abit ) {
            fp = fopen( curr->dst, "rb" );
            if( fp != NULL ) fclose( fp );
            if( !(dent->d_attr & _A_ARCH) && fp != NULL ) {
                /* file hasn't changed */
                free( curr );
                continue;
            }
        }
#endif
        *owner = curr;
        owner = &curr->next;
    }
    return( head );
}

static unsigned ProcOneCopy( char *src, char *dst )
{
    FILE        *sp;
    FILE        *dp;
    unsigned    len;
    unsigned    out;
    static char buff[32U*1024];

    sp = fopen( src, "rb" );
    if( sp == NULL ) {
        Log( FALSE, "Can not open '%s' for reading: %s\n", src, strerror( errno ) );
        return( 1 );
    }
    dp = fopen( dst, "wb" );
    if( dp == NULL ) {
        Log( FALSE, "Can not open '%s' for writing: %s\n", dst, strerror( errno ) );
        fclose( sp );
        return( 1 );
    }
    Log( FALSE, "Copying '%s' to '%s'...\n", src, dst );
    for( ;; ) {
        len = fread( buff, 1, sizeof( buff ), sp );
        if( len == 0 ) break;
        if( ferror( sp ) ) {
            Log( FALSE, "Error reading '%s': %s\n", src, strerror( errno ) );
            fclose( sp );
            fclose( dp );
            return( 1 );
        }
        out = fwrite( buff, 1, len, dp );
        if( ferror( dp ) ) {
            Log( FALSE, "Error writing '%s': %s\n", dst, strerror( errno ) );
            fclose( sp );
            fclose( dp );
            return( 1 );
        }
        if( out != len ) {
            Log( FALSE, "Error writing '%s': Disk full\n", dst );
            fclose( sp );
            fclose( dp );
            return( 1 );
        }
    }
    /* set the date back? */
    fclose( sp );
    fclose( dp );
#ifdef __UNIX__
    {
        /* copy permissions: mostly necessary for the "x" bit */
        struct stat buf;
        stat( src, &buf );
        // some files is copied from the source tree with the read-only permission
        // for next run we need the write permission for the current user as minimum
        chmod( dst, buf.st_mode | S_IWUSR );
    }
#endif
    return( 0 );
}

static unsigned ProcCopy( char *cmd, bool test_abit )
{
    char        *src;
    char        *dst;
    copy_entry  *list;
    copy_entry  *next;
    unsigned    res;

    src = cmd;
    dst = strchr( src, ' ' );
    if( dst == NULL ) {
        dst = strchr( src, '\t' );
        if( dst == NULL ) {
            Log( FALSE, "Missing destination parameter\n" );
            return( 1 );
        }
    }
    *dst = '\0';
    dst = SkipBlanks( dst + 1 );
    if( *dst == '\0' ) {
        Log( FALSE, "Missing destination parameter\n" );
        return( 1 );
    }
    list = BuildList( src, dst, test_abit );
    for( ;; ) {
        if( list == NULL ) break;
        res = ProcOneCopy( list->src, list->dst );
        if( res != 0 ) {
            while( list != NULL ) {
                next = list->next;
                free( list );
                list = next;
            }
            return( res );
        }
        next = list->next;
        if( test_abit ) {
            list->next = IncludeStk->reset_abit;
            IncludeStk->reset_abit = list;
        } else {
            free( list );
        }
        list = next;
    }
    return( 0 );
}

#ifndef __UNIX__
static unsigned ProcMkdir( char *cmd )
{
    struct stat sb;

    if ( -1 == stat( cmd, &sb ) )
        return( mkdir( cmd ) );
    else
        return( 0 );
}
#endif

#if 0
void PMakeOutput( char *str )
{
    Log( FALSE, "%s\n", str );
}

static unsigned DoPMake( pmake_data *data )
{
    pmake_list  *curr;
    unsigned    res;
    char        cmd[256];

    for( curr = data->dir_list; curr != NULL; curr = curr->next ) {
        res = SysChdir( curr->dir_name );
        if( res != 0 ) return( res );
        getcwd( IncludeStk->cwd, sizeof( IncludeStk->cwd ) );
        if( data->display ) LogDir( IncludeStk->cwd );
        PMakeCommand( data, cmd );
        res = SysRunCommand( cmd );
        if( res != 0 ) return( res );
    }
    return( 0 );
}

static unsigned ProcPMake( char *cmd )
{
    pmake_data  *data;
    unsigned    res;
    char        save[_MAX_PATH];

    data = PMakeBuild( cmd );
    if( data == NULL ) return( 1 );
    if( data->want_help || data->signaled ) {
        PMakeCleanup( data );
        return( 2 );
    }
    strcpy( save, IncludeStk->cwd );
    res = DoPMake( data );
    SysChdir( save );
    getcwd( IncludeStk->cwd, sizeof( IncludeStk->cwd ) );
    PMakeCleanup( data );
    return( res );
}
#endif

unsigned RunIt( char *cmd )
{
    unsigned    res;

    #define BUILTIN( b )        \
        (memicmp( cmd, b, sizeof( b ) - 1 ) == 0 && cmd[sizeof(b)-1] == ' ')
    res = 0;
    if( BUILTIN( "CD" ) ) {
        res = SysChdir( SkipBlanks( cmd + sizeof( "CD" ) ) );
        if( res == 0 ) {
            getcwd( IncludeStk->cwd, sizeof( IncludeStk->cwd ) ) ;
        }
    } else if( BUILTIN( "CDSAY" ) ) {
        res = SysChdir( SkipBlanks( cmd + sizeof( "CDSAY" ) ) );
        if( res == 0 ) {
            getcwd( IncludeStk->cwd, sizeof( IncludeStk->cwd ) );
            LogDir( IncludeStk->cwd );
        }
    } else if( BUILTIN( "SET" ) ) {
        res = ProcSet( SkipBlanks( cmd + sizeof( "SET" ) ) );
    } else if( BUILTIN( "ECHO" ) ) {
        Log( Quiet, "%s\n", SkipBlanks( cmd + sizeof( "ECHO" ) ) );
    } else if( BUILTIN( "COPY" ) ) {
        res = ProcCopy( SkipBlanks( cmd + sizeof( "COPY" ) ), FALSE );
    } else if( BUILTIN( "ACOPY" ) ) {
        res = ProcCopy( SkipBlanks( cmd + sizeof( "ACOPY" ) ), TRUE );
#ifndef __UNIX__
    } else if( BUILTIN( "MKDIR" ) ) {
        res = ProcMkdir( SkipBlanks( cmd + sizeof( "MKDIR" ) ) );
#endif
#if 0
    } else if( BUILTIN( "PMAKE" ) ) {
        res = ProcPMake( SkipBlanks( cmd + sizeof( "PMAKE" ) ) );
#endif
    } else {
        res = SysRunCommand( cmd );
    }
    return( res );
}
