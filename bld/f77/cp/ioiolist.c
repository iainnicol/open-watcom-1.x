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
// IOIOLIST  : process an input or output list
//

#include "ftnstd.h"
#include "errcod.h"
#include "opr.h"
#include "opn.h"
#include "iodefn.h"
#include "prdefn.h"
#include "global.h"
#include "stmtsw.h"

extern  bool            RecComma(void);
extern  bool            ReqComma(void);
extern  bool            RecOpenParen(void);
extern  bool            RecCloseParen(void);
extern  bool            ReqCloseParen(void);
extern  bool            RecEquSign(void);
extern  bool            RecTrmOpr(void);
extern  bool            RecNOpn(void);
extern  bool            ReqNOpn(void);
extern  bool            RecNextOpr(byte);
extern  bool            RecArrName(void);
extern  bool            RecEOS(void);
extern  void            Error(int,...);
extern  void            ChkAssumed(void);
extern  void            TermDo(void);
extern  void            ImpDo(void);
extern  void            DelCSNode(void);
extern  void            ProcIOExpr(void);
extern  void            FreeITNodes(itnode *);
extern  void            AdvanceITPtr(void);
extern  void            GStartIO(void);
extern  void            GIOItem(void);
extern  void            GIOArray(void);
extern  void            GIOStructArray(void);
extern  void            GStopIO(void);
extern  sym_id          CkAssignOk(void);
extern  void            GIOStruct(sym_id);
extern  bool            Already(uint);
extern  void            StructErr(uint,sym_id);
extern  bool            NotFormatted(void);


void    IOList() {
//================

// Process the input/output list.

    GStartIO();
    if( CITNode->link != NULL ) {
        if( RecNOpn() && RecNextOpr( OPR_TRM ) ) {
            AdvanceITPtr();                   // WRITE(6,3)
        } else if( Already( IO_NAMELIST ) ) {
            Error( IL_NO_IOLIST );
        }
        for(;;) {
            if( CITNode->link == NULL ) break;
            ProcessList();
        }
    }
    GStopIO();
}


static  bool    HasUnion( sym_id fld ) {
//======================================

    for(;;) {
        if( fld == NULL ) return( FALSE );
        if( fld->fd.typ == TY_STRUCTURE ) {
            if( HasUnion( fld->fd.xt.record->fields ) ) break;
        }
        if( fld->fd.typ == TY_UNION ) break;
        fld = fld->fd.link;
    }
    return( TRUE );
}


static  void    ChkStructIO( sym_id sym ) {
//========================================

    if( HasUnion( sym->sd.fields ) ) {
        if( ( StmtSw & SS_DATA_INIT ) || !NotFormatted() ) {
            StructErr( SP_STRUCT_HAS_UNION, sym );
        }
    }
}


bool    StartImpDo() {
//====================

// This procedure scans the i/o list to recognize an implied do.
// If it is not found FALSE returns, if it is found TRUE returns and:
// -  the implied DO is initialized
// -  a terminal operator is placed over the comma at the
//    end of the i/o list within the implied DO. This is used
//    as a signal to generate closing code for the implied DO.
// -  the nodes containing the do list are released from
//    from the internal text list.
// -  a null operator is placed over the bracket at the

    itnode      *citnode;
    itnode      *lastcomma;
    int         level;

    if( !RecNOpn() ) return( FALSE );
    if( !RecNextOpr( OPR_LBR ) ) return( FALSE );
    citnode = CITNode;
    AdvanceITPtr();
    lastcomma = NULL;
    level = 0;
    AdvanceITPtr();
    for(;;) {
        if( RecOpenParen() ) {
            level++;
        } else if( RecCloseParen() ) {
            level--;
        } else if( RecComma() && ( level == 0 ) ) {
            lastcomma = CITNode;
        }
        if( ( level < 0 ) || RecTrmOpr() ) {
            CITNode = citnode;
            return( FALSE );
        }
        AdvanceITPtr();
        if( RecEquSign() && ( level == 0 ) ) break;
    }
    if( ( lastcomma == NULL ) || ( lastcomma->link != CITNode ) ) {
        CITNode = citnode;
        return( FALSE );
    }
    InitImpDo( lastcomma );
    CITNode = citnode;
    AdvanceITPtr();
    if( ( RecNextOpr( OPR_TRM ) && RecNOpn() ) ) {
        Error( IL_EMPTY_IMP_DO );
    }
    return( TRUE );
}


void    ProcessList() {
//=====================

// This procedure will process one 'thing' from the i/o list. A 'thing' is:
//     1) initializing an implied DO
//     2) finishing an implied DO
//     3) an i/o list item

    if( RecTrmOpr() ) {
        FinishImpDo();
        if( !RecTrmOpr() ) {
            ReqComma();
        }
    } else if( !StartImpDo() ) {
        ProcIOExpr();
        ListItem();
        if( !RecTrmOpr() ) {
            ReqComma();
        }
    }
}


void    ListItem() {
//==================

// Process one list item.

    sym_id      sd;

    if( RecNOpn() ) {
        if( !CpError ) {
            Error( SX_SURP_OPR );
        }
    } else if( RecArrName() ) {
        CITNode->sym_ptr->ns.xflags |= SY_DEFINED;
        ChkAssumed();
        if( CITNode->typ == TY_STRUCTURE ) {
            ChkStructIO( CITNode->sym_ptr->ns.xt.record );
            GIOStructArray();
        } else {
            GIOArray();
        }
    } else if( CITNode->typ == TY_STRUCTURE ) {
        CITNode->sym_ptr->ns.xflags |= SY_DEFINED;
        if( CITNode->opn & OPN_FLD ) {
            sd = CITNode->value.st.field_id->fd.xt.record;
        } else {
            sd = CITNode->sym_ptr->ns.xt.record;
        }
        ChkStructIO( sd );
        GIOStruct( sd );
    } else {
        if( StmtProc == PR_READ ) {
            CkAssignOk();
        }
        GIOItem();
    }
    AdvanceITPtr();
}


void    InitImpDo( itnode *lastcomma ) {
//======================================

// Initialize the implied DO-loop.

    int         level;
    itnode      *imp_do_list;

    CITNode = lastcomma;
    CITNode->opr = OPR_TRM;     // marks the end of the i/o list
    ImpDo();
    if( !ReqCloseParen() ) {
        level = 0;
        for(;;) {
            if( RecOpenParen() ) {
                level++;
            } else if( RecCloseParen() ) {
                level--;
            }
            if( level < 0 ) break;
            if( CITNode->link == NULL ) {
                DelCSNode();
                CITNode->opr = OPR_TRM;
                CITNode->oprpos = 9999;
                break;
            }
            AdvanceITPtr();
        }
    }
    ReqNOpn();
    imp_do_list = lastcomma->link;
    lastcomma->link = CITNode->link;
    CITNode->link = NULL;
    FreeITNodes( imp_do_list );
}


void    FinishImpDo() {
//=====================

// Finish the implied DO.

    TermDo();
    AdvanceITPtr();
}
