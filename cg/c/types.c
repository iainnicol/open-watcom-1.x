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
* Description:  Code generator type system.
*
****************************************************************************/


#include "standard.h"
#include "cgdefs.h"
#include "typclass.h"
#include "typedef.h"
#include "cgmem.h"

typedef enum {
                TYPE_DEFINITION,
                TYPE_ALIAS
} type_class;

typedef struct alias {
    struct type_def     *tptr;
    cg_type             refno;
} alias;

typedef union type_alloc {
        struct alias    alias;
        struct type_def type_def;
} type_alloc;

typedef struct type_list {
        union type_alloc        tipe;
        struct type_list        *link;
        type_class              format;
} type_list;

static    type_list     *TypeList;


/*                          refno           length  attributes*/
/*                          ======          ======  ==========*/

static type_def TUInt1 = {  CGTY_UINT_1,       1,      0 };
static type_def TInt1  = {  CGTY_INT_1,        1,      TYPE_SIGNED };
static type_def TUInt2 = {  CGTY_UINT_2,       2,      0 };
static type_def TInt2  = {  CGTY_INT_2,        2,      TYPE_SIGNED };
static type_def TUInt4 = {  CGTY_UINT_4,       4,      0 };
static type_def TInt4  = {  CGTY_INT_4,        4,      TYPE_SIGNED };
static type_def TUInt8 = {  CGTY_UINT_8,       8,      0 };
static type_def TInt8  = {  CGTY_INT_8,        8,      TYPE_SIGNED };
extern type_def TNearCP;
extern type_def TLongCP;
extern type_def THugeCP;
extern type_def TNearP;
extern type_def TLongP;
extern type_def THugeP;
static type_def TSingle     = { CGTY_SINGLE,      4,      TYPE_SIGNED + TYPE_FLOAT };
static type_def TDouble     = { CGTY_DOUBLE,      8,      TYPE_SIGNED + TYPE_FLOAT };
static type_def TLongDouble = { CGTY_LONG_DOUBLE, 10,     TYPE_SIGNED + TYPE_FLOAT };
static type_def TBool       = { CGTY_BOOLEAN,     0,      0 };
static type_def TNull       = { CGTY_DEFAULT,     0,      0 };
static type_def TPascal     = { CGTY_PROC_PARM,   4,      0 };

type_def *PTInteger;
type_def *PTUnsigned;
type_def *PTPointer;
type_def *PTCodePointer;

extern  void    InitTyping() {
/*****************************
    initialize our typeing system
*/

    TypeList = NULL;
}


extern  type_def        *TypeAddress( cg_type tipe ) {
/*****************************************************
    given a type refno, "tipe" which is known to the front end, return a
    pointer to the appropriate "type_def".
*/

    type_list   *list;

    switch( tipe ) {

    case CGTY_UINT_1:
        return( &TUInt1 );
    case CGTY_INT_1:
        return( &TInt1 );
    case CGTY_UINT_2:
        return( &TUInt2 );
    case CGTY_INT_2:
        return( &TInt2 );
    case CGTY_UINT_4:
        return( &TUInt4 );
    case CGTY_INT_4:
        return( &TInt4 );
    case CGTY_UINT_8:
        return( &TUInt8 );
    case CGTY_INT_8:
        return( &TInt8 );
    case CGTY_NEAR_CODE_PTR:
        return( &TNearCP );
    case CGTY_LONG_CODE_PTR:
        return( &TLongCP );
    case CGTY_NEAR_POINTER:
        return( &TNearP );
    case CGTY_LONG_POINTER:
        return( &TLongP );
    case CGTY_HUGE_POINTER:
        return( &THugeP );
    case CGTY_SINGLE:
        return( &TSingle );
    case CGTY_DOUBLE:
        return( &TDouble );
    case CGTY_LONG_DOUBLE:
        return( &TLongDouble );
    case CGTY_BOOLEAN:
        return( &TBool );
    case CGTY_DEFAULT:
        return( &TNull );
    case CGTY_PROC_PARM:
        return( &TPascal );
    case CGTY_INTEGER:
        return( PTInteger );
    case CGTY_UNSIGNED:
        return( PTUnsigned );
    case CGTY_POINTER:
        return( PTPointer );
    case CGTY_CODE_PTR:
        return( PTCodePointer );
    default:
        list = TypeList;
        while( list != NULL ) {
            if( list->format == TYPE_DEFINITION ) {
                if( list->tipe.type_def.refno == tipe ) {
                    return( &list->tipe.type_def );
                }
            } else {/* TYPE_ALIAS*/
                if( list->tipe.alias.refno == tipe ) {
                    return( list->tipe.alias.tptr );
                }
            }

            list = list->link;
        }
        return( NULL );
    }
}


extern  type_length     TypeLength( cg_type tipe ) {
/***************************************************
    Return the size of a given type "tipe".
*/

    type_def    *t;

    t = TypeAddress( tipe );
    return( t->length );
}


extern  type_def        *TypeAlias( cg_type define, cg_type existing ) {
/***********************************************************************
    cause refno "define" to become an alias for existing type "existing"
*/

    type_def    *t;
    type_list   *list;

    t = TypeAddress( existing );
    if( t->refno == CGTY_DEFAULT ) return( t );
    list = CGAlloc( sizeof( type_list ) );
    list->link = TypeList;
    TypeList = list;
    list->format = TYPE_ALIAS;
    list->tipe.alias.refno = define;
    list->tipe.alias.tptr  = t;
    return( t );
}


extern  type_def        *TypeDef( cg_type refno, type_length length, type_length align ) {
/*****************************************************************************************
    Define a structure/array type which will have handle "refno".  The
    type will occupy "length" bytes of storage.
*/

    type_list   *list;

    align = align;
    list = CGAlloc( sizeof( type_list ) );
    list->link = TypeList;
    TypeList = list;
    list->format = TYPE_DEFINITION;
    list->tipe.type_def.refno  =  refno;
    list->tipe.type_def.length = length;
    list->tipe.type_def.attr   = 0;
#if _TARGET & _TARG_RISC
    list->tipe.type_def.align  = align;
#endif
    return( &list->tipe.type_def );
}


extern  void    TypeFini() {
/***************************
    Finish up the typeing stuff
*/

    type_list   *junk;
    type_list   *next;

    next = TypeList;
    while( next != NULL ) {
        junk = next;
        next = next->link;
        CGFree( junk );
    }
}
