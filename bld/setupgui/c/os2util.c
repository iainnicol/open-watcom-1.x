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


#include <stdio.h>
#include <io.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#define INCL_DOSFILEMGR
#define INCL_DOSERRORS
#include "gui.h"
#include "setup.h"
#include "setupwpi.h"
#include "setupinf.h"


extern bool CreatePMInfo( bool uninstall )
/****************************************/
{
    char                PMProgName[ _MAX_PATH ], PMProgDesc[ MAXBUF ];
    char                PMIconFileName[ _MAX_PATH ], WorkingDir[ _MAX_PATH ];
    char                PMParams[ MAXBUF ];
    char                Cmd[ 2 * _MAX_PATH ], t1[ MAXBUF ], t2[ MAXBUF ];
    char                GroupFileName[ _MAX_PATH ];
    char                Folder[ _MAX_PATH ];
    int                 nDirIndex, icon_number;
    int                 nPMProg, nMaxPMProgs, len;
    unsigned long       dwTemp;
    char                *p;
    HOBJECT             obj;

    SimGetPMGroup( t1 );
    if( t1[ 0 ] == '\0' ) {
        return( TRUE );
    }

    SimGetPMGroupFileName( t2 );
    if( t2[ 0 ] != '\0' ) {
        sprintf( GroupFileName, "<%s>", t2 );
    } else {
        sprintf( GroupFileName, "<SETUP_FOL>" );
    }
    sprintf(Cmd, "OPEN=ICON;OBJECTID=%s;", GroupFileName );   // add more parms here if necessary

    SimGetPMGroupIcon( t2 );
    if( t2[0] != '\0' ) {
        strcat( Cmd, "ICONFILE=" );
        ReplaceVars( &Cmd[ strlen(Cmd) ], t2 );
        strcat( Cmd, ";" );
    }

    obj = WinCreateObject( "WPFolder", t1,
                           Cmd, "<WP_DESKTOP>", CO_UPDATEIFEXISTS);

    // Add the individual PM files to the Group box.
    nMaxPMProgs = SimGetNumPMProgs();
    StatusLines( STAT_CREATEPROGRAMFOLDER, "" );
    StatusAmount( 0, nMaxPMProgs );

    for( nPMProg = 0; ( obj != 0 ) && ( nPMProg < nMaxPMProgs ); nPMProg++ ) {
        StatusAmount( nPMProg, nMaxPMProgs );
        if( !SimCheckPMCondition( nPMProg ) ) {
            continue;
        }
        SimGetPMDesc( nPMProg, PMProgDesc );
        // replace '\n' in Description with LineFeed character
        for( p = PMProgDesc; *p != '\0'; ++p ) {
            if( *p == '\\' && *(p+1) == 'n' ) {
                *p = '\n';
                strcpy( p + 1, p + 2 );
                ++p;
            }
        }

        nDirIndex = SimGetPMProgName( nPMProg, PMProgName );
        if( strcmp( PMProgName, "GROUP" ) == 0 ) {
            SimGetPMParms( nPMProg, t1 );
            if( t1[ 0 ] == '\0' ) {
                return( TRUE );
            }

            if( PMProgDesc[ 0 ] != '\0' ) {
                sprintf( GroupFileName, "<%s>", t1 );
            } else {
                sprintf( GroupFileName, "<SETUP_FOL>" );
            }
            sprintf(Cmd, "OPEN=ICON;OBJECTID=%s;", GroupFileName );   // add more parms here if necessary

            SimGetPMGroupIcon( t2 );
            if( t2[0] != '\0' ) {
                strcat( Cmd, "ICONFILE=" );
                ReplaceVars( &Cmd[ strlen(Cmd) ], t2 );
                strcat( Cmd, ";" );
            }

            obj = WinCreateObject( "WPFolder", PMProgDesc,
                                   Cmd, "<WP_DESKTOP>", CO_UPDATEIFEXISTS);

        } else {
            if( nDirIndex == SIM_INIT_ERROR ) {
                WorkingDir[ 0 ] = '\0';
                ReplaceVars( t2, PMProgName );
                strcpy( PMProgName, t2 );
            } else {
                SimGetDir( nDirIndex, WorkingDir );
            }

            // get parameters
            SimGetPMParms( nPMProg, t1 );
            ReplaceVars( PMParams, t1 );
            if( PMParams[ 0 ] == '+' ) {
                // format is: +folder_name[+parameters]
                p = strchr( &PMParams[ 1 ], '+' );
                if( p == NULL ) {
                    strcpy( Folder, &PMParams[ 1 ] );
                    PMParams[ 0 ] = '\0';
                } else {
                    len = p - PMParams - 1;
                    memcpy( Folder, &PMParams[ 1 ], len );
                    Folder[ len ] = '\0';
                    ++p;
                    memmove( PMParams, p, strlen( p ) );
                }
            } else {
                // use default folder
                strcpy( Folder, GroupFileName );
            }

            // Append the subdir where the icon file is and the icon file's name.
            dwTemp = SimGetPMIconInfo( nPMProg, PMIconFileName );
            nDirIndex = (short) ( dwTemp & 0xFFFF );
            icon_number = (short) ( dwTemp >> 16 );
            if( icon_number == -1 ) icon_number = 0;
            if( nDirIndex != -1 ) {
                SimGetDir( nDirIndex, t1 );
                strcat( t1, PMIconFileName );
                strcpy( PMIconFileName, t1 );
            }

            if( PMProgName[ 0 ] == '+' ) {
                sprintf( Cmd, "SHADOWID=%s%s", WorkingDir, &PMProgName[ 1 ] );
                obj = WinCreateObject( "WPShadow", PMProgDesc,
                                   Cmd, Folder, CO_REPLACEIFEXISTS );
            } else {
                // Add the new file to the already created PM Group.
                sprintf( Cmd, "EXENAME=%s%s;PARAMETERS=%s;STARTUPDIR=%s",
                     WorkingDir, PMProgName, PMParams, WorkingDir );
                obj = WinCreateObject( "WPProgram", PMProgDesc,
                                   Cmd, Folder, CO_REPLACEIFEXISTS );
            }
            if( uninstall && obj != NULLHANDLE ) {
                // if uninstalling, have to create object to get handle
                WinDestroyObject( obj );
            }
        }
    }
    StatusAmount( nMaxPMProgs, nMaxPMProgs );
    return( TRUE );
}


