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
* Description:  CDSAY command used in the build process.
*
****************************************************************************/


#include <string.h>
#include <ctype.h>
#include <time.h>
#include <direct.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>

#define BSIZE   256
#define SCREEN  79
const char Equals[] =   "========================================"\
                        "========================================";

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
    printf("%s %s %s%s\n", eq, tbuff, eq, ( bufflen & 1 ) ? "" : "=" );
}

unsigned ChgDir( char *dir )
{
    char        *end;
    unsigned    len;
    unsigned    total;

    if( dir[0] == '\0' ) return( 0 );
    len = strlen( dir );
    end = &dir[len-1];
    switch( *end ) {
    case '\\':
    case '/':
        if( end > dir && end[-1] != ':' ) {
            *end = '\0';
            --len;
        }
        break;
    }
    if( len > 2 && dir[1] == ':' ) {
        _dos_setdrive( toupper( dir[0] ) - 'A' + 1, &total );
    }
    return( chdir( dir ) );
}

int main(int argc, char **argv)
{
    int    res = 0;
    char   cwd[_MAX_PATH];

    if (argc > 1) {
        res = ChgDir( argv[1] );
    }
    if( res == 0 ) {
        getcwd( cwd, sizeof( cwd ) );
        LogDir( strupr(cwd) );
    }
    else {
        printf("Error! CDSAY: invalid directory\n");
    }
    return res;
}
