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
;* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
;*               DESCRIBE IT HERE!
;*
;*****************************************************************************


;<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
;<>
;<> The following 25 routines are all X ** Y routines, where X and Y take
;<> on all the different numeric types.
;<>
;<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

.8087

include fcdef.inc
include errcod.inc
include stword.inc

        rtxref  PowII
        rtxref  PowRI
        rtxref  PowXI
        rtxref  PowRR
        ifxref  C16Pow
        ifxref  C32Pow

        fmodstart       fcexp

        dataseg

        math_rtn        dw      2 dup(?)

        enddata

;
; Compute y**x for integer exponent.
;


fcode   II_EXP
        pop     AX
        pop     DX
        pop     BX
        pop     CX
        exit_fcode                      ; switch to run-time environment
        docall  PowII
        enter_fcode                     ; switch to F-Code environment
        push    DX
        push    AX
        next
efcode  II_EXP


fcode   RI_EXP
dfcode  DI_EXP
dfcode  EI_EXP
        exit_fcode_fpu  1               ; exit F-Code environment
        pop     ax                      ; load exponent
        pop     dx                      ; ...
        mov     di,offset PowRI         ; routine to call
        mov     bp,seg PowRI            ; ...
;;;;;;;;hop rt_call
efcode  RI_EXP


defn    rt_call
        mov     ss:math_rtn,di          ; do the exponentiation
        mov     ss:math_rtn+2,bp        ; ...
        call    dword ptr SS:math_rtn   ; ...
        enter_fcode_fpu                 ; switch to F-Code environment
        next
endproc rt_call


fcode   IR_EXP
dfcode  ID_EXP
dfcode  IE_EXP
        exit_fcode_fpu  1               ; exit F-Code environment
        mov     bp,sp                   ; get stack frame
        fild    dword ptr [bp]          ; load the base
        mov     di,offset PowRR         ; offset of run time routine
        mov     bp,seg PowRR            ; ...
        _fwait                          ; wait for fpu to finish
        add     sp,4                    ; pop arg from stack
        hop     rt_call                 ; perform the call
efcode  IR_EXP


fcode   RR_EXP                          ; y   x
dfcode  RD_EXP
dfcode  RE_EXP
dfcode  DR_EXP
dfcode  DD_EXP
dfcode  DE_EXP
dfcode  ER_EXP
dfcode  ED_EXP
dfcode  EE_EXP
        exit_fcode_fpu  2               ; exit F-Code environment
        mov     di,offset PowRR         ; offset of run time routine
        mov     bp,seg PowRR            ; ...
        hop     rt_call                 ; perform the call
efcode  RR_EXP


fcode   IC_EXP
dfcode  IQ_EXP
dfcode  IX_EXP
        mov     bp,sp                   ; get stack frame
        fldz                            ; 0  a  b
        sub     sp,16-4                 ; allocate more temps on the stack
        fild    dword ptr [bp]          ; s  0  a  b
        add     bp,4                    ; point bp at right place for CC_EXP
        hop     ic_entry
efcode  IC_EXP


fcode   RC_EXP                          ; s  a  b
dfcode  RQ_EXP
dfcode  RX_EXP
dfcode  DC_EXP
dfcode  DQ_EXP
dfcode  DX_EXP
dfcode  EC_EXP
dfcode  EQ_EXP
dfcode  EX_EXP
        fldz                            ; 0  s  a  b
        fxch                            ; s  0  a  b
        hop    CC_EXP
efcode  RC_EXP


fcode   CI_EXP
dfcode  QI_EXP
dfcode  XI_EXP
        fldz                            ; 0   a   b
        mov     bp,sp                   ; get stack frame
        fxch    ST(2)                   ; b   a   0
        sub     sp,16-4                 ; allocate more temporaries
        fild    dword ptr [bp]          ; s   b   a   0
        add     bp,4                    ; point bp at right place for CC_EXP
        fxch    ST(2)                   ; a   b   s   0
        hop     ci_entry
efcode  CI_EXP


fcode   CR_EXP                          ; a   b   s
dfcode  QR_EXP
dfcode  XR_EXP
dfcode  CD_EXP
dfcode  QD_EXP
dfcode  XD_EXP
dfcode  CE_EXP
dfcode  QE_EXP
dfcode  XE_EXP
        fldz                            ; 0   a   b   s
        fxch    ST(3)                   ; s   a   b   0
        fxch    ST(2)                   ; b   a   s   0
        fxch                            ; a   b   s   0
;;;;;;;;hop     CC_EXP
efcode  CR_EXP


fcode   CC_EXP
dfcode  CQ_EXP
dfcode  CX_EXP
dfcode  QC_EXP
dfcode  QQ_EXP                          ; z   w
dfcode  QX_EXP                          ; z   w
dfcode  XC_EXP
dfcode  XQ_EXP                          ; z   w
dfcode  XX_EXP                          ; z   w
        mov     BP,SP                   ; setup stack frame
        sub     SP,16                   ; ...
ic_entry:
ci_entry:
        mov     di,si                   ; save f-code ptr
        lea     si,-16[BP]              ; return value offset
        exit_fcode                      ; switch to run-time environ
        docall  C16Pow                  ; do the exponentiation
        enter_fcode_fpu                 ; switch to fcode environ
        fld     qword ptr -8[BP]        ; load imag part of result
        mov     si,di                   ; restore f-code ptr
        fld     qword ptr -16[BP]       ;load real part of result
        next    0,1                     ; deallocate temps and continue
efcode  CC_EXP

        fmodend
        end