static bool SetEAttr( char *filename, char const *name, char const *val )
//=======================================================================
{
    FEA2LIST            *fet;
    GEA2LIST            *get;
    EAOP2               eabuf;
    int                 ret;
    int                 len;
    char                *value;
    int                 plen;
    int                 nlen;

    plen = strlen( val );
    nlen = strlen( name );
    len = sizeof( FEA2LIST ) + nlen + plen + 4;
    fet = GUIMemAlloc( len );
    fet->cbList = len;
    fet->list[0].oNextEntryOffset = sizeof( FEA2 ) + nlen + plen + 4;
    fet->list[0].fEA = 0;
    fet->list[0].cbName = nlen;
    fet->list[0].cbValue = plen + 4;
    strcpy( fet->list[0].szName, name );
    value = &fet->list[0].szName[nlen+1];
    *((USHORT *)value)= EAT_ASCII;
    value +=2;
    *((USHORT *)value)= plen;
    value +=2;
    memcpy( value, val, plen );

    len = sizeof( GEA2LIST ) + nlen ;
    get = GUIMemAlloc( len );
    get->cbList = len;
    get->list[0].oNextEntryOffset = sizeof( GEA2 ) + nlen;
    get->list[0].cbName = nlen;
    strcpy( get->list[0].szName, name );

    eabuf.fpGEA2List = get;
    eabuf.fpFEA2List = fet;
    ret = DosSetPathInfo( filename, FIL_QUERYEASIZE, &eabuf, sizeof( eabuf ), 0 );
    GUIMemFree( fet );
    GUIMemFree( get );
    return( ret == NO_ERROR );
}


static char             dir_name[ _MAX_PATH ], label[ _MAX_PATH ], t1[ _MAX_PATH ];

void LabelDirs()
//==============

// Process [Label] section - use extended attributes to add
//                           long label to directories

{
    int                 i, num;

    num = SimNumLabels();
    for( i = 0; i < num; ++i ) {
        SimGetLabelDir( i, t1 );
        ReplaceVars( dir_name, t1 );
        SimGetLabelLabel( i, label );
        SetEAttr( dir_name, ".LONGNAME", label );
    }
}
