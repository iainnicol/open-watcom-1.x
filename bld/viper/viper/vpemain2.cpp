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


extern "C" {
    #include <io.h>
    #include "rcdefs.h"
    #include "stdlib.h"
    #include "banner.h"
};

#include "vpemain.hpp"
#include "vmsglog.hpp"

#include "wwinmain.hpp"
#include "wmenu.hpp"
#include "wfiledlg.hpp"
#include "wmsgdlg.hpp"
#include "winpdlg.hpp"
#include "wpickdlg.hpp"
#include "wautodlg.hpp"
#include "weditdlg.hpp"
#include "wfilenam.hpp"
#include "wobjfile.hpp"
#include "wstrlist.hpp"
#include "wserver.hpp"
#include "wclient.hpp"
#include "wprocess.hpp"
#include "mconfig.hpp"

#include "vcompon.hpp"
#include "mcompon.hpp"
#include "maction.hpp"
#include "mtarget.hpp"
#include "mtoolitm.hpp"
#include "vcompdlg.hpp"

#include "wabout.hpp"
#include "mcommand.hpp"
#include "wmetrics.hpp"
#include "wsystem.hpp"

#include "wstatwin.hpp"
#include "wflashp.hpp"
#include "vhelpstk.hpp"
#include "veditdlg.hpp"
#include "ide.h"
#include "mitem.hpp"

#include "inifile.hpp"

#define IDE_INI_IDENTIFIER      "WATCOM_IDE_0"
#define IDE_INI_TOOLBAR         "toolbar"
#define IDE_INI_STATWND         "statuswnd"
#define IDE_INI_AUTOREFRESH     "refresh"
#define IDE_INI_EDITOR          "editor"
#define IDE_INI_EDITOR_ISDLL    "dll_editor"
#define IDE_INI_EDITOR_PARMS    "editor_parms"
#define IDE_INI_FILENAME        "ideinit.cfg"
#define IDE_INI_DIR             "binw"
#define IDE_INI_HEIGHT          "height"
#define IDE_INI_WIDTH           "width"
#define IDE_INI_X               "x_coord"
#define IDE_INI_Y               "y_coord"
#define MAX_CMD_LINE            256

extern char _viperTitle[];
extern char _viperError[];
extern char _viperRequest[];
extern char _viperInfo[];

void VpeMain::cForPBProject( WFileName &pj, bool nt ) {

    WString     mask( "wp6d" );

    if( nt ) {
        mask = "np2d";
    }
#ifdef __NT__
    mask.concat( 'n' );
#else
    mask.concat( 'w' );
#endif
    if( _project == NULL || _project->filename() != pj && okToClear() ) {
        clearProject();
        // eventually access should be provided by WCLASS
        if( !access( pj, F_OK ) ) {
            loadProject( pj );
        } else {
            _project = new MProject( pj );
            attachModel( _project );
            WFileName targname( pj );
            targname.setExt( ".dll" );
            MRule *rule = _config->findMatchingRule( targname, mask );
            MComponent* mcomp = new MComponent( _project, rule, mask, targname );
            _project->addComponent( mcomp );
            VComponent* vcomp = new VComponent( this, mcomp, vCompStyle() );
            _compViews.add( vcomp );
            mcomp->updateItemList();
        }
    }
    // update targets
    if( _project != NULL ) {
        unsigned        cnt;
        MComponent      *mcomp;

        cnt = _project->components().count();
        for( ; cnt > 0; cnt -- ) {
            mcomp = (MComponent *)(_project->components()[ cnt - 1 ] );
            mcomp->updateItemList();
        }
    }
}

static void splitCommand( const char *cmd, WString &targ, WString &file ) {
    unsigned    i;
    unsigned    targ_end;

    while( isspace( *cmd ) ) cmd++;
    i = 0;
    targ = cmd;
    while( !isspace( targ[i] ) && targ[i] != '\0' ) i++;
    targ_end = i;
    while( isspace( targ[i] ) ) i++;
    file = targ.gets() + i;
    targ.truncate( targ_end );
}

