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
* Description:  Assmebler symbols internal structures and definitions.
*
****************************************************************************/


#ifndef _ASMSYM_H_
#define _ASMSYM_H_

#include "asminlin.h"
#include "asmops2.h"

typedef enum {
        MT_BYTE   = T_BYTE,
        MT_WORD   = T_WORD,
        MT_DWORD  = T_DWORD,
        MT_QWORD  = T_QWORD,
        MT_FWORD  = T_FWORD,
        MT_TBYTE  = T_TBYTE,
        MT_OWORD  = T_OWORD,

        MT_SHORT  = T_SHORT,
        MT_NEAR   = T_NEAR,
        MT_FAR    = T_FAR,

        MT_PTR    = T_PTR,

#ifdef _WASM_
        MT_SBYTE  = T_SBYTE,
        MT_SWORD  = T_SWORD,
        MT_SDWORD = T_SDWORD,

        MT_STRUCT = T_STRUCT,

        MT_PROC   = T_PROC,
        MT_ABS    = T_ABS
#endif
} memtype;

typedef struct asm_sym {
        struct asm_sym  *next;
        char            *name;

#ifdef _WASM_
        struct asm_sym  *segment;
        uint_32         offset;
        uint_32         first_size;   /* size of 1st initializer in bytes */
        uint_32         first_length; /* size of 1st initializer--elts. dup'd */
        uint_32         total_size;   /* total number of bytes (sizeof) */
        uint_32         total_length; /* total number of elements (lengthof) */
        char            *(*mangler)( struct asm_sym *sym, char *buffer );
        unsigned        public:1;
        unsigned        langtype:3;
#else
        long            addr;
#endif
        memtype         mem_type;
        enum sym_state  state;
        struct asmfixup *fixup;
} asm_sym;

extern struct asm_sym *AsmLookup( char *name );
extern struct asm_sym *AsmGetSymbol( char *name );

#ifdef _WASM_

extern void AsmTakeOut( char *name );
extern int AsmChangeName( char *old, char *new );

extern struct asm_sym *AllocDSym( char *, int );

#define IS_SYM_COUNTER( x ) ( ( x[0] == '$' ) && ( x[1] == 0 ) )

#endif

#endif
