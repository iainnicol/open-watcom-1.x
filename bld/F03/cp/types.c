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
// TYPES        : Type size information
//

#include "ftnstd.h"
#include "global.h"
#include "symflgs.h"
#include "cpopt.h"


// This array is indexed by the TY_... values defined in symflags.h e.g. TY_REAL = 5
// there are more TY_... values than in this array index > TY_STRUCTURE is outside of this array
const byte __FAR        Sizes[] = { 1, 4,               // LOGICAL (TY_LOGICAL_1, TY_LOGICAL)
                                    1, 2, 4,            // INTEGER  (TY_INTEGER_1, TY_INTEGER_2, TY_INTEGER)
                                    4, 8, 16,           // REAL     (TY_REAL, TY_DOUBLE, TY_TRUE_EXTENDED)
                                    8, 16, 32,          // COMPLEX  (TY_COMPLEX, TY_DCOMPLEX, TY_TRUE_XCOMPLEX
                                    1,                  // CHARACTER(TY_CHAR)
                                    0, };               // STRUCTURE(TY_STRUCTURE)


uint            TypeSize( uint typ ) {
//====================================

// Get the size of the storage unit for the given data type.

    return( Sizes[ typ ] );
}


uint            StorageSize( uint typ ) {
//=======================================

// Get the size of the storage unit for a the given data type.
// This function is sensitive to the "short" option.

    if( Options & OPT_SHORT ) {
        if( typ == TY_INTEGER ) return( sizeof( intstar2 ) );
        if( typ == TY_LOGICAL ) return( sizeof( logstar1 ) );
    }
    if( Options & OPT_EXTEND_REAL ) {
        if( typ == TY_REAL ) return( sizeof( double ) );
        if( typ == TY_DOUBLE ) return( Sizes[ TY_EXTENDED ] );
    }
    return( Sizes[ typ ] );
}


intstar4        ITIntValue( itnode *it ) {
//========================================

// Get integer value from i.t. node.

    if( it->size == sizeof( intstar1 ) ) {
        if( it->is_unsigned ) {
            return( (unsigned_8)it->value.intstar1 );
        } else {
            return( it->value.intstar1 );
        }
    }
    if( it->size == sizeof( intstar2 ) ) {
        if( it->is_unsigned ) {
            return( (unsigned_16)it->value.intstar2 );
        } else {
            return( it->value.intstar2 );
        }
    }
    // must be sizeof( intstar4 )
    return( it->value.intstar4 );
}
