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


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <ctype.h>
#include "vi.h"
#include "keys.h"
#include "source.h"
#include "win.h"
#ifdef __WIN__
#include "winrtns.h"
#endif

static event *nextEvent( void )
{
    LastEvent = GetNextEvent( TRUE );
    return( &EventList[ LastEvent ] );
}

static void defaultRange( range *range )
{
    range->start.line = CurrentLineNumber;
    range->start.column = CurrentColumn;
    range->end.line = CurrentLineNumber;
    range->end.column = CurrentColumn;
    range->line_based = FALSE;
    /*
     * we don't fill in hi_start and hi-end - assume that if a routine
     * is going to modify range->highlight then it had better set those
     * other values to something as well.
     */
    range->highlight = FALSE;
    range->fix_range = FALSE;

} /* defaultRange */

/*
 * doOperator - process an operator event
 */
static int doOperator( event *ev )
{
    event       *next;
    int         rc;
    long        count;
    range       range;
    int         next_type;
    bool        is_op_alias;

    rc = ERR_INVALID_OP;
    defaultRange( &range );
    count = GetRepeatCount();
    is_op_alias = ev->b.is_op_alias;
    if( is_op_alias ) {
        ev->rtn.alias( &ev, &next );
    } else {
        next = nextEvent();
        // a count is the only thing allowed to interfere between an op and
        // its argument so we just keep chewing...
        if( next != &EventList[ '0' ] ) {
            while( next->b.is_number ) {
                if( EditFlags.Modeless ) {
                    next->alt_rtn.old();
                } else {
                    next->rtn.old();
                }
                next = nextEvent();
            }
        }
        count *= GetRepeatCount();
    }
    KillRepeatWindow();
    if( EditFlags.Modeless ) {
        range.fix_range = next->alt_b.fix_range;
        next_type = next->alt_b.type;
    } else {
        range.fix_range = next->b.fix_range;
        next_type = next->b.type;
    }
    EditFlags.OperatorWantsMove = TRUE; // was: if( count==1 )
    if( next_type == EVENT_OP ) {
        // op/op only valid when ops are equal
        if( next == ev ) {
            rc = GetLineRange( &range, count, CurrentLineNumber );
        }
    } else {
        // it had better be a move operation
        if( next_type == EVENT_REL_MOVE || next_type == EVENT_ABS_MOVE ) {
            /*
             * Kluge! want 'ce' instead of 'cw' - this sucks.
             *
             * - even better kludge: if we are currently on white
             *   space, then treat 'cw' as 'cw'. arrrrr. cge.
             */
            if( (ev == &EventList[ 'c' ] || ev == &EventList[ VI_KEY(ALT_F1) ]) &&
                        LastEvent == 'w' ) {
                EditFlags.IsChangeWord = TRUE;
                if( CurrentLine != NULL ) {
                    if( !isspace( CurrentLine->data[CurrentColumn-1] ) ) {
                        next = &EventList[ 'e' ];
                        range.fix_range = FALSE;
                    }
                }
            }
            if( EditFlags.Modeless ) {
                rc = next->alt_rtn.move( &range, count );
            } else {
                rc = next->rtn.move( &range, count );
            }
            EditFlags.IsChangeWord = FALSE;
        } else {
            /*
             * Kluge! treat 'r' as a movement command.
             */
            if( LastEvent == 'r' ) {
                rc = GetSelectedRegion( &range );
            } else if( LastEvent == '0' ) {
                rc = MoveLineBegin( &range, 1 );
            } else if( LastEvent == VI_KEY( ESC ) ) {
                rc = RANGE_REQUEST_CANCELLED;
            }
        }
    }
    EditFlags.OperatorWantsMove = FALSE;
    if( rc == ERR_NO_ERR ) {
        if( ev->b.modifies ) {
            rc = ModificationTest();
        }
        if( rc == ERR_NO_ERR ) {
            NormalizeRange( &range );
            if( EditFlags.Modeless ) {
                rc = ev->alt_rtn.op( &range );
            } else {
                rc = ev->rtn.op( &range );
            }
        }
    }
    return( rc );

} /* doOperator */

