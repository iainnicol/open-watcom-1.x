/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2004 Sybase, Inc. All Rights Reserved.
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
// protoypes for inout.c
//
#ifndef inout_h_
#define inout_h_
#pragma once

/* needs #include "standard.h" */
#ifdef __cplusplus
extern "C" void    CompErr( uint );
extern "C" bool    isErrFileOpen(void);
extern "C" void    OpenErr(void); 
extern "C" void    InitComIO(void);
extern "C" void    InitMemIO(void);
extern "C" void    FiniComIO(void);
extern "C" void    OpenSrc(void);
extern "C" void    IOPurge(void);
extern "C" void    ReadSrc(void);
extern "C" void    Include(char *);
extern "C" bool    SetLst(bool);
extern "C" void    SrcInclude( char *, const file_handle);
extern "C" void    Conclude(void);
extern "C" void    PrintErr(char *);
extern "C" void    PrtErrNL(void);
extern "C" void    JustErr(char *);
extern "C" void    CloseErr(void);
extern "C" void    TOutNL(char *);
extern "C" void    TOut(char *);
extern "C" void    OpenLst(void);
extern "C" void    ChkPntLst(void);
extern "C" bool    WasStmtListed(void);
extern "C" void    GetBanner(char *);
extern "C" void    GetCopyright(char *);
extern "C" void    GetTrademark(char *);
extern "C" void    GetMoreInfo(char *);
extern "C" void    PrtBanner(void);
extern "C" void    PrtLstNL(char *);
extern "C" void    PrtLst(char *);
extern "C" void    CloseLst(void);
extern "C" void    LFEndSrc(void);
extern "C" void    LFNewPage(void);
extern "C" void    LFSkip(void);

#else
extern void    CompErr( uint );
extern bool    isErrFileOpen(void);
extern void    OpenErr(void); 
extern void    InitComIO(void);
extern void    InitMemIO(void);
extern void    FiniComIO(void);
extern void    OpenSrc(void);
extern void    IOPurge(void);
extern void    ReadSrc(void);
extern void    Include(char *);
extern bool    SetLst(bool);
extern void    SrcInclude( char *, const file_handle);
extern void    Conclude(void);
extern void    PrintErr(char *);
extern void    PrtErrNL(void);
extern void    JustErr(char *);
extern void    CloseErr(void);
extern void    TOutNL(char *);
extern void    TOut(char *);
extern void    OpenLst(void);
extern void    ChkPntLst(void);
extern bool    WasStmtListed(void);
extern void    GetBanner(char *);
extern void    GetCopyright(char *);
extern void    GetTrademark(char *);
extern void    GetMoreInfo(char *);
extern void    PrtBanner(void);
extern void    PrtLstNL(char *);
extern void    PrtLst(char *);
extern void    CloseLst(void);
extern void    LFEndSrc(void);
extern void    LFNewPage(void);
extern void    LFSkip(void);
#endif


#endif
