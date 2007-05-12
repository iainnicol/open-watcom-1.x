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
* Description:  Mapping of cg to CPU specific types for MIPS.
*
****************************************************************************/


#include "standard.h"
#include "coderep.h"
#include "cgdefs.h"
#include "procdef.h"
#include "zoiks.h"

extern type_class_def MapIntReturn( cg_type type )
/************************************************/
{
    switch( type ) {
    case CGTY_INT_1:
    case CGTY_INT_2:
    case CGTY_INT_4:
        return( I4 );
    case CGTY_INT_8:
        return( I8 );
    case CGTY_UINT_1:
    case CGTY_UINT_2:
    case CGTY_UINT_4:
        return( U4 );
    case CGTY_UINT_8:
        return( U8 );
    default:
        _Zoiks( ZOIKS_123 );
        return( XX );
    }
}


extern type_class_def MapPointer( cg_type type )
/***********************************************
    return the internal type associated with
    pointer type given. This varies depending upon
    the archtecture
*/
{
    switch( type ) {
    case CGTY_NEAR_POINTER:
    case CGTY_NEAR_CODE_PTR:
    case CGTY_HUGE_POINTER:
    case CGTY_LONG_POINTER:
    case CGTY_LONG_CODE_PTR:
        return( U4 );
    default:
        _Zoiks( ZOIKS_123 );
        return( XX );
    }
}


extern  type_class_def  MapFloat( cg_type type, call_attributes attr )
/*********************************************************************
    called by the return value generator to decide whether to treat
    floating point return values as floats or structs.
*/
{
    attr = attr;
    if( type == CGTY_SINGLE ) return( FS );
    return( FD );
}


extern  type_class_def MapStruct( type_length length, call_attributes attr )
/***************************************************************************
    called by the return value generator to decide whether to treat
    1/2/4 byte struct return values as ints or structs.
*/
{
    attr = attr;
    length = length;
#if 0
    if( length == 1 ) return( U1 );
    if( length == 2 ) return( U2 );
    if( length == 4 ) return( U4 );
#endif
    return( XX );
}