/*
 * DoMove - handle a movement command
 */
int DoMove( event *ev )
{
    range       range;
    int         rc;
    int         curcol;
    int         type;

    defaultRange( &range );
    if( EditFlags.Modeless ) {
        rc = ev->alt_rtn.move( &range, GetRepeatCount() );
        type = ev->alt_b.type;
    } else {
        rc = ev->rtn.move( &range, GetRepeatCount() );
        type = ev->b.type;
    }
    if( rc == ERR_NO_ERR ) {
        curcol = CurrentColumn;
        if( range.start.line != CurrentLineNumber ) {
            if( type == EVENT_REL_MOVE ) {
                GoToLineRelCurs( range.start.line );
            } else {
                curcol = -1;
                MemorizeCurrentContext();
                GoToLineNoRelCurs( range.start.line );
            }
        }
        if( curcol != range.start.column ) {
            GoToColumnOK( range.start.column );
        }
#ifndef __WIN__
        if( range.highlight ) {
            // don't handle multi-line highlights yet
            assert( range.hi_start.line == range.hi_end.line );
            EditFlags.ResetDisplayLine = TRUE;
            DCUpdate();
            HiliteAColumnRange( range.hi_start.line,
                range.hi_start.column, range.hi_end.column );
        }
#endif
    }
    return( rc );
}

static void ensureCursorDisplayed( void )
{
    int         len, wc, diff;

    if( ( EditFlags.Modeless == TRUE ) && ( CurrentFile != NULL ) ) {
        len = WindowAuxInfo( CurrentWindow, WIND_INFO_TEXT_LINES );
        if( CurrentLineNumber < TopOfPage ||
            CurrentLineNumber > TopOfPage + len - 1 ) {
                SetCurrentLine( CurrentLineNumber );
        }

        wc = VirtualCursorPosition() - LeftColumn;
        if( !ColumnInWindow( wc, &diff ) ) {
            SetCurrentColumn( CurrentColumn );
        }
    }
}

/*
 * DoLastEvent - process the last keystroke event
 */
int DoLastEvent( void )
{
    event       *event;
    int         rc;
    bool        keep_sel;

    if( LastEvent >= EventCount ) {
        return( InvalidKey() );
    } else {
        if( !EditFlags.InsertModeActive || EditFlags.Modeless ) {
            if( !EditFlags.Modeless && KeyMaps[LastEvent].data != NULL ) {
                if( !KeyMaps[LastEvent].inuse ) {
                    return( DoKeyMap( LastEvent ) );
                }
            }
            event = &EventList[ LastEvent ];
            keep_sel = event->b.keep_selection;
            if( event->b.keep_selection_maybe ) {
                if( SelRgn.selected ) {
                    keep_sel = TRUE;
                }
            }
            if( !keep_sel && !EditFlags.ScrollCommand ) {
                UnselectRegion();
            }
            if( EditFlags.ScrollCommand == FALSE ) {
                ensureCursorDisplayed();
            }
            switch( event->b.type ) {
            case EVENT_INS:
                if( EditFlags.Modeless ) {
                    /* don't allow following cursor movements to affect seln
                     */
                    keep_sel = SelRgn.selected;
                    DeleteSelectedRegion();
                    SelRgn.selected = keep_sel;
                    InsertLikeLast();
                    rc = event->rtn.ins();
                    DoneCurrentInsert( FALSE );
                    SelRgn.selected = FALSE;
                } else {
                    if( !EditFlags.InsertModeActive ) {
                        InsertLikeLast();
                    }
                    rc = event->rtn.ins();
                }
                break;
            case EVENT_OP:
                DoneCurrentInsert( TRUE );
                rc = doOperator( event );
                break;
            case EVENT_REL_MOVE:
            case EVENT_ABS_MOVE:
                DoneCurrentInsert( TRUE );
                rc = DoMove( event );
                break;
            case EVENT_MISC:
                DoneCurrentInsert( TRUE );
                rc = event->rtn.old();
                break;
            }
            return( rc );
        } else {
//          UnselectRegion();
            if( EditFlags.EscapedInsertChar ) {
                return( IMChar() );
            } else {
                if( InputKeyMaps[LastEvent].data != NULL ) {
                    if( !InputKeyMaps[LastEvent].inuse ) {
                        return( StartInputKeyMap( LastEvent ) );
                    }
                }
                return( (EventList[LastEvent].ins)() );
            }
        }
    }

} /* DoLastEvent */