void VpeMain::remoteFileOp( const char *cmd ) {
    WFileName   targ;
    WFileName   file;
    WFileName   fn;
    VComponent  *comp;
    unsigned    i;

    splitCommand( cmd + 2, targ, file );
    i = _compViews.count();
    while( i > 0 ) {
        comp = (VComponent *)_compViews[ i-1 ];
        comp->component()->filename().noExt( fn );
        if( fn == targ ) {
            if( cmd[0] == 'f' ) {
                switch( cmd[1] ) {
                case 'b':
                    comp->beginFileList( MITEM_OWNER_WINMAKER );
                    break;
                case 'a':
                    comp->markFile( file, MITEM_OWNER_WINMAKER );
                    break;
                case 'e':
                    comp->endFileList( MITEM_OWNER_WINMAKER );
                    break;
                }
            }
        }
        i--;
    }
}

WString* VpeMain::DdeCallback( const char* c ) {

    WFileName   fn( c );

    switch( c[0] ) {
    case 'f':
        if( _refuseFileLists ) {
            return( new WString( "err" ) );
        } else {
            remoteFileOp( c );
            return( new WString( "ok" ) );
        }
    case 'p':
        if( c[1] == 'b' ) {
            WFileName   fn( c + 2 );
            show();
            cForPBProject( fn, FALSE );
            return( new WString( "ok" ) );
        } else if( c[1] == 'n' ) {
            WFileName   fn( c + 2 );
            show();
            cForPBProject( fn, TRUE );
            return( new WString( "ok" ) );
        }
        break;
    case 'v':
        if( c[1] == 'e' ) {
            // do nothing
        }
        break;
    case 'z':
        if( c[1] == '0' ) {
            show();
            setFocus();
        }
        break;
    }
    return( NULL );
}

void VpeMain::readIdeInit()
{
    char buff[_MAX_PATH];
    int width, height, x, y;

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_TOOLBAR, "1", buff, _MAX_PATH );
    if( buff[0] == '0' ) {
        delete clearToolBar();
        _toolBarActive = FALSE;
    }

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_STATWND, "1", buff, _MAX_PATH );
    if( buff[0] == '0' ) {
        deleteStatusBar();
    }

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_AUTOREFRESH, "1", buff, _MAX_PATH );
    if( buff[0] == '0' ) {
        _autoRefresh = FALSE;
    } else {
        _autoRefresh = TRUE;
    }
    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_EDITOR, (const char*)_config->editor(),
                        buff, _MAX_PATH );
    _editor = buff;

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_EDITOR_ISDLL,
                        _config->editorIsDLL() ? "1" : "0",
                        buff, _MAX_PATH );
    if( buff[0] == '0' ) {
        _editorIsDll = FALSE;
    } else {
        _editorIsDll = TRUE;
    }

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_EDITOR_PARMS, "%f", buff, _MAX_PATH );
    _editorParms = buff;

    for( int i=0; i<4; i++ ) {
        itoa( i+1, buff, 10 );
        MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                buff, "*", buff, _MAX_PATH ); // if we get "*", doesn't exist
        if( buff[0] != '*' ) {
            _oldProjects.add( new WFileName( buff ) );
        }
    }
    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_HEIGHT, "0", buff, _MAX_PATH );
    height = atoi( buff );

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_WIDTH, "0", buff, _MAX_PATH );
    width = atoi( buff );

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_X, "0", buff, _MAX_PATH );
    x = atoi( buff );

    MyGetProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                        IDE_INI_Y, "0", buff, _MAX_PATH );
    y = atoi( buff );

    WRect sc;
    WSystemMetrics::screenCoordinates( sc );
    if( width == 0 ) width = sc.w() * 3/4;
    if( height == 0 ) height = sc.h() * 9/10;

    sc.w( width );
    sc.h( height );
    sc.x( x );
    sc.y( y );
    move( sc );
}

void writeEditor( WFile &ifile, char *edtext, char *isdlltext,
                        WFileName &editor, bool isdll, bool thisos ) {
    // the WFileName class has no != operator
    if( ( !thisos && !( editor == "" ) )
        || ( thisos && !( editor == _config->editor() ) )
        || ( thisos && isdll != _config->editorIsDLL() ) ) {
        ifile.printf( "%s=%s\n", edtext, editor.gets() );
        ifile.printf( "%s=%d\n", isdlltext, isdll == TRUE );
    }
}

