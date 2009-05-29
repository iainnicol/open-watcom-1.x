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

        extrn   _edata                  : byte  ; end of DATA (start of BSS)
        extrn   _end                    : byte  ; end of BSS (start of STACK)

        extrn   ___begtext              : near

        assume  nothing

_TEXT   segment use32 word public 'CODE'

        assume  cs:_TEXT
        assume  ds:_DATA
        assume  fs:_DATA
        assume  gs:_DATA
        assume  ss:_DATA

public _cstart_

_cstart_ proc  far
        sub     ebp,ebp                 ; ebp=0 indicate end of ebp chain
        call    __RdosMain
        dd      ___begtext              ; make sure dead code elimination
;
; copyright message
;
include msgrt32.inc
include msgcpyrt.inc

_cstart_ endp

_TEXT   ends

        end     _cstart_
