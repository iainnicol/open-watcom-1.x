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
// CLE       : compile, link, and execute a FORTRAN program
//

#include "ftnstd.h"
#include "global.h"
#include "progsw.h"
#include "cpopt.h"

#include <time.h>

extern  void            ComRead(void);
extern  void            OpenSrc(void);
extern  void            OpenLst(void);
extern  bool            SetLst(bool);
extern  void            PrtBanner(void);
extern  void            LFEndSrc(void);
extern  void            CloseLst(void);
extern  void            CloseErr(void);
extern  void            DoCompile(void);
extern  void            StatProg(void);
extern  void            VSTInit(void);
extern  void            STPurge(void);
extern  void            ITPurge(void);
extern  void            CSPurge(void);
extern  void            IOPurge(void);
extern  void            EnPurge(void);
extern  void            EqPurge(void);
extern  void            TDPurge(void);
extern  void            OpenSymTab(void);
extern  void            Conclude(void);
extern  void            InitMacros(void);
extern  void            FiniMacros(void);
extern  void            FiniMacroProcessor(void);
extern  void            InitAuxInfo(void);
extern  void            FiniAuxInfo(void);
#if _OPT_CG == _OFF
extern  void            SetRunVars(void);
extern  void            DoExecute(void);
#else
extern  void            InitGlobalSegs(void);
extern  void            FreeGlobalSegs(void);
extern  void            SDRewind(file_handle);
#endif

unsigned_32     CompTime;
#if _OPT_CG == _OFF
unsigned_32     ExecTime;
#endif


void            CLE() {
//=====================

    time_t      start;

    InitPurge();
    OpenSrc();
    if( CurrFile != NULL ) {
        StartCompile();
        start = time( NULL );
        Compile();
        CompTime = difftime( time( NULL ), start );
        FiniCompile();
#if _OPT_CG == _OFF
        if( (Options & OPT_RUN) && !(ProgSw & PS_ERROR) ) {
            if( (Options & OPT_LINK) || !(Options & OPT_OBJECT) ) {
                StartExecute();
                start = time( NULL );
                Execute();
                ExecTime = difftime( time( NULL ), start );
                FiniExecute();
            }
        }
#endif
        Conclusion();
    } else {
        // Consider: wfc /who what
        CloseErr();
    }
}


static  void    StartCompile() {
//==============================

    OpenLst();
    PrtBanner();
}


#if _OPT_CG == _OFF

static  void    Compile() {
//=========================

    InitAuxInfo();      // must be done before ComRead()
    InitMacros();
    ComRead(); // pre-read must occur here in case of null program
    DoCompile();
    FiniMacros();
    FiniAuxInfo();
}


static  void    StartExecute() {
//==============================

    SetRunVars();
}


static  void    Execute() {
//=========================

    DoExecute();
}


static  void    FiniExecute() {
//=============================

}


#else

static  void    Compile() {
//=========================

    InitGlobalSegs();
    ProgSw |= PS_DONT_GENERATE;
    InitAuxInfo();      // must be done before ComRead()
    InvokeCompile();
    if( ( ( Options & OPT_SYNTAX ) == 0 ) && // syntax check only
        ( ( CurrFile != NULL ) ) &&          // not an "null" file
        ( ( ProgSw & PS_ERROR ) == 0 ) ) {   // no error during first pass
        CurrFile->flags &= ~CONC_PENDING;
        CurrFile->rec = 0;
        SrcRecNum = 0;
        ProgSw = 0;
        SDRewind( CurrFile->fileptr );
        InvokeCompile();
    }
    FiniAuxInfo();
    FreeGlobalSegs();
}


void            InvokeCompile() {
//===============================

    InitMacros();
    ComRead(); // pre-read must occur here in case of null program
    if( ProgSw & PS_SOURCE_EOF ) {
        Conclude();
    } else {
        DoCompile();
    }
    FiniMacros();
}

#endif


static  void    FiniCompile() {
//=============================

    SetLst( TRUE ); // listing file on for statistics
    LFEndSrc();
    CloseErr();
}


static  void    Conclusion() {
//============================

    StatProg();
    if( ProgSw & PS_ERROR ) {
        PurgeAll();
    }
    CloseLst();
}


void            PurgeAll() {
//==========================

    STPurge();
    ITPurge();
    CSPurge();
    IOPurge();
    EnPurge();
    EqPurge();
    TDPurge();
    FiniMacroProcessor();
}


static  void    InitPurge() {
//===========================

// Initialize variables for purge routines in case the purge routines
// get called and the corresponding variables don't get initialized.

    // Initialize for STPurge();
    OpenSymTab();
    VSTInit();
    // Initialize for ITPurge();
    ITHead = NULL;
    ITPool = NULL;
    // Initialize for CSPurge();
    CSHead = NULL;
    // Initialize for IOPurge();
    CurrFile = NULL;
    // Initialize for EnPurge();
    Entries = NULL;
    // Initialize for EqPurge();
    EquivSets = NULL;
}
