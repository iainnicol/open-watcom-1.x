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
* Description:  Tool bar stuff
*
****************************************************************************/


#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "winvi.h"
#include <shellapi.h>
#include "toolbr.h"
#include "keys.h"
#include "color.h"
#include "bitmap.h"

typedef struct tool_item {
    ss                  tool_head;
    UINT                id;
    HBITMAP             bmp;
    char                is_blank:1;
    char                dont_save:1;
    char                spare:6;
    char                *name;
    char                *help;
    char                cmd[1];
} tool_item;

static void             *toolBar = NULL;
static ss               *toolBarHead = NULL;
static ss               *toolBarTail = NULL;
static BOOL             fixedToolBar;
// static RECT          fixedRect;
static bool             userClose = TRUE;
static HBITMAP          buttonPattern;

RECT                    ToolBarFloatRect;

int HandleToolCommand( UINT id )
{
    ss          *p;
    tool_item   *item;
    int         len, rc;
    char        *str;

    for( p = toolBarHead; p != NULL; p = p->next ) {
        item = (tool_item *)p;
        if( item->id == id ) {
            len = strlen( item->cmd ) + 1;
            str = alloca( len );
            memcpy( str, item->cmd, len );
            rc = RunCommandLine( str );
            return( rc );
        }
    }
    return( MENU_COMMAND_NOT_HANDLED );
}
#define BORDER_X( x )           ( (x) / 4 )
#define BORDER_Y( y )           ( (y) / 8 )
#define TOOLBAR_HEIGHT( y )     ( (y) + 2 * BORDER_Y( y ) + 3 )

static void nukeButtons( void )
{
    ss          *p;
    tool_item   *tool;

    p = toolBarHead;
    while( p != NULL ) {
        tool = (tool_item *)p;
        p = p->next;
        if( tool->bmp ) {
            DeleteObject( tool->bmp );
        }
        MemFree( tool );
    }
    toolBarHead = NULL;
    toolBarTail = NULL;
}

BOOL MyToolBarProc( HWND hwnd, unsigned msg, UINT w, LONG l );
void ToolBarHelp( HWND hwnd, UINT id, BOOL isdown );

#if 0
static void newToolBarWindow( void )
{
    RECT                rect;
    POINT               tl;
    int                 height, width;
    TOOLDISPLAYINFO     dinfo;

    userClose = FALSE;

    GetWindowRect( EditContainer, &rect );
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    tl.x = rect.left;
    tl.y = 0;
    ScreenToClient( Root, &tl );

    if( fixedToolBar ) {
        // make it float
        tl.y = 0;
        height += (fixedRect.bottom - fixedRect.top)+1;
        dinfo.area = ToolBarFloatRect;
        dinfo.style = TOOLBAR_FLOAT_STYLE;
        dinfo.is_fixed = FALSE;
    } else {
//      tl.y = fixedRect.bottom + 1;
//      height -= (fixedRect.bottom - fixedRect.top)+1;
        tl.y = fixedRect.bottom;
        height -= (fixedRect.bottom - fixedRect.top);
        dinfo.area = fixedRect;
        dinfo.style = TOOLBAR_FIXED_STYLE;
        dinfo.is_fixed = TRUE;
    }
    dinfo.button_size.x = ToolBarButtonWidth;
    dinfo.button_size.y = ToolBarButtonHeight;
    dinfo.border_size.x = BORDER_X( ToolBarButtonWidth );
    dinfo.border_size.y = BORDER_Y( ToolBarButtonHeight );
    dinfo.background = buttonPattern;
    dinfo.hook = MyToolBarProc;
    dinfo.helphook = ToolBarHelp;

    ToolBarDisplay( toolBar, &dinfo );

    MoveWindow( EditContainer, tl.x, tl.y, width, height, TRUE );
    ShowWindow( ToolBarWindow( toolBar ), SW_SHOWNORMAL );
    UpdateWindow( ToolBarWindow( toolBar ) );
    fixedToolBar = !fixedToolBar;

    userClose = TRUE;

} /* newToolBarWindow */
#endif

/*
 * ToolBarHelp - update tool bar hint text
 */
void ToolBarHelp( HWND hwnd, UINT id, BOOL isdown )
{
    ss                 *p;

    hwnd = hwnd;
    SetMenuHelpString( NULL );
    if( isdown ) {
        p = toolBarHead;
        while( p != NULL ) {
            tool_item *item = (tool_item *)p;
            if( item->id == id ) {
                SetMenuHelpString( item->help );
                break;
            }
            p = p->next;
        }
    }
    UpdateStatusWindow();

} /* ToolBarHelp */