bool VpeMain::reallyClose()
{
    WRect rect;
    show( WWinStateShowNormal );
    if( _quitAnyways || okToQuit() ) {
        startWait();
        clearProject();
        stopWait();
        _winMakerClient.ShutDown();
        // write out .INI file stuff
        char buff[_MAX_PATH];
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_EDITOR, (char*)_editor.gets() );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_EDITOR_ISDLL, _editorIsDll ? "1" : "0" );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_EDITOR_PARMS, _editorParms.gets() );
        for( int i=0; i<_oldProjects.count(); i++ ) {
            itoa( i+1, buff, 10 );
            MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                buff, (const char*)*((WFileName*)_oldProjects[i]) );
        }
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_TOOLBAR, _toolBarActive ? "1" : "0" );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_STATWND, (_statusBar != NULL) ? "1" : "0" );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_AUTOREFRESH, _autoRefresh ? "1" : "0" );
        getRectangle( rect );
        itoa( rect.w(), buff, 10 );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_WIDTH, buff );
        itoa( rect.h(), buff, 10 );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_HEIGHT, buff );
        itoa( rect.x(), buff, 10 );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_X, buff );
        itoa( rect.y(), buff, 10 );
        MyWriteProfileString( IDE_INI_DIR, IDE_INI_FILENAME, IDE_INI_IDENTIFIER,
                              IDE_INI_Y, buff );
        if( _otherhelp != NULL ) {
            delete _otherhelp;
            _otherhelp = NULL;
        }
        delete _help;
        _help = NULL;
        return( TRUE );
    }
    return( FALSE );
}

bool VpeMain::executeCommand( const char* c, int location, const char* title )
{
    if( c && strlen( c ) > 0 ) {
        WString* cur = NULL;
        WStringList opts;
        for( int i=0; c[i]!= '\0'; i++ ) {
            if( cur ) {
                if( c[i] == '"' ) {
                    opts.add( cur );
                    cur = NULL;
                } else {
                    cur->concat( c[i] );
                }
            } else if( c[i] == '$' && c[i+1] == '"' ) {
                i++;
                cur = new WString();
            }
        }
        delete cur;
        cur = NULL;
        WStringList reps;
        if( opts.count() > 0 ) {
            WString dTitle( title );
            if( dTitle.size() == 0 ) dTitle = "AutoDialog";
            WAutoDialog prompts( this, dTitle, opts );
            if( !prompts.getInput( reps ) ) {
                setStatus( NULL );
                return( FALSE );
            }
        }
        WString cmd;
        int j = 0;
        for( i=0; c[i]!= '\0'; i++ ) {
            if( !cur ) {
                if( c[i] == '$' && c[i+1] == '"' ) {
                    i++;
                    cur = &reps.stringAt( j );
                    j++;
                } else {
                    cmd.concat( c[i] );
                }
            } else if( c[i] == '"' ) {
                cmd.concat( *cur );
                cur = NULL;
            }
        }
        startWait();
        switch( location ) {
            case EXECUTE_NORMAL: {
                setStatus( "Executing..." );
                execute( cmd );
                break;
            }
            case EXECUTE_BATCH: {
                runBatch( cmd );
                break;
            }
            case EXECUTE_MAKE: {
                if( makeMake() ) {
                    runBatch( cmd );
                }
                break;
            }
            case EXECUTE_BROWSE: {
                executeBrowse( cmd );
                break;
            }
            case EXECUTE_EDITOR: {
                executeEditor( cmd );
                break;
            }
            case EXECUTE_TOUCH_ALL: {
                MsgRetType      rc;
                unsigned        i;
                VComponent      *comp;
                rc = WMessageDialog::messagef( this, MsgQuestion, MsgYesNo,
                        _viperRequest,
                        "Do you really want to remake all targets and their components?" );
                if( rc == MsgRetYes ) {
                    i = _compViews.count();
                    while( i > 0 ) {
                        comp = (VComponent *)_compViews[ i-1 ];
                        comp->touchComponent( TRUE );
                        i--;
                    }
                }
                break;
            }
            case EXECUTE_HELP: {
                if( _otherhelp == NULL ) {
                    delete _otherhelp;
                }
                _otherhelp = new WSystemHelp( this, "", cmd );
                _otherhelp->sysHelpContent();
                break;
            }
            case EXECUTE_WINMAKER: {
                if( _winMakerClient.Run( cmd ) ) {
                    WMessageDialog::messagef( this, MsgError, MsgOk,
                        _viperError, "Unable to run or connect to Visual Programmer.");
                }
                break;
            }
        }
        stopWait();
        setStatus( NULL );
        if( _quitAnyways ) {
            exit( NULL );
        }
    }
    return( TRUE );
}

