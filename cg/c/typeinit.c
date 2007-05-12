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
* Description:  Basic target types.
*
****************************************************************************/


#include "standard.h"
#include "cgdefs.h"
#include "typclass.h"
#include "typedef.h"
#include "model.h"

extern  type_def        *TypeAddress(cg_type);
extern  type_def        *TypeAlias(cg_type,cg_type);
extern  void            TargTypeInit(void);
extern  void            InitTyping(void);


extern    type_def      *TypeInteger;
extern    type_def      *TypeHugeInteger;
extern    type_def      *TypeLongInteger;
extern    type_def      *TypeLongLongInteger;
extern    type_def      *TypeNearInteger;
extern    type_def      *TypeUnsigned;
extern    type_def      *TypePtr;
extern    type_def      *TypeBoolean;
extern    type_def      *TypeNone;
extern    type_def      *TypeProcParm;


extern  void    TypeInit( void )
/******************************/
{
    InitTyping();
    TargTypeInit();
    TypeProcParm = TypeAddress( CGTY_PROC_PARM );
    TypeInteger = TypeAddress( CGTY_INTEGER );
    TypeHugeInteger = TypeAddress( CGTY_HUGE_INTEGER );
    TypeLongInteger = TypeAddress( CGTY_LONG_INTEGER );
    TypeLongLongInteger = TypeAddress( CGTY_INT_8 );   // should be something else perhaps?
    TypeNearInteger = TypeAddress( CGTY_NEAR_INTEGER );
    TypeUnsigned = TypeAddress( CGTY_UNSIGNED );
    TypeBoolean = TypeAddress( CGTY_BOOLEAN );
    TypeNone = TypeAddress( CGTY_DEFAULT );
    TypePtr = TypeAddress( CGTY_POINTER );
}
