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
;* Description:  Startup code for RDOS, 32-bit usermode application.
;*
;*****************************************************************************

        name    cstart

.387
.386p

include xinit.inc

        assume  nothing

        extrn   __RdosMain              : near
        extrn   __FiniRtns              : near
        extrn   exit_                   : near

        extrn   _edata                  : byte  ; end of DATA (start of BSS)
        extrn   _end                    : byte  ; end of BSS (start of STACK)


DGROUP group CONST,_DATA,DATA,TIB,TI,TIE,XIB,XI,XIE,YIB,YI,YIE,_BSS,STACK

        assume  nothing

; this guarantees that no function pointer will equal NULL
; (WLINK will keep segment 'BEGTEXT' in front)
; This segment must be at least 4 bytes in size to avoid confusing the
; signal function.

BEGTEXT segment use32 word public 'CODE'
        assume  cs:BEGTEXT
forever label   near
        int     3h
        jmp     short forever
___begtext label byte
        nop
        nop
        nop
        nop
        public ___begtext
        assume  cs:nothing
BEGTEXT ends

_TEXT   segment use32 word public 'CODE'

CONST   segment word public 'DATA'
CONST   ends

TIB     segment byte public 'DATA'
TIB     ends
TI      segment byte public 'DATA'
TI      ends
TIE     segment byte public 'DATA'
TIE     ends

XIB     segment word public 'DATA'
XIB     ends
XI      segment word public 'DATA'
XI      ends
XIE     segment word public 'DATA'
XIE     ends

YIB     segment word public 'DATA'
YIB     ends
YI      segment word public 'DATA'
YI      ends
YIE     segment word public 'DATA'
YIE     ends

_DATA   segment use32 word public 'DATA'
_DATA   ends

DATA    segment word public 'DATA'
DATA    ends

_BSS          segment word public 'BSS'
_BSS          ends

STACK_SIZE      equ     10000h

STACK   segment para stack 'STACK'
stlow   db      (STACK_SIZE) dup(?)
STACK   ends

        assume  cs:_TEXT
        assume  ds:_DATA
        assume  fs:_DATA
        assume  gs:_DATA
        assume  ss:_DATA

public _cstart_

_cstart_ proc  far
        lea     ecx,_end                ; end of _BSS segment (start of free)
        lea     edi,_edata              ; start of _BSS segment
        sub     ecx,edi                 ; calc # of bytes in _BSS segment
        xor     eax,eax                 ; zero the _BSS segment
        mov     dl,cl                   ; copy the lower bits of size
        shr     ecx,2                   ; get number of dwords
        rep     stosd                   ; copy them
        mov     cl,dl                   ; get lower bits
        and     cl,3                    ; get number of bytes left (modulo 4)
        rep     stosb

        sub     ebp,ebp                 ; ebp=0 indicate end of ebp chain
        call    __RdosMain

        jmp     exit_                   ; exit
        dd      ___begtext              ; make sure dead code elimination
_cstart_ endp


_TEXT   ends

        end     _cstart_
