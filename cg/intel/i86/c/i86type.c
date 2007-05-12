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
* Description:  Special i86 pointer types.
*
****************************************************************************/


#include "standard.h"
#include "cgdefs.h"
#include "typclass.h"
#include "typedef.h"
#include "model.h"
#include "targsys.h"

extern  type_def        *TypeAlias(cg_type,cg_type);
extern  type_def        *TypeAddress( cg_type );

//type_def THugeCP= {  CGTY_LONG_CODE_PTR,4,      TYPE_POINTER + TYPE_CODE };
type_def TLongCP= {  CGTY_LONG_CODE_PTR,4,      TYPE_POINTER + TYPE_CODE };
type_def TNearCP= {  CGTY_NEAR_CODE_PTR,2,      TYPE_POINTER + TYPE_CODE };
type_def THugeP = {  CGTY_HUGE_POINTER, 4,      TYPE_POINTER };
type_def TLongP = {  CGTY_LONG_POINTER, 4,      TYPE_POINTER };
type_def TNearP = {  CGTY_NEAR_POINTER, 2,      TYPE_POINTER };

extern type_def *PTInteger;
extern type_def *PTUnsigned;
extern type_def *PTPointer;
extern type_def *PTCodePointer;


extern  void    TargTypeInit( void )
/**********************************/
{
    TypeAlias( CGTY_UNSIGNED, CGTY_UINT_2 );
    TypeAlias( CGTY_INTEGER, CGTY_INT_2 );
    PTInteger = TypeAddress( CGTY_INT_2 );
    PTUnsigned = TypeAddress( CGTY_UINT_2 );

    if( _IsTargetModel( BIG_CODE ) ) {
        TypeAlias( CGTY_CODE_PTR, CGTY_LONG_CODE_PTR );
        PTCodePointer = TypeAddress( CGTY_LONG_CODE_PTR );
    } else {
        TypeAlias( CGTY_CODE_PTR, CGTY_NEAR_CODE_PTR );
        PTCodePointer = TypeAddress( CGTY_NEAR_CODE_PTR );
    }
    if( _IsTargetModel( BIG_DATA ) ) {
        if( _IsTargetModel( CHEAP_POINTER ) ) {
            TypeAlias( CGTY_POINTER, CGTY_LONG_POINTER );
            PTPointer = TypeAddress( CGTY_LONG_POINTER );
        } else {
            TypeAlias( CGTY_POINTER, CGTY_HUGE_POINTER );
            PTPointer = TypeAddress( CGTY_HUGE_POINTER );
        }
    } else {
        TypeAlias( CGTY_POINTER, CGTY_NEAR_POINTER );
        PTPointer = TypeAddress( CGTY_NEAR_POINTER );
    }
    TypeAlias( CGTY_NEAR_INTEGER, CGTY_INT_2 );
    TypeAlias( CGTY_LONG_INTEGER, CGTY_INT_2 );
    TypeAlias( CGTY_HUGE_INTEGER, CGTY_INT_4 );
}
