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
* Description:  Undo command processing.
*
****************************************************************************/


#include "vi.h"

/*
 * StartUndoGroupWithPosition - begin set of undos, save start position
 */
void StartUndoGroupWithPosition( undo_stack *stack, linenum lne,
                                 linenum top, int col )
{
    undo        *cundo;

    if( !EditFlags.Undo || stack == NULL ) {
        return;
    }

    cundo = UndoAlloc( stack, START_UNDO_GROUP );

    if( cundo == NULL ) {
        stack->OpenUndo++;
        return;
    }

    /*
     * check if there is an undo group in progress
     */
    if( stack->current >= 0 && stack->OpenUndo > 0 ) {
        stack->OpenUndo++;
        AddUndoToCurrent( cundo, stack );
        cundo->data.sdata.depth = stack->OpenUndo;
        return;
    }

    /*
     * no group active, make this the head group
     */
    stack->OpenUndo = 1;
    if( cundo == NULL ) {
        return;
    }
    cundo->data.sdata.depth = 1;
    cundo->data.sdata.p.line = lne;
    cundo->data.sdata.top = top;
    cundo->data.sdata.time_stamp = ClockTicks;
    if( col == 0 ) {
        col = 1;
    }
    cundo->data.sdata.p.column = col;
    PushUndoStack( cundo, stack );

    /*
     * check if we are adding something to the undo stack, and
     * if this is NOT during an undo operation.  If so, then we
     * cannot do an undo-undo, since there have been text changes
     */
    if( stack == UndoStack && !EditFlags.UndoInProg ) {
        PurgeUndoStack( UndoUndoStack );
    }

} /* StartUndoGroupWithPosition */

/*
 * UndoReplaceLines - undo the replacement of a group of lines
 */
int UndoReplaceLines( linenum sline, linenum eline  )
{
    int i;
    fcb *head, *tail;

    if( !EditFlags.Undo || UndoStack == NULL ) {
        return( ERR_NO_ERR );
    }
    i = GetCopyOfLineRange( sline, eline, &head, &tail );
    if( i ) {
        return( i );
    }
    StartUndoGroup( UndoStack );
    UndoDeleteFcbs( sline - 1, head, tail, UndoStack );
    UndoInsert( sline, eline, UndoStack );
    EndUndoGroup( UndoStack );
    return( ERR_NO_ERR );

} /* UndoReplaceLines */

/*
 * numberLines - give fcbs a line number sequence
 */
static void numberLines( fcb *cfcb, linenum sline )
{
    linenum     tot;

    while( cfcb != NULL ) {
        tot = cfcb->end_line - cfcb->start_line;
        cfcb->start_line = sline;
        cfcb->end_line = sline + tot;
        sline += tot + 1;
        cfcb = cfcb->next;
    }

} /* numberLines */

/*
 * UndoDeleteFcbs - set up transaction to undo the deletion of fcbs
 */
void UndoDeleteFcbs( linenum sline, fcb *fcbhead, fcb *fcbtail,
                     undo_stack *stack  )
{
    undo        *cundo;

    /*
     * set up undo entry
     */
    if( stack == NULL || stack->current < 0 || !EditFlags.Undo ) {
        return;
    }
    cundo = UndoAlloc( stack, UNDO_DELETE_FCBS );
    if( cundo == NULL ) {
        return;
    }
    AddUndoToCurrent( cundo, stack );

    /*
     * set up start line in fcb head
     */
    numberLines( fcbhead, sline );

    /*
     * save the data
     */
    cundo->data.fcbs.fcb_head = fcbhead;
    cundo->data.fcbs.fcb_tail = fcbtail;

} /* UndoDeleteFcbs */

/*
 * UndoInsert - set up stuff to undo the insert of a set of lines
 */
void UndoInsert( linenum sline, linenum eline , undo_stack *stack )
{
    undo        *top, *cundo;
    bool        neednew = FALSE;

    if( stack == NULL || stack->current < 0 || !EditFlags.Undo ) {
        return;
    }

    /*
     * check if we need a new entry; ie, if this line number
     * is not part of the current sequence, allocate a new entry
     */
    top = stack->stack[stack->current];
    if( top->type != UNDO_INSERT_LINES ) {
        neednew = TRUE;
    } else if( top->data.del_range.end != sline - 1 ) {
        neednew = TRUE;
    } else if( top->data.del_range.end == sline ) {
        return;
    }

    /*
     * if we need a new delete range, allocate it; otherwise,
     * just increment the previous one by one
     */
    if( neednew ) {
        cundo = UndoAlloc( stack, UNDO_INSERT_LINES );
        if( cundo == NULL ) {
            return;
        }
        AddUndoToCurrent( cundo, stack );
        cundo->data.del_range.start = sline;
        cundo->data.del_range.end = eline;
    } else {
        top->data.del_range.end = eline;
    }

} /* UndoInsert */

/*
 * PatchDeleteUndo - go and patch together undo deletes
 */
