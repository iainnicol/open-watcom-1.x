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
// CSIF      : processing for the block and logical IF
//

#include "ftnstd.h"
#include "errcod.h"
#include "ctrlflgs.h"
#include "opn.h"
#include "opr.h"
#include "global.h"

extern  void            Error(int,...);
extern  void            AddCSNode(byte);
extern  void            DelCSNode(void);
extern  void            BlockLabel(void);
extern  void            CSNoMore(void);
extern  void            Match(void);
extern  void            CSCond(label_id);
extern  void            Recurse(void);
extern  void            GLabel(label_id);
extern  void            GBranch(label_id);
extern  void            AdvanceITPtr(void);
extern  label_id        NextLabel(void);
extern  bool            RecNOpn(void);
extern  bool            RecNextOpr(byte);
extern  bool            ReqEOS(void);
extern  bool            RecKeyWord(char *);
extern  void            FreeLabel(label_id);
#if _OPT_CG == _OFF
extern  void            GISNCall(void);
#endif


void    CpLogIf() {
//=================

// Process a logical IF statement.

    label_id    if_skip;

    if_skip = NextLabel();
    CSCond( if_skip );
    if( RecKeyWord( "THEN" ) &&
        ( RecNextOpr( OPR_TRM ) || RecNextOpr( OPR_COL ) ) ) {
        AddCSNode( CS_IF );
        CSHead->branch = if_skip;
        CSHead->bottom = NextLabel();
        CITNode->opn = OPN_PHI;       // not part of the block label
        BlockLabel();
        CtrlFlgs |= CF_BAD_DO_ENDING;
    } else {
        Recurse();
        GLabel( if_skip );
        FreeLabel( if_skip );
    }
}


void    CpElseIf() {
//==================

// Process an ELSEIF statement.

    if( ( CSHead->typ == CS_IF ) || ( CSHead->typ == CS_ELSEIF ) ) {
        GBranch( CSHead->bottom );
        GLabel( CSHead->branch );
        FreeLabel( CSHead->branch );
#if _OPT_CG == _OFF
        GISNCall();
#endif
        CSHead->typ = CS_ELSEIF;
        CSHead->branch = NextLabel();
        CSHead->block = ++BlockNum;
    } else if( CSHead->typ == CS_ELSE ) {
        Error( IF_ELSE_LAST );
    } else {
        Match();
    }
    CSCond( CSHead->branch );
    if( RecKeyWord( "THEN" ) ) {
        AdvanceITPtr();
        ReqEOS();
    } else {
        Error( IF_NO_THEN );
    }
}


void    CpElse() {
//================

// Process an ELSE statement.

    if( ( CSHead->typ == CS_IF ) || ( CSHead->typ == CS_ELSEIF ) ) {
        GBranch( CSHead->bottom );
        GLabel( CSHead->branch );
        FreeLabel( CSHead->branch );
#if _OPT_CG == _OFF
        GISNCall();
#endif
        CSHead->typ = CS_ELSE;
        CSHead->block = ++BlockNum;
    } else if( CSHead->typ == CS_ELSE ) {
        Error( IF_ELSE_LAST );
    } else {
        Match();
    }
    CSNoMore();
}


void    CpEndif() {
//=================

// Process an ENDIF statement.

    if( ( CSHead->typ == CS_IF ) || ( CSHead->typ == CS_ELSEIF ) ) {
        GLabel( CSHead->branch );
        FreeLabel( CSHead->branch );
        GLabel( CSHead->bottom );
        FreeLabel( CSHead->bottom );
#if _OPT_CG == _OFF
        GISNCall();
#endif
    } else if( CSHead->typ == CS_ELSE ) {
        GLabel( CSHead->bottom );
        FreeLabel( CSHead->bottom );
#if _OPT_CG == _OFF
        GISNCall();
#endif
    } else {
        Match();
    }
    DelCSNode();
    CSNoMore();
}
