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
// CSLOOPS   : processing for all looping structures
//

#include "ftnstd.h"
#include "errcod.h"
#include "opr.h"
#include "opn.h"
#include "global.h"
#include "stmtsw.h"

extern  void            *FMemAlloc(int);
extern  void            Error(int,...);
extern  void            Extension(int,...);
extern  void            CkTypeDeclared(void);
extern  void            AddCSNode(byte);
extern  void            DelCSNode(void);
extern  void            BlockLabel(void);
extern  void            ColonLabel(void);
extern  void            CSNoMore(void);
extern  void            CSExtn(void);
extern  void            Match(void);
extern  void            CSCond(label_id);
extern  void            EatDoParm(void);
extern  void            AdvanceITPtr(void);
extern  bool            RecNOpn(void);
extern  bool            RecNumber(void);
extern  bool            RecNOpr(void);
extern  bool            RecNextOpr(byte);
extern  bool            RecComma(void);
extern  bool            RecName(void);
extern  bool            ReqDoVar(void);
extern  bool            ReqNextOpr(byte,int);
extern  bool            ReqNOpn(void);
extern  bool            RecKeyWord(char *);
extern  void            GLabel(label_id);
extern  void            GBranch(label_id);
extern  label_id        NextLabel(void);
extern  unsigned_32     LkUpDoTerm(void);
extern  sym_id          STShadow(sym_id);
extern  void            STUnShadow(sym_id);
extern  void            Recurse(void);
extern  void            GDoInit(int);
extern  void            GDoEnd(void);
extern  void            NameErr(int,sym_id);
extern  void            FreeLabel(label_id);
extern  void            RemKeyword(itnode *,int);
extern  void            BIOutSymbol(sym_id);
#if _OPT_CG == _OFF
extern  void            GDbugInfo(void);
extern  void            GISNCall(void);
#endif


static  void    InitLoop( int loop_type ) {
//=========================================

    AddCSNode( loop_type );
    CSHead->branch = NextLabel();
    CSHead->bottom = NextLabel();
    CSHead->cycle = NextLabel();
    GLabel( CSHead->branch );
}


static  void    FiniLoop() {
//==========================

    GBranch( CSHead->branch );
    GLabel( CSHead->bottom );
    FreeLabel( CSHead->branch );
    FreeLabel( CSHead->bottom );
    FreeLabel( CSHead->cycle );
}


void    CpLoop() {
//================

// Compile a LOOP statement.

    CSExtn();
    InitLoop( CS_LOOP );
    BlockLabel();
#if _OPT_CG == _OFF
    GDbugInfo();
#endif
}


void    CpEndLoop() {
//===================

// Compile an ENDLOOP statment.

    if( CSHead->typ == CS_LOOP ) {
        GLabel( CSHead->cycle );
        FiniLoop();
    } else {
        Match();
    }
    DelCSNode();
    CSNoMore();
}


void    CpWhile() {
//=================

// Compile a WHILE statement.
//    WHILE( expr )DO <:label> -- block while
//    WHILE( expr )   <:label> -- block while
//    WHILE( expr ) STATEMENT  -- one line while

    CSExtn();
    InitLoop( CS_WHILE );
#if _OPT_CG == _OFF
    GISNCall();
#endif
    CSCond( CSHead->bottom );
    if( RecNOpn() && RecNextOpr( OPR_COL ) ) {
        BlockLabel();
    } else if( RecKeyWord( "DO" ) &&
               ( RecNextOpr( OPR_TRM ) || RecNextOpr( OPR_COL ) ) ) {
        CITNode->opn = OPN_PHI;
        BlockLabel();
    } else {
        Recurse();
        GLabel( CSHead->cycle );
        FiniLoop();
        DelCSNode();
    }
}


void    CpEndWhile() {
//====================

// Compile an ENDWHILE statement.

    if( CSHead->typ == CS_WHILE ) {
        GLabel( CSHead->cycle );
        FiniLoop();
    } else {
        Match();
    }
    DelCSNode();
    CSNoMore();
}


void    CpUntil() {
//=================

// Compile an UNTIL statement.

    if( ( CSHead->typ == CS_LOOP ) || ( CSHead->typ == CS_WHILE ) ) {
        GLabel( CSHead->cycle );
        CSCond( CSHead->branch );
        GLabel( CSHead->bottom );
        FreeLabel( CSHead->branch );
        FreeLabel( CSHead->bottom );
        FreeLabel( CSHead->cycle );
    } else {
        Match();
    }
    DelCSNode();
    CSNoMore();
}


static  unsigned_32     DoLabel() {
//=================================

    unsigned_32 term;

    if( RecNumber() ) {
        term = LkUpDoTerm();
        AdvanceITPtr();
        if( !RecNOpr() && !RecComma() ) {
            Error( DO_NO_COMMA_OR_VAR );
        }
    } else {
        term = 0;
    }
    return( term );
}