bool VpeMain::execute( const WString& cmd )
{
    if( _config->debug() && !confirm( "Starting '%s'", cmd ) ) {
        return( FALSE );
    }
    startWait();

    int icount = strlen( cmd );
    for( int i=0; i<icount; ) {
        WString cbuff;
        while( isspace( cmd[i] ) ) i++;
        for( ;i<icount; ) {
            char ch = cmd[i];
            i++;
            if( ch == '\n' || ch == '\r' ) break;
            cbuff.concat( ch );
        }
        if( cbuff.size() > 0 ) {
            if( strnicmp( cbuff, "!Error ", 7 ) == 0 ) {
                WString msg;
                for( int i=7; i<cbuff.size() && cbuff[i] != '$'; i++ ) {
                    msg.concat( cbuff[i] );
                }
                WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, msg );
                return( FALSE );
            } else {
                if( !executeOne( cbuff ) ) {
                    return( FALSE );
                }
            }
        }
    }
    return( TRUE );
}

bool VpeMain::executeOne( const WString& cmd )
{
    int i = 0;
    WWindowState wstate = WWinStateShowNormal;
    WWindowType wtype = WWinTypeDefault;
    if( strnicmp( cmd, "!FullScreen ", 12 ) == 0 ) {
        i += 12;
        wtype = WWinTypeFullScreen;
    } else if( strnicmp( cmd, "!Windowed ", 10 ) == 0 ) {
        i += 10;
        wtype = WWinTypeWindowed;
    } else if( strnicmp( cmd, "!Hidden ", 8 ) == 0 ) {
        i += 10;
        wstate = WWinStateHide;
    }
    int ret = WSystemService::sysExec( &cmd[i], wstate, wtype );
    stopWait();

#ifdef __OS2__
    if( ret == -1 ) {

        // this is a kludge because the WMessageDialog can only handle
        // finitely long strings
        WString         cmdmsg;
        cmdmsg = cmd;
        cmdmsg.truncate( MAX_CMD_LINE );

        //
        // WARNING - this may stop working if WCLASS modifies errno
        //
        WMessageDialog::messagef( this, MsgError, MsgOk, _viperError,
                                "Unable to run %s: %s.",
                                (const char*)cmdmsg, strerror( errno ) );
        return( FALSE );
    }
#endif

#if defined( __WINDOWS__ ) || defined ( __NT__ )
    if( ret <= 32 ) {

        // this is a kludge because the WMessageDialog can only handle
        // finitely long strings
        WString         cmdmsg;
        cmdmsg = cmd;
        cmdmsg.truncate( MAX_CMD_LINE );

        switch( ret ) {
        case 0:
            WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, "%s: Out of memory.", (const char*)cmdmsg );
            break;
        case 2:
            WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, "%s: Program or one of its components not found.", (const char*)cmdmsg );
            break;
        case 3:
            WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, "%s: Path not found.", (const char*)cmdmsg );
            break;
        case 16:
            WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, "%s: Contains multiple writeable data segments.", (const char*)cmdmsg );
            break;
        default:
            WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, "%s: return code=%d.", (const char*)cmdmsg, ret );
        }
        return( FALSE );
    }
#endif
    return( TRUE );
}

