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
* Description:  compile-time symbols type constant tables data
*
****************************************************************************/


//       id              keyword         size    ptype
pick( TY_NO_TYPE,       "",                  0,  PT_NOTYPE  )  // no type specified == PT_NO_TYPE
pick( TY_LOGICAL_1,     "LOGICAL*1",         1,  PT_LOG_1   )  // 0 LOGICAL*1
pick( TY_LOGICAL_2,     "LOGICAL*2",         2,  PT_LOG_2   )  // 1 LOGICAL*2
pick( TY_LOGICAL,       "LOGICAL",           4,  PT_LOG_4   )  // 2 LOGICAL*4
pick( TY_LOGICAL_8,     "LOGICAL*8",         8,  PT_LOG_8   )  // 3 LOGICAL*8
pick( TY_INTEGER_1,     "INTEGER*1",         1,  PT_INT_1   )  // 4 INTEGER*1
pick( TY_INTEGER_2,     "INTEGER*2",         2,  PT_INT_2   )  // 5 INTEGER*2
pick( TY_INTEGER,       "INTEGER",           4,  PT_INT_4   )  // 6 INTEGER*4
pick( TY_INTEGER_8,     "INTEGER*8",         8,  PT_INT_8   )  // 7 INTEGER*8
pick( TY_REAL,          "REAL",              4,  PT_REAL_4  )  // 8 REAL
pick( TY_DOUBLE,        "DOUBLEPRECISION",   8,  PT_REAL_8  )  // 9 DOUBLE PRECISION
pick( TY_TRUE_EXTENDED, "EXTENDEDPRECISION", 16, PT_REAL_16 )  // 10 EXTENDED PRECISION
pick( TY_COMPLEX,       "COMPLEX",           8,  PT_CPLX_8  )  // 11 COMPLEX
pick( TY_DCOMPLEX,      "DOUBLECOMPLEX",     16, PT_CPLX_16 )  // 12 DOUBLE COMPLEX
pick( TY_TRUE_XCOMPLEX, "EXTENDEDCOMPLEX",   32, PT_CPLX_32 )  // 13 EXTENDED COMPLEX
pick( TY_CHAR,          "CHARACTER",         1,  PT_CHAR    )  // 14 CHARACTER
pick( TY_STRUCTURE,     "STRUCTURE",         0,  PT_STRUCT  )  // 15 structure
pick( TY_UNION,         "",                  0,  PT_NOTYPE  )  // 16 union
pick( TY_HEX,           "",                  0,  PT_NOTYPE  )  // 17 z constants in DATA statements