void PatchDeleteUndo( undo_stack *stack )
{
    undo        *top, *next, *del, *topdel, *after, *tmp;
    bool        merge;
    int         i;
    fcb         *cfcb, *nfcb;

    /*
     * see if we can merge this with the last undo record
     * (provided we are in an open undo group)
     *
     * we need the following undo sequence, after the first one:
     * END_UNDO_GROUP
     * UNDO_DELETE_FCBS
     *      - must have same start line as the first one
     * START_UNDO_GROUP
     */
    if( stack == NULL || stack->OpenUndo <= 0 || stack->current < 0 ||
        !EditFlags.Undo ) {
        return;
    }
    top = stack->stack[stack->current];
    topdel = top->next;
    next = top->next->next->next;   /* go past first delete group */
    if( next == NULL || next->type != END_UNDO_GROUP ) {
        return;
    }
    next = next->next;
    if( next == NULL || next->type != UNDO_DELETE_FCBS ) {
        return;
    }
    del = next;
    next = next->next;
    if( next == NULL || next->type != START_UNDO_GROUP ) {
        return;
    }
    after = next->next;

    /*
     * if two starts are the same, then these are back-to-back deletes
     * and we can merge them.
     */
    merge = FALSE;
    if( del->data.fcbs.fcb_head->start_line == topdel->data.fcbs.fcb_head->start_line ) {
        merge = TRUE;
    }

    /*
     * merge data two records together
     */
    if( merge ) {
        /*
         * join fcbs from the two undo records: the fcbs
         * from the 2nd record become the head fcbs, and
         * the fcbs from the 2nd record follow them.
         */
        del->data.fcbs.fcb_tail->next = topdel->data.fcbs.fcb_head;
        topdel->data.fcbs.fcb_head->prev = del->data.fcbs.fcb_tail;
        topdel->data.fcbs.fcb_head = del->data.fcbs.fcb_head;
        numberLines( topdel->data.fcbs.fcb_head, topdel->data.fcbs.fcb_head->start_line );

        /*
         * join the top undo sequence with the third one
         */
        next = top->next->next->next;   /* go past first delete group */
        top->next->next->next = after;  /* join first undo group to third */

        /*
         * delete the END_UNDO_GROUP, UNDO_DELETE_FCBS,
         * and START_UNDO_GROUP records for the 2nd entry
         */
        tmp = next->next;
        MemFree( next );
        next = tmp;
        tmp = next->next;
        MemFree( next );
        MemFree( tmp );

        /*
         * merge the line data from the fcbs together
         */
        cfcb = topdel->data.fcbs.fcb_head;
        while( cfcb != NULL ) {

            nfcb = cfcb->next;
            if( nfcb == NULL ) {
                break;
            }
            if( !cfcb->in_memory || !nfcb->in_memory ) {
                    cfcb = nfcb;
                    continue;
            }
            i = JoinFcbs( cfcb, nfcb );
            if( i == COULD_NOT_MERGE_FCBS ) {
                cfcb = nfcb;
            } else {
                DeleteLLItem( (ss **)&(topdel->data.fcbs.fcb_head),
                              (ss **)&(topdel->data.fcbs.fcb_tail), (ss *)nfcb );
                FcbFree( nfcb );
            }
        }

    }

} /* PatchDeleteUndo */

/*
 * StartUndoGroup - begin set of undos
 */
void StartUndoGroup( undo_stack *us  )
{
    StartUndoGroupWithPosition( us, CurrentPos.line, LeftTopPos.line, CurrentPos.column );

} /* StartUndoGroup */

/*
 * EndUndoGroup - end set of undos
 */
void EndUndoGroup( undo_stack *stack )
{
    undo        *cundo;
    int         done;

    if( stack == NULL || !EditFlags.Undo ) {
        return;
    }
    if( stack->current < 0 ) {
        if( EditFlags.UndoLost ) {
            stack->OpenUndo--;
            if( stack->OpenUndo == 0 ) {
                EditFlags.UndoLost = FALSE;
            }
        }
        return;
    }
    cundo = UndoAlloc( stack, END_UNDO_GROUP );

    /*
     * decrement the open count and add element
     */
    stack->OpenUndo--;
    if( cundo == NULL ) {
        if( stack->OpenUndo == 0 ) {
            EditFlags.UndoLost = FALSE;
        }
        return;
    }
    AddUndoToCurrent( cundo, stack );

    /*
     * if we have just closed a group, make sure there is something
     * to do; if not, take this item off.  this gets rid of all those
     * annoying undo events created for something that didn't modify
     * the file
     */
    if( stack->OpenUndo == 0 ) {
        done = FALSE;
        while( !done ) {
            switch( cundo->type ) {
            case START_UNDO_GROUP:
            case END_UNDO_GROUP:
                break;
            default:
                done = TRUE;
            }
            cundo = cundo->next;
            if( cundo == NULL ) {
                break;
            }
        }
        if( !done ) {
            cundo = PopUndoStack( stack );
            UndoFree( cundo, FALSE );
        }
    }

} /* EndUndoGroup */

/*
 * TryEndUndoGroup - try to end undo group in last specified stack
 */
void TryEndUndoGroup( undo_stack *cstack )
{
    info        *cinfo;

    cinfo = InfoHead;
    while( cinfo != NULL ) {
        if( cstack == cinfo->UndoStack ) {
            EndUndoGroup( cstack );
            break;
        }
        cinfo = cinfo->next;
    }

} /* TryEndUndoGroup */
