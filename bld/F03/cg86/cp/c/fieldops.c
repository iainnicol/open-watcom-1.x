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
// FIELDOPS     : field selection operator generation routines
//

#include "ftnstd.h"
#include "global.h"
#include "opn.h"
#include "fcodes.h"
#include "stmtsw.h"
#include "objutil.h"

extern  void            EmitOp(unsigned_16);
extern  void            PushOpn(itnode *);
extern  void            DumpTypes(uint,uint,uint,uint);
extern  uint            TypeSize(uint);
extern  sym_id          GTempString(uint);
extern  void            PushConst(intstar4);


void    GFieldSCB( inttarg size ) {
//=================================

// Setup an SCB for a character field.

    PushConst( size );
    EmitOp( FLIP );
}


void    FieldOp( int typ1, int typ2, int op ) {
//=============================================

// Generate code for a field selection operator.

    typ1 = typ1; op = op;
    PushOpn( CITNode->link );
    PushOpn( CITNode );
    if( CITNode->opn & OPN_FLD ) {
        // sub-field reference
        EmitOp( ADD );
        DumpTypes( TY_INTEGER, TypeSize( TY_INTEGER ),
                   TY_INTEGER, TypeSize( TY_INTEGER ) );
    } else {
        EmitOp( FIELD_OP );
        OutPtr( CITNode->sym_ptr );
        if( ( StmtSw & SS_DATA_INIT ) == 0 ) {
            if( typ2 == TY_CHAR ) {
                if( ( CITNode->link->opn & OPN_WHAT ) != OPN_ARR ) {
                    if( ( ( CITNode->link->opn & OPN_WHAT ) != OPN_NWL ) &&
                        ( ( CITNode->link->opn & OPN_WHAT ) != OPN_ASS ) ) {
                        GFieldSCB( CITNode->link->size );
                    }
                    EmitOp( MAKE_SCB );
                    OutPtr( GTempString( 0 ) );
                }
            }
        } else {
            OutPtr( CITNode->link->sym_ptr );
        }
    }
}
