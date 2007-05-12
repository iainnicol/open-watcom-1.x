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


#include "standard.h"
#include "coderep.h"
#include "typedef.h"
#include "cgdefs.h"
#include "procdef.h"

extern  type_def*       TypeAddress(cg_type);
extern  type_class_def  MapPointer(cg_type);
extern  type_class_def  MapIntReturn(cg_type);
extern  type_class_def  MapFloat(cg_type,call_attributes);
extern  type_class_def  MapStruct(type_length,call_attributes);

static cg_type  Types[] = {
         CGTY_UINT_1,
         CGTY_INT_1,
         CGTY_UINT_2,
         CGTY_INT_2,
         CGTY_UINT_4,
         CGTY_INT_4,
         CGTY_UINT_8,
         CGTY_INT_8,
         CGTY_LONG_POINTER,
         CGTY_HUGE_POINTER,
         CGTY_SINGLE,
         CGTY_DOUBLE,
         CGTY_DOUBLE,
         CGTY_DEFAULT
         };


extern  type_def        *ClassType( type_class_def tipe ) {
/*********************************************************/

    return( TypeAddress( Types[ tipe ] ) );
}


extern  type_class_def  ReturnClass( type_def *tipe, call_attributes attr ) {
/***************************************************************************/

    switch( tipe->refno ) {
    case CGTY_INT_1:
    case CGTY_UINT_1:
    case CGTY_INT_2:
    case CGTY_UINT_2:
    case CGTY_INT_4:
    case CGTY_UINT_4:
    case CGTY_INT_8:
    case CGTY_UINT_8:
        return( MapIntReturn( tipe->refno ) );
    case CGTY_NEAR_POINTER:
    case CGTY_NEAR_CODE_PTR:
    case CGTY_HUGE_POINTER:
    case CGTY_LONG_CODE_PTR:
    case CGTY_LONG_POINTER:
        return( MapPointer( tipe->refno ) );
    case CGTY_SINGLE:
    case CGTY_DOUBLE:
    case CGTY_LONG_DOUBLE:
        return( MapFloat( tipe->refno, attr ) );
    default:
        return( MapStruct( tipe->length, attr ) );
    }
}


extern  type_class_def  TypeClass( type_def *tipe ) {
/***************************************************/

    switch( tipe->refno ) {
    case CGTY_INT_1:
        return( I1 );
    case CGTY_UINT_1:
        return( U1 );
    case CGTY_INT_2:
        return( I2 );
    case CGTY_UINT_2:
        return( U2 );
    case CGTY_INT_4:
        return( I4 );
    case CGTY_UINT_4:
        return( U4 );
    case CGTY_INT_8:
        return( I8 );
    case CGTY_UINT_8:
        return( U8 );
    default:
        return( ReturnClass( tipe, EMPTY ) );
    }
}
