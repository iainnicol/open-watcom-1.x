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
#include "vi.h"

/*
 * SplitFcbAtLine - split a fcb at specified line (specified line goes in
 *                  new one) - line 1 causes new fcb to be created at start
 */
int SplitFcbAtLine( linenum lne, file *f, fcb *fb )
{
    linenum     sline;
    int         bytecnt = 0;
    line        *cl, *pl;
    fcb         *cfcb;

    /*
     * if at start line or end line + 1, no splitting possible
     */
    if( lne == fb->start_line ) {
        return( NO_SPLIT_CREATED_AT_START_LINE );
    }
    if( lne == fb->end_line + 1 ) {
        return( NO_SPLIT_CREATED_AT_END_LINE );
    }

    /*
     * check if we tried to split at line that is not in fcb;
     */
    if( lne > fb->end_line ) {
        return( ERR_NO_SUCH_LINE );
    }

    /*
     * get fcb to split, and make sure that it isn't swapped while
     * we use it
     */
    FetchFcb( fb );
    fb->non_swappable = TRUE;

    /*
     * get position
     */
    sline = fb->start_line;
    cl = fb->line_head;
    while( sline != lne ) {
        bytecnt += cl->len + 1;
        cl = cl->next;
        sline++;
    }

    /*
     * add the new fcb
     */
    pl = cl->prev;
    cfcb = FcbAlloc( f );
    InsertLLItemAfter( (ss **)&(f->fcb_tail), (ss *)fb, (ss *)cfcb );

    /*
     * reset line data for new fcb
     */
    cfcb->start_line = lne;
    cfcb->end_line = fb->end_line;
    cfcb->line_head = cl;
    cfcb->line_head->prev = NULL;
    cfcb->line_tail = fb->line_tail;
    cfcb->byte_cnt = fb->byte_cnt - bytecnt;

    /*
     * reset line data for original fcb
     */
    fb->end_line = lne - 1;
    fb->line_tail = pl;
    fb->line_tail->next = NULL;
    fb->byte_cnt = bytecnt;

    /*
     * check for locked fcb
     */
    if( fb->globalmatch ) {
        /*
         * make sure original one should stay locked
         */
        fb->globalmatch = FALSE;
        cl = fb->line_head;
        while( cl != NULL ) {
            if( cl->inf.ld.globmatch ) {
                fb->globalmatch = TRUE;
                break;
            }
            cl = cl->next;
        }
        /*
         * see if new one needs to be locked
         */
        cl = cfcb->line_head;
        while( cl != NULL ) {
            if( cl->inf.ld.globmatch ) {
                cfcb->globalmatch = TRUE;
                break;
            }
            cl = cl->next;
        }
    }

    /*
     * release fcbs
     */
    fb->non_swappable = FALSE;
    cfcb->non_swappable = FALSE;
    return( ERR_NO_ERR );

} /* SplitFcbAtLine */

/*
 * CheckCurrentFcbCapacity - check if fcb has exceeded its capacity; if so,
 *                           split it
 */
int CheckCurrentFcbCapacity( void )
{
    int         i, bc, bl;
    line        *cl;
    linenum     l;

    /*
     * check if fcb is full
     */
    if( FcbSize( CurrentFcb ) <= MAX_IO_BUFFER ) {
        return( ERR_NO_ERR );
    }
    FetchFcb( CurrentFcb );

    /*
     * can't take it, so split it
     */
    cl = CurrentFcb->line_head;
    bl = CurrentFcb->byte_cnt / 2;
    bc = cl->len + 1;
    l = CurrentFcb->start_line;
    while( bc < bl ) {
        cl = cl->next;
        l++;
        bc += cl->len + 1;
    }
    i = SplitFcbAtLine( l, CurrentFile, CurrentFcb );
    if( i ) {
        return( i );
    }

    /*
     * check if current line is in new fcb, if so, switch to new fcb;
     * as well, new fcb had better have the same display status as the old
     */
    CurrentFcb->next->on_display = CurrentFcb->on_display;
    if( CurrentLineNumber > CurrentFcb->end_line ) {
        CurrentFcb = CurrentFcb->next;
        FetchFcb( CurrentFcb );
    }
    return( ERR_NO_ERR );

} /* CheckCurrentFcbCapacity */
