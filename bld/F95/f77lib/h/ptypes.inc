;*****************************************************************************
;*
;*                            Open Watcom Project
;*
;*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
;*
;*  ========================================================================
;*
;*    This file contains Original Code and/or Modifications of Original
;*    Code as defined in and that are subject to the Sybase Open Watcom
;*    Public License version 1.0 (the 'License'). You may not use this file
;*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
;*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
;*    provided with the Original Code and Modifications, and is also
;*    available at www.sybase.com/developer/opensource.
;*
;*    The Original Code and all software distributed under the License are
;*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
;*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
;*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
;*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
;*    NON-INFRINGEMENT. Please see the License for the specific language
;*    governing rights and limitations under the License.
;*
;*  ========================================================================
;*
;* Description:  Run and compile-time constants indicating parameter type
;*               and attributes
;*
;*****************************************************************************

;/**************** IMPORTANT NOTE *******************************
;
;  data in files:  ptypes.inc, ptypes.h and ptypdefn.h 
;  
;  must corespond each to other
;
;****************************************************************/


PT_NOTYPE       equ 0            ; no type
PT_LOG_1        equ 1            ; logical*1
PT_LOG_2        equ 2            ; logical*2
PT_LOG_4        equ 3            ; logical*4
PT_LOG_8        equ 4            ; logical*8
PT_INT_1        equ 5            ; integer*1
PT_INT_2        equ 6            ; integer*2
PT_INT_4        equ 7            ; integer*4
PT_INT_8        equ 8            ; integer*8
PT_REAL_4       equ 9            ; real*4
PT_REAL_8       equ 10           ; real*8
PT_REAL_16      equ 11           ; real*16
PT_CPLX_8       equ 12           ; complex*8
PT_CPLX_16      equ 13           ; complex*16
PT_CPLX_32      equ 14           ; complex*32
PT_CHAR         equ 15           ; character
PT_STRUCT       equ 16           ; structure
PT_ARRAY        equ 17           ; array