void    CpDo() {
//==============

// Compile a DO statement.

    signed_32   term;

    AddCSNode( CS_DO );
    term = DoLabel();
    if( term == 0 ) {
        Extension( DO_DO_EXT );
    }
    InitDo( term );
    ColonLabel();
}


void    CpDoWhile() {
//===================

// Compile a DO WHILE statement.

    Extension( DO_DO_EXT );
    InitLoop( CS_DO_WHILE );
    CSHead->cs_info.do_term = DoLabel();
    if( RecKeyWord( "WHILE" ) ) {
        RemKeyword( CITNode, 5 );
        CSCond( CSHead->bottom );
        BlockLabel();
    } else {
        if( ReqNOpn() ) {
            BlockLabel();
        }
    }
}


void    CpEndDo() {
//=================

// Compile an ENDDO statement.

    if( CSHead->typ == CS_DO ) {
        if( CSHead->cs_info.do_parms->do_term == 0 ) {
            TermDo();
        } else {
            BadDoEnd();
        }
    } else if( CSHead->typ == CS_DO_WHILE ) {
        if( CSHead->cs_info.do_term == 0 ) {
            TermDoWhile();
        } else {
            BadDoEnd();
        }
    } else {
        Match();
    }
    CSNoMore();
}


static  void    BadDoEnd() {
//==========================

    Error( DO_BAD_ENDDO );
    FreeLabel( CSHead->branch );
    FreeLabel( CSHead->bottom );
    DelCSNode();
}


void    InitDo( signed_32 term ) {
//================================

// Initialize a DO or implied DO.
// Process "do i=e1,e2,e3" where e1, e2 and e3 are numeric expressions.
//

    do_entry    *do_pointer;
    sym_id      do_var;

#if _OPT_CG == _ON
    if( ( StmtSw & SS_DATA_INIT ) == 0 ) {
#endif
        CSHead->branch = NextLabel();
        CSHead->bottom = NextLabel();
        CSHead->cycle = NextLabel();
#if _OPT_CG == _ON
    }
#endif
    do_pointer = FMemAlloc( sizeof( do_entry ) );
    CSHead->cs_info.do_parms = do_pointer;
    do_pointer->do_term = term;
    do_pointer->do_parm = NULL;
    if( ReqDoVar() ) {
        CkTypeDeclared();
        do_var = CITNode->sym_ptr;
        BIOutSymbol( do_var );
        do_var->ns.flags |= SY_REFERENCED;
        do_var->ns.xflags |= SY_DEFINED;
        if( do_var->ns.flags & SY_DO_PARM ) {
            Error( DO_PARM_REDEFINED );
        }
        do_pointer->do_parm = do_var;   // remember id of "i"
        ReqNextOpr( OPR_EQU, EQ_NO_EQUALS );
        if( StmtSw & SS_DATA_INIT ) {
            if( !_IsTypeInteger( do_var->ns.typ ) ) {
                NameErr( DA_BAD_DO_VAR, do_var );
            }
            do_var = STShadow( do_var );
            CITNode->flags = do_var->ns.flags;
        }
        CITNode->sym_ptr = do_var;
        GDoInit( do_var->ns.typ );
#if _OPT_CG == _OFF
        GLabel( CSHead->branch );
#endif
        do_var->ns.flags |= SY_DO_PARM;
    }
}


void    ImpDo() {
//===============

    AddCSNode( CS_DO );
    InitDo( 0 );
}


void    TermDo() {
//================

// Terminate a DO or an implied DO.

    do_entry    *do_pointer;
    sym_id      do_var;

    if( CSHead->typ == CS_DO ) {
        do_pointer = CSHead->cs_info.do_parms;
        if( do_pointer->do_parm != NULL ) {
            if( ( StmtSw & SS_DATA_INIT ) == 0 ) {
                GLabel( CSHead->cycle );
            }
            GDoEnd();
            do_var = do_pointer->do_parm;
            if( (do_var->ns.flags & SY_SPECIAL_PARM) &&
                !(do_var->ns.flags & SY_PS_ENTRY) ) {
                STUnShadow( do_var );
            }
            do_var->ns.flags &= ~SY_DO_PARM;
#if _OPT_CG == _ON
            if( ( StmtSw & SS_DATA_INIT ) == 0 ) {
#endif
                GLabel( CSHead->bottom );
#if _OPT_CG == _ON
            }
#endif
        }
    } else {
        Match();
    }
#if _OPT_CG == _ON
    if( ( StmtSw & SS_DATA_INIT ) == 0 ) {
#endif
        FreeLabel( CSHead->branch );
        FreeLabel( CSHead->bottom );
        FreeLabel( CSHead->cycle );
#if _OPT_CG == _ON
    }
#endif
    DelCSNode();
}


void            TermDoWhile() {
//=============================

    GLabel( CSHead->cycle );
    FiniLoop();
    DelCSNode();
}


void    CpContinue() {
//====================

// Compile a CONTINUE statement.

    CSNoMore();
}
