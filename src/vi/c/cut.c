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
#include <string.h>
#include "vi.h"
#include "keys.h"

/*
 * Cut - cut out a block of text
 */
int Cut( linenum s, int scol, linenum e, int ecol, int delflag )
{
    fcb         *sfcb, *efcb;
    line        *cline;
    int         i, rc, j;

    // bloody computers!
    ecol++;

    /*
     * get entire range
     */
    rc = GetCopyOfLineRange( s, e, &sfcb, &efcb );
    if( rc ) {
        return( rc );
    }

    /*
     * add un-deleted part of first line to work line
     */
    cline = sfcb->line_head;
    strcpy( WorkLine->data, cline->data );
    WorkLine->data[scol] = 0;

    /*
     * prune start line
     */
    sfcb->byte_cnt -= cline->len;
    for( i = scol; i <= cline->len; i++ ) {
        cline->data[i - scol] = cline->data[i];
    }
    cline->len = strlen( cline->data );
    sfcb->byte_cnt += cline->len;

    /*
     * add un-deleted part of last line to work line
     */
    cline = efcb->line_tail;
    j = strlen( WorkLine->data );
    for( i = ecol; i <= cline->len; i++ ) {
        WorkLine->data[i - ecol + j] = cline->data[i];
    }
    WorkLine->len = strlen( WorkLine->data );

    /*
     * prune last line
     */
    efcb->byte_cnt -= cline->len;
    cline->data[ecol] = 0;
    cline->len = strlen( cline->data );
    efcb->byte_cnt += cline->len;

    AddFcbsToSavebuf( sfcb, efcb, FALSE );

    /*
     * check if just yanking; if so, then go back
     */
    if( !delflag ) {
        LineYankMessage( s, e );
        return( ERR_NO_ERR );
    }

    StartUndoGroup( UndoStack );
    /*
     * set to first line
     */
    rc = SaveAndResetFilePos( s );
    if( rc ) {
        EndUndoGroup( UndoStack );
        return( rc );
    }

    /*
     * replace start line
     */
    CurrentLineReplaceUndoStart();
    ReplaceCurrentLine();
    CurrentLineReplaceUndoEnd( TRUE );
    WorkLine->len = -1;
    RestoreCurrentFilePos();

    /*
     * delete all lines but first
     */
    rc = DeleteLineRange( s + 1, e, 0 );
    if( rc ) {
        return( rc );
    }

    EndUndoGroup( UndoStack );

    return( ERR_NO_ERR );

} /* Cut */