/*
 * MyToolBarProc - called by toolbar window proc
 */
BOOL MyToolBarProc( HWND hwnd, unsigned msg, UINT w, LONG l )
{
    switch( msg ) {
    case WM_KILLFOCUS:
        UnselectRegion();
        break;
    case WM_LBUTTONDBLCLK:
        // flip the current state of the toolbar - if we are fixed then start to float or vice versa
//      newToolBarWindow();
//      return( TRUE );
        break;
    case WM_MOVE:
    case WM_SIZE:
        // Whenever we are moved or sized as a floating toolbar, we
        // remember our position so that we can restore it when dbl. clicked
        if( !fixedToolBar && userClose ) {
            DefWindowProc( hwnd, msg, w, l );
            GetWindowRect( hwnd, &ToolBarFloatRect );
        }
        return( FALSE );
    case WM_DESTROY:
        if( userClose ) {
            // the user closed the toolbar so remember this
            EditFlags.Toolbar = FALSE;
        }
        break;
    }
    return( FALSE );

} /* MyToolBarProc */

/*
 * createToolBar - create the tool bar
 */
static void createToolBar( RECT *rect )
{
    int                 toolbar_height;
    TOOLDISPLAYINFO     dinfo;

    fixedToolBar = TRUE;
    dinfo.button_size.x = ToolBarButtonWidth;
    dinfo.button_size.y = ToolBarButtonHeight;
    dinfo.border_size.x = BORDER_X( ToolBarButtonWidth );
    dinfo.border_size.y = BORDER_Y( ToolBarButtonHeight );
    dinfo.style = TOOLBAR_FIXED_STYLE;
    dinfo.is_fixed = TRUE;
    toolbar_height = TOOLBAR_HEIGHT( ToolBarButtonHeight );
    dinfo.area = *rect;
    dinfo.area.bottom = ((dinfo.area.top + toolbar_height+1)&~1)-1;
    dinfo.area.top -= 1;
    dinfo.area.bottom -= 1;
    dinfo.area.left -= 1;
    dinfo.area.right += 1;
    dinfo.hook = MyToolBarProc;
    dinfo.helphook = ToolBarHelp;
    dinfo.background = LoadBitmap( InstanceHandle, "BUTTONPATTERN" );
    buttonPattern = dinfo.background;
    toolBar = ToolBarInit( Root );
#if defined (__NT__)
    ToolBarChangeSysColors( GetSysColor( COLOR_BTNFACE ),
#else
    ToolBarChangeSysColors( GetRGB( ToolBarColor ),
#endif
                            GetSysColor( COLOR_BTNHIGHLIGHT ),
                            GetSysColor( COLOR_BTNSHADOW ) );
    ToolBarDisplay( toolBar, &dinfo );
    if( toolBar != NULL ) {
        // CopyRect( &fixedRect, &dinfo.area );
        // WARNING: These are some pretty stupid arbitrary constants here
        rect->top = dinfo.area.bottom;
        ShowWindow( ToolBarWindow( toolBar ), SW_SHOWNORMAL );
        // UpdateWindow( ToolBarWindow( toolBar ) );
    }

} /* createToolBar */

/*
 * addToolBarItem - add an item to the tool bar
 */
static void addToolBarItem( tool_item *item )
{
    TOOLITEMINFO        info;

    if( item->is_blank ) {
        info.blank_space = 8;
        info.flags = ITEM_BLANK;
    } else {
        info.id = item->id;
        info.bmp = item->bmp;
        info.flags = 0;
    }
    info.depressed = FALSE;
    ToolBarAddItem( toolBar, &info );
    InvalidateRect( ToolBarWindow( toolBar ), NULL, FALSE );

} /* addToolBarItem */

/*
 * NewToolBar - create a new brand tool bar
 */
void NewToolBar( RECT *rect )
{
    ss          *curr;
    RECT         covered;

    if( toolBar ) {
        userClose = FALSE;
        CloseToolBar();
        userClose = TRUE;
    }
    if( !EditFlags.Toolbar ) {
        return;
    }
    createToolBar( rect );
    curr = toolBarHead;
    while( curr != NULL ) {            
        addToolBarItem( (tool_item *)curr );
        curr = curr->next;
    }
    UpdateToolBar( toolBar );
    covered = *rect;
    covered.bottom = rect->top;
    covered.top = 0;
    InvalidateRect( EditContainer, &covered, FALSE );

} /* NewToolBar */

/*
 * AddBitmapToToolBar - add a toolbar item ([temp], bitmap, help & command)
 */
int AddBitmapToToolBar( char *data )
{
    char                file[ _MAX_PATH ];
    char                help[ MAX_STR ];
    char                dont_save[ MAX_STR ];
    tool_item           *item;
    int                 cmd_len;
    int                 name_len;

    dont_save[0]=0;

    RemoveLeadingSpaces( data );
    if( strnicmp( data, "temp", 4 ) == 0 ) {
        /* get to the command */
        GetStringWithPossibleQuote( data, dont_save );
    }

    GetStringWithPossibleQuote( data, file );
    GetStringWithPossibleQuote( data, help );

    RemoveLeadingSpaces( data );
    cmd_len = strlen( data );
    name_len = strlen( file );
    item = MemAlloc( sizeof( tool_item ) + cmd_len + name_len
                        + strlen( help ) + 2 );
    strcpy( item->cmd, data );
    if( name_len != 0 ) {
        item->id = NextMenuId();
    } else {
        item->is_blank = TRUE;
    }
    if( strlen( dont_save ) != 0 ) {
        item->dont_save = TRUE;
    } else {
        item->dont_save = FALSE;
    }

    if( file[ 0 ] && item->cmd[ 0 ] ) {
        item->bmp = LoadBitmap( InstanceHandle, file );
        if( item->bmp == HNULL ) {
            item->bmp = ReadBitmapFile( ToolBarWindow( toolBar ), file, NULL );
        }
        item->name = &item->cmd[ cmd_len + 1 ];
        strcpy( item->name, file );
        item->help = &item->name[ name_len + 1 ];
        strcpy( item->help, help );
    } else {
        item->bmp = HNULL;
    }
    if( toolBar ) {
        addToolBarItem( item );
    }
    AddLLItemAtEnd( &toolBarHead, &toolBarTail, &item->tool_head );
    return( ERR_NO_ERR );

} /* AddBitmapToToolBar */

/*
 * DeleteFromToolBar - delete an item from the toolbar
 */
int DeleteFromToolBar( char *data )
{
    char        buffer[ MAX_STR ];
    int         index;
    ss         *p;

    NextWord1( data, buffer );
    index = atoi( buffer );
    // index should be (base 1) index of tool in list
    if( index > 0 ) {
        p = toolBarHead;
        while( p != NULL ) {
            index -= 1;
            if( index == 0 ) break;
            p = p->next;
        }
        if( p ) {
            tool_item *item = (tool_item *)p;
            ToolBarDeleteItem( toolBar, item->id );
            DeleteLLItem( &toolBarHead, &toolBarTail, p );
            if( item->bmp != NULL ) {
                DeleteObject( item->bmp );
            }
            return( ERR_NO_ERR );
        }
    }
    return( ERR_INVALID_MENU );
}

/*
 * CloseToolBar - make the toolbar go away.
 */
void CloseToolBar( void )
{
    if( toolBar != NULL ) {
        DeleteObject( buttonPattern );
        ToolBarFini( toolBar );
        toolBar = NULL;
    }

} /* CloseToolBar */

/*
 * DestroyToolBar - make the toolbar go away and destroy all buttons.
 */
void DestroyToolBar( void )
{
    if( toolBar != NULL ) {
        CloseToolBar();
    }
    nukeButtons();

} /* DestroyToolBar */

/*
 * GetToolbarWindow - return the current toolbar window
 */
HWND GetToolbarWindow( void )
{
    return( ToolBarWindow( toolBar ) );

} /* GetToolbarWindow */

/*
 * BarfToolBarData - output toolbar data to config file
 */
void BarfToolBarData( FILE *f )
{
    ss          *p;
    tool_item   *citem;

    p = toolBarHead;
    while( p != NULL ) {
        citem = (tool_item *)p;
        if( citem->dont_save ) {
            /* do nothing */
        } else if( citem->is_blank ) {
            MyFprintf( f, "addtoolbaritem\n" );
        } else {
            MyFprintf( f, "addtoolbaritem %s \"%s\" %s\n", citem->name,
                            citem->help, citem->cmd );
        }
        p = p->next;
    }

} /* BarfToolBarData */
