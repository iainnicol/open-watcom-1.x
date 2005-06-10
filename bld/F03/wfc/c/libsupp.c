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


//
// LIBSUPP   : Library support
//

#include "ftnstd.h"
#include "sdfile.h"
#include "global.h"
#include "omodes.h"
#include "inout.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

extern  file_handle     SDOpen(char *,int);
extern  char            *SDSrcExtn(char *);
extern  int             MakeName(char *,char *,char *);
extern  int             CopyMaxStr(char *,char *,int);
extern  void            SrcInclude(char *,file_handle );

extern  char            ForExtn[];

static  char            LibEnvStr[] = { "FINCLUDE" };


static  file_handle FindSrcFile( char *fname ) {
//=============================================

// Find a source file.

    file_handle  fp;

    MakeName( fname, SDSrcExtn( fname ), fname );
    fp = SDOpen( fname, READ_FILE );
    if( fp != NULL ) {
        SrcInclude( fname, fp );
    }
    return( fp );
}


static  file_handle SearchDir( char *path, char *name ) {
//======================================================

// Search a directory for a source file.

    char        fname[MAX_FILE+1];

    fname[ Combine( path, name, fname, MAX_FILE ) ] = NULLCHAR;
    return( FindSrcFile( fname ) );
}


static  bool    ExtractName( char **lib ) {
//=========================================

// Extract a file name from library specification.

    char        *ptr;
    bool        last;

    ptr = *lib;
    for(;;) {
        if( *ptr == NULLCHAR ) {
            last = TRUE;
            break;
        }
        if( *ptr == ';' ) {
            last = FALSE;
            break;
        }
       ptr++;
    }
    *lib = ptr;
    for(;;) {
        ptr--;
        if( *ptr != ' ' ) break;
    }
    ptr++;
    *ptr = NULLCHAR;
    return( last );
}


static file_handle SearchPath( char *path, char *name ) {
//======================================================

    char        *ptr;
    file_handle fp;
    bool        last;

    fp = NULL;
    ptr = alloca( strlen( path ) + sizeof( char ) );
    if( ptr != NULL ) {
        strcpy( ptr, path );
        for(;;) {
            path = ptr;
            last = ExtractName( &ptr );
            fp = SearchDir( path, name );
            if( fp != NULL ) break;
            if( last ) break;
            ptr++; // skip the ';'
        }
    }
    return( fp );
}


file_handle      IncSearch( char *name ) {
//=======================================

// Search for a library member.

    file_handle fp;
    char        *path;

    fp = NULL;
    if( IncludePath != NULL ) {
        fp = SearchPath( IncludePath, name );
        if( fp != NULL ) return( fp );
    }
    path = getenv( LibEnvStr );
    if( path != NULL ) {
        fp = SearchPath( path, name );
    }
    return( fp );
}




static  int     Combine( char *path, char *name, char *buff, int buff_len ) {
//===========================================================================

// Combine the path and filename.

    int         len;

    len = CopyMaxStr( path, buff, buff_len );
    if( ( buff[ len - 1 ] != ':' ) && ( buff[ len - 1 ] != '\\' ) &&
        ( buff[ len - 1 ] != '/' ) ) {
        buff[ len ] = '\\';
        ++len;
        buff[ len ] = NULLCHAR;
    }
    len += CopyMaxStr( name, buff + len, buff_len - len );
    return( len );
}
