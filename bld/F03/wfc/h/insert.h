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
/*
* protoypes for file insert.c
*/

#ifndef insert_h_
#define insert_h_

/* needs #include "standard.h" */

extern void    TypeErr( int, uint); 
extern void    StmtExtension( int ); 
extern void    StmtErr( int );
extern void    StmtIntErr( int, int );
extern void    StmtPtrErr( int , void * );
extern void    NameWarn( int , sym_id );
extern void    NameErr( int , sym_id );
extern void    NameStmtErr( int , sym_id , int );
extern void    PrmCodeErr( int , int );
extern void    NameExt( int , sym_id );
extern void    NamNamErr( int , sym_id , sym_id );
extern void    ClassNameErr( int , sym_id );
extern void    PrevDef( sym_id ); 
extern void    NameTypeErr( int , sym_id );
extern void    TypeTypeErr( int , uint , uint );
extern void    TypeNameTypeErr( int , uint, sym_id, uint );
extern void    KnownClassErr( int , uint );
extern void    ClassErr( int , sym_id );
extern void    OpndErr( int );
extern void    IllName( sym_id );
extern void    IllType( sym_id );
extern void    StructErr( int , sym_id );
extern void    FieldErr( int , sym_id ); 

#endif
