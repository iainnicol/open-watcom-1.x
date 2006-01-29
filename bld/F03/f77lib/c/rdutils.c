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
// RDUTILS      : Run-time utilities for READ
//

#include "ftnstd.h"
#include "rundat.h"
#include "errcod.h"

#include <string.h>

extern  void            Suicide(void);
extern  void            IOErr(int,...);
extern  bool            NoEOF(ftnfile *);
extern  void            FGetBuff(ftnfile *);
extern  void            SetEOF(void);
extern  void            SysEOF(void);
extern  void            ChkIOErr(ftnfile *);
extern  void            NextIFBuff(char *,int,unsigned_32,string  *);
extern  void            UpdateRecNum(ftnfile *);


void    NextRec() {
//=================

    ftnfile     *fcb;

    fcb = IOCB->fileinfo;
    if( fcb->flags & FTN_EOF ) {
        IOErr( IO_PAST_EOF );
    } else {
        if( fcb->internal != NULL ) {
            if( fcb->recnum > IOCB->elmts ) {
                fcb->flags |= FTN_EOF;
            }
            fcb->len = fcb->internal->len;
            NextIFBuff( fcb->buffer, fcb->len, fcb->recnum, fcb->internal );
            fcb->recnum++;
        } else {
            UpdateRecNum( fcb );
            FGetBuff( fcb );
            ChkIOErr( fcb );
            if( ( IOCB->set_flags & SET_FMTPTR ) &&
                ( ( IOCB->flags & NML_DIRECTED ) == 0 ) ) {
                memset( fcb->buffer + fcb->len, ' ', fcb->bufflen - fcb->len  );
                fcb->len = fcb->bufflen;
            }
            fcb->buffer[ fcb->len ] = NULLCHAR;
        }
        if( fcb->flags & FTN_EOF ) {
            if( !NoEOF( fcb ) && !_NoRecordOrganization( fcb ) ) {
                fcb->eofrecnum = fcb->recnum - 1;
            }
            SysEOF();
        }
        fcb->col = 0;
    }
}
