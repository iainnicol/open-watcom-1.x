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
// EXCLOSE      : Run-time CLOSE statement processor
//

#include "ftnstd.h"
#include "errcod.h"
#include "rundat.h"
#include "rtenv.h"

extern  void            IOErr(int,...);
extern  bool            FindFtnFile(void);
extern  void            CloseFile(ftnfile *);
extern  void            CloseDeleteFile(ftnfile *);
extern  int             FindKWord(char **,int,int,string PGM *);
extern  void            DiscoFile(ftnfile *);
extern  int             IOMain(void (*)());

//
// ClStatTab - close status table
//

static  char    *ClStatTab[] = {
        "unknown",
        "keep",
        "delete",
        NULL };


static  void    ExClose() {
//=========================

    byte        cl_stat;
    byte        op_stat;

    if( IOCB->flags & BAD_UNIT ) {
        IOErr( IO_IUNIT );
    }
    FindFtnFile();
    if( IOCB->fileinfo != NULL ) {
        CloseFile( IOCB->fileinfo );
        cl_stat = FindKWord( ClStatTab, STAT_SPEC, STATUS_UNKNOWN,
             ( IOCB->set_flags & SET_STATPTR ) ? IOCB->statptr : NULL );
        op_stat = IOCB->fileinfo->status;
        if( cl_stat == STATUS_UNKNOWN ) {
            cl_stat = STATUS_KEEP;
            if( op_stat == STATUS_SCRATCH ) {
                cl_stat = STATUS_DELETE;
            }
        }
        if( ( cl_stat == STATUS_KEEP ) && ( op_stat == STATUS_SCRATCH ) ) {
            IOErr( IO_ISTAT );
        }
        if( (cl_stat == STATUS_DELETE) && (IOCB->fileinfo->flags & FTN_FSEXIST) ) {
            CloseDeleteFile( IOCB->fileinfo );
        } else {
            CloseFile( IOCB->fileinfo );
        }
        DiscoFile( IOCB->fileinfo );
    }
}


int     IOClose() {
//=================

    IOCB->iostmt = IO_CLOSE;
    return( IOMain( &ExClose ) );
}