void VpeMain::executeEditor( const WString& cmd )
{
    if( _config->debug() && !confirm( "executeEditor: '%s'", cmd ) ) {
        return;
    }
    setStatus( "Executing editor..." );
    WStringList x( cmd );
    if( _editorIsDll ) {
        if( _editorDll.isInitialized() ) {      //internal-use DLL
            if( x.stringAt(0) == "EditSaveAll" ) {
                // don't start a new editor up if one is not already there
                _editorDll.EDITSaveAll();
            } else if( _editorDll.EDITConnect() ) {
                if( x.stringAt(0) == "EditFile" ) {
                    char* file = (char*)(const char*)x.stringAt( 1 );
                    char* help = (char*)(const char*)x.stringAt( 2 );
                    if( _editorDll.EDITFile( file, help ) ) {
                        _editorDll.EDITShowWindow( EDIT_SHOWNORMAL );
                    } else {
                        WMessageDialog::messagef( this, MsgError, MsgOk,
                                    _viperInfo, "Unable to start editor" );
                    }
                } else if( x.stringAt( 0 ) == "EditLocate" ) {
                    long lRow = atol( x.stringAt( 1 ) );
                    int nCol = atoi( x.stringAt( 2 ) );
                    int len = atoi( x.stringAt( 3 ) );
                    _editorDll.EDITLocate( lRow, nCol, len );
                    _editorDll.EDITShowWindow( EDIT_SHOWNORMAL );
                } else if( x.stringAt( 0 ) == "EditLocateError" ) {
                    long lRow = atol( x.stringAt( 1 ) );
                    int nCol = atoi( x.stringAt( 2 ) );
                    int len = atoi( x.stringAt( 3 ) );
                    int resId = atoi( x.stringAt( 4 ) );
                    char* msg = (char*)(const char*)x.stringAt( 5 );
                    _editorDll.EDITLocateError( lRow, nCol, len, resId, msg );
                    _editorDll.EDITShowWindow( EDIT_SHOWNORMAL );
                } else if( x.stringAt(0) == "EditFileAtPos" ) {
                    char* file = (char*)(const char*)x.stringAt( 1 );
                    file += 2; // for "-f" before filename
                    long lRow = atol( x.stringAt( 2 ) );
                    int nCol = atoi( x.stringAt( 3 ) );
                    int len = atoi( x.stringAt( 4 ) );
                    int resId = atoi( x.stringAt( 5 ) );
                    char* msg = (char*)(const char*)x.stringAt( 6 );
                    char* help = (char*)(const char*)x.stringAt( 7 );
                    if( _editorDll.EDITFile( file, help ) ) {
                        _editorDll.EDITShowWindow( EDIT_SHOWNORMAL );
                        _editorDll.EDITLocateError( lRow, nCol, len, resId, msg );
                        _editorDll.EDITShowWindow( EDIT_SHOWNORMAL );
                    } else {
                        WMessageDialog::messagef( this, MsgError, MsgOk,
                                    _viperInfo, "Unable to start editor" );
                    }
                } else if( x.stringAt(0) == "TakeFocus" ) {
                    _editorDll.EDITShowWindow( EDIT_SHOWNORMAL );
                }
            } else {
                WMessageDialog::messagef( this, MsgError, MsgOk, _viperInfo,
                                          "Unable to connect to editor" );
            }
        } else {
            WMessageDialog::messagef( this, MsgError, MsgOk, _viperInfo,
                                        "Editor not available" );
        }
    } else if( x.stringAt(0) == "EditFile" ) {
        WString bat( _editor );
        bat.concat( ' ' );
        bat.concat( x.cStringAt(1) );
        execute( bat );
    } else if( x.stringAt(0) == "EditFileAtPos" ) {
        WString bat( _editor );
        bat.concat( ' ' ); // space after editor name before parms
        int parmsize = _editorParms.size();

        for( int i=0; i < parmsize; i++ ) {
            switch( _editorParms[i] ) {
            case '%':
                switch( _editorParms[i+1] ) {
                case 'f': // file name
                    // string contains "-f<filename>" so strip the -f
                    bat.concat( (char*)(const char*)x.stringAt( 1 )+2 );
                    break;
                case 'r': // row to go to
                    bat.concat( x.stringAt( 2 ) );
                    break;
                case 'c': // column to go to
                    bat.concat( x.stringAt( 3 ) );
                    break;
                case 'l': // length of hilight
                    bat.concat( x.stringAt( 4 ) );
                    break;
                case 'h': // helpid
                    bat.concat( x.stringAt( 5 ) );
                    break;
                case 'e': // error message
                    bat.concat( x.stringAt( 6 ) );
                    break;
                case '%': // a real '%'
                    bat.concat( x.stringAt( '%' ) );
                    break;
                default:
                    // ignore the '%' and the character
                    break;
                }
                i+=2; // skip % and following char
            default:
                bat.concat( _editorParms[i] );
                break;
            }
        }
        execute( bat );
    }
}

bool VpeMain::makeMake()
{
    WString     editcmd( "EditSaveAll" );
    MsgRetType  ret;

    if( !running() ) {
        if( checkProject() ) {
            executeEditor( editcmd );
            ret = MsgRetYes;
            if( _winMakerClient.GenerateCode() ) {
                ret = WMessageDialog::messagef( this, MsgError, MsgYesNo,
                                        _viperError,
                                        "Unable refresh Visual Programmer Files\n"
                                        "Do you want to continue the build?" );
            }
            if( ret == MsgRetYes ) {
                setStatus( "Creating MAKE file(s)..." );
                if( _project->makeMakeFile() ) {
                    return( TRUE );
                }
                WMessageDialog::messagef( this, MsgError, MsgOk, _viperError,
                                          "Unable to create makefile(s)" );
                return( FALSE );
            }
        }
        return( FALSE );
    }
    WMessageDialog::messagef( this, MsgError, MsgOk, _viperError, "Makefile in use" );
    return( FALSE );
}