/*
 * DoneLastEvent - finished with the last event
 */
void DoneLastEvent( int rc, bool is_dotmode )
{
    if( !EditFlags.InsertModeActive ) {
        /*
         * save last command for '.'
         */
        if( !is_dotmode ) {
            if( EditFlags.DotMode ) {
                EditFlags.DotMode = FALSE;
            } else if( EditFlags.Dotable && !EditFlags.MemorizeMode ) {
                SaveDotCmd();
            }
        }

        /*
         * reset number and and buffer number
         */
        if( rc != GOT_A_SAVEBUF ) {
            if( rc != GOT_A_DIGIT ) {
                /* repeat count should not reset save buf */
                SavebufNumber = NO_SAVEBUF;
                DoneRepeat();
            }
        }

        if( !is_dotmode ) {
            EditFlags.Dotable = FALSE;
        }
    }

} /* DoneLastEvent */

/*
 * EditMain - main driver for editor (command mode)
 */
void EditMain( void )
{
    int         rc;
    char        *msg;
    bool        doclear;

    /*
     * loop forever, or at least until all done
     */
    while( TRUE ) {

    #if 0
    #ifdef __WIN__
        PushMode();
        UpdateFiles();
        PopMode();
    #endif
    #endif
        if( !EditFlags.InsertModeActive || EditFlags.Modeless ) {
            if( EditFlags.Modeless ) {
                UpdateEditStatus();
                EditFlags.NoCapsLock = FALSE;
            } else {
                UpdateCurrentStatus( CSTATUS_COMMAND );
                EditFlags.NoCapsLock = TRUE;
            }

            if( !EditFlags.Modeless && EditFlags.ReturnToInsertMode &&
                                !NonKeyboardEventsPending() ) {
                EditFlags.ReturnToInsertMode = FALSE;
                if( EditFlags.WasOverstrike ) {
                    LastEvent = 'R';
                } else {
                    LastEvent = 'i';
                }
            } else {
                DCUpdateAll();
                #ifdef __WIN__
                    SetWindowCursorForReal();
                #endif
                LastEvent = GetNextEvent( TRUE );
            }
            EditFlags.NoCapsLock = FALSE;
            doclear = TRUE;
            if( LastEvent == VI_KEY( MOUSEEVENT ) ) {
                if( LastMouseEvent == MOUSE_MOVE ) {
                    doclear = FALSE;
                }
            }
            if( doclear ) {
                if( EditFlags.AutoMessageClear ) {
                    ClearWindow( MessageWindow );
                }
                #ifndef __WIN__
                    ResetDisplayLine();
                #endif
            }
        } else {
            // Cannot do a RestoreInfo while we are in insert mode
            // because it will call ValidateCurrentColumn which will
            // do something stupid on us... PushMode/PopMode solution
            // not working yet... this needs a little work
            DCUpdate();
            #ifdef __WIN__
                SetWindowCursorForReal();
            #endif
            LastEvent = GetNextEvent( TRUE );
        }

        rc = DoLastEvent();

        if( EditFlags.ReadOnlyError && rc <= 0 ) {
            EditFlags.ReadOnlyError = FALSE;
            rc = ERR_READ_ONLY_FILE_MODIFIED;
        }
        if( rc > 0 ) {
            msg = GetErrorMsg( rc );
        }

        DoneLastEvent( rc, FALSE );

        if( rc > 0 ) {
            Error( msg );
        }

    }

} /* EditMain */

/*
 * AbsoluteNullResponse - give no response
 */
int AbsoluteNullResponse( void )
{
    return( ERR_NO_ERR );
}

/*
 * NullResponse - give null response for keystroke
 */
int NullResponse( void )
{
    if( !EditFlags.EscapeMessage ) {
        ClearWindow( MessageWindow );
    } else {
        DisplayFileStatus();
    }
    UnselectRegion();
    return( ERR_NO_ERR );

} /* NullResponse */

static window_id        repeatWindow = (window_id)-1;

/*
 * KillRepeatWindow - just like it says
 */
void KillRepeatWindow( void )
{
    if( repeatWindow != NO_WINDOW ) {
        CloseAWindow( repeatWindow );
        repeatWindow = NO_WINDOW;
    }
}

/*
 * DoneRepeat - done getting repeat count
 */
void DoneRepeat( void )
{
    RepeatDigits=0;
    if( !EditFlags.MemorizeMode ) {
        DotDigits = 0;
    }
    KillRepeatWindow();

} /* DoneRepeat */

/*
 * SetRepeatCount - set up a fake repeat count
 */
void SetRepeatCount( long num )
{
    char        str[MAX_NUM_STR];

    ltoa( num, str, 10 );
    strcpy( RepeatString, str );
    RepeatDigits = strlen( str );

} /* SetRepeatCount */

/*
 * GetRepeatCount - return repeat count and reset it
 */
long GetRepeatCount( void )
{
    long        i;

    if( RepeatDigits == 0 ) {
        NoRepeatInfo = TRUE;
        return( 1L );
    }
    i = atol( RepeatString );
    RepeatDigits = 0;
    NoRepeatInfo = FALSE;
    return( i );

} /* GetRepeatCount */

#ifndef __WIN__
#define UpdateRepeatString( str ) DisplayLineInWindow( repeatWindow, 1, str )
#else
extern void UpdateRepeatString( char *str );
#endif

/*
 * DoDigit - process a digit typed in
 */
int DoDigit( void )
{
    int i;

    if( LastEvent == '0' && RepeatDigits == 0 ) {
        LeftColumn = 0;
        GoToColumnOK( 1 );
        DCDisplayAllLines();
        return( ERR_NO_ERR );
    }

    if( RepeatDigits == MAX_REPEAT_STRING-1 ) {
        DoneRepeat();
        return( ERR_REPEAT_STRING_TOO_LONG );
    }

    if( repeatWindow == (window_id)-1 && EditFlags.RepeatInfo ) {
        i = NewWindow2( &repeatWindow, &repcntw_info );
        if( i ) {
            DoneRepeat();
            return( i );
        }
        WindowTitle( repeatWindow, "Repeat Count" );
    }

    RepeatString[RepeatDigits++] = LastEvent;
    RepeatString[RepeatDigits] = 0;
    if( repeatWindow != (window_id)-1 ) {
        UpdateRepeatString( RepeatString );
    }
    return( GOT_A_DIGIT );

} /* DoDigit */

/*
 * InvalidKey - process invalid keystroke
 */
int InvalidKey( void )
{
    Error( GetErrorMsg( ERR_INVALID_KEY ), LastEvent );
    return( DO_NOT_CLEAR_MESSAGE_WINDOW );

} /* InvalidKey */

/*
 * Modified - set file modified flag
 */
void Modified( bool f )
{
    if( f ) {
        CurrentFile->need_autosave = TRUE;
        if( EditFlags.ReadOnlyCheck ) {
            if( CFileReadOnly() ) {
                EditFlags.ReadOnlyError = TRUE;
            }
        }
    }
    if( CurrentFile->modified != f  ) {
        CurrentFile->modified = f;
        SetModifiedVar( f );
    }
    UnselectRegion();

} /* Modified */

/*
 * ResetDisplayLine - reset display line, if required (after hilight)
 */
void ResetDisplayLine( void )
{
    if( EditFlags.ResetDisplayLine ) {
        memcpy( WorkLine->data, CurrentLine->data, CurrentLine->len+1 );
        WorkLine->len = CurrentLine->len;
        DisplayWorkLine( FALSE );
        DCUpdate();
        WorkLine->len = -1;
        EditFlags.ResetDisplayLine = FALSE;
    }

} /* ResetDisplayLine */