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


include graph.inc

        xref    BitCopy
        xref    BitReplace
        xref    BitAnd
        xref    BitOr
        xref    BitXor

        extrn   __GRCGPort : word
        extrn   __CurrColor : word
        extrn   __PlotAct : word
        extrn   __Transparent : word

        modstart necutils

        xdefp   _NECSet_
        xdefp   _NECReset_
        xdefp   _NECByteRep_
        xdefp   _NECByteXor_
        xdefp   _NECByteAnd_
        xdefp   _NECByteOr_
        xdefp   _NECRep_
        xdefp   _NECXor_
        xdefp   _NECAnd_
        xdefp   _NECOr_
        xdefp   _NECGetDot_
        xdefp   _NECPixZap_
        xdefp   _NECPixFill_
        xdefp   _NECPixCopy_
        xdefp   _NECPixRead_
        xdefp   _NEC16Xor_
        xdefp   _NEC16And_
        xdefp   _NEC16Or_
        xdefp   _NEC16GetDot_
        xdefp   _NEC16PixZap_
        xdefp   _NEC16PixFill_
        xdefp   _NEC16PixCopy_
        xdefp   _NEC16PixRead_
        xdefp   _NEC1120MoveUp_
        xdefp   _NEC1120MoveDown_
        xdefp   _NEC1120MoveLeft_
        xdefp   _NEC1120MoveRight_
        xdefp   _NEC1120Xor_
        xdefp   _NEC1120Or_
        xdefp   _NEC1120And_
        xdefp   _NEC1120Zap_
        xdefp   _NEC1120Fill_
        xdefp   _NEC1120GetDot_
        xdefp   _NEC1120Copy_
        xdefp   _NEC1120Read_
        xdefp   _NECMoveDown_
        xdefp   _NECMoveUp_
        xdefp   _NECMoveDown_
        xdefp   _NECMoveLeft_
        xdefp   _NECMoveRight_
        xdefp   _NECScanLeft_
        xdefp   _NECScanRight_

Planetable db   0Eh, 01Dh, 02Bh, 037h

ifdef _386
Segtable dd     0, 08000h, 010000h, 038000h
else
Segtable dw     0A800h, 0B000h, 0B800h, 0E000h
endif

StartPlot macro
ifdef _386
        push    _edi
else
        push    es
        push    si
endif
        endm

EndPlot macro
ifdef _386
        pop     _edi
else
        pop     si
        pop     es
endif
        endm

NextPlane macro p16,p32
ifdef _386
        add     _edi,p32
else
        mov     si,p16
        mov     es,si
endif
        endm

DGROUP  group _DATA
assume  ds:DGROUP,ss:DGROUP
_DATA   segment word public 'DATA'
_ChargerOn  db  0
_DATA   ends

;=========================================================================
;
;   Charger On function
;
;   Input       AH          colour
;               AL          port #
;
;   Charger Off Function
;
;   Input       NONE
;
;=========================================================================

_TurnChargerOn:
        push    _edx

        mov     dx, word ptr ss:__GRCGPort   ; set graphics charger port
        out     dx, al              ; select RWM mode

        inc     dx                  ; set fill colour
        inc     dx
        shr     ah, 1               ; - get next bit
        sbb     al, al              ; - create 0x00 or 0xff mask on bit val
        out     dx, al              ; - out mask

        shr     ah, 1               ; - get next bit
        sbb     al, al              ; - create 0x00 or 0xff mask on bit val
        out     dx, al              ; - out mask

        shr     ah, 1               ; - get next bit
        sbb     al, al              ; - create 0x00 or 0xff mask on bit val
        out     dx, al              ; - out mask

        shr     ah, 1               ; - get next bit
        sbb     al, al              ; - create 0x00 or 0xff mask on bit val
        out     dx, al              ; - out mask

        mov     byte ptr ss:_ChargerOn,1

        pop     _edx
        ret

_TurnChargerOff:
        push    _eax
        push    _edx

        mov     dx, word ptr ss:__GRCGPort ; Turn off graphics charger
        xor     al, al                     ; . . .
        out     dx, al                     ; . . .

        mov     byte ptr ss:_ChargerOn,0

        pop     _edx
        pop     _eax
        ret

;=========================================================================
;
;   NEC Set and Reset functions
;
;   Input       NONE
;
;
;=========================================================================

_NECSet_:
        cmp     word ptr ss:__PlotAct, 0       ; if rep mode
        _if     e
          push    _eax
          mov     al, 0c0h                     ; select RWM mode
          mov     ah, byte ptr ss:__CurrColor  ; select colour
          call    _TurnChargerOn
          pop     _eax
        _endif
        ret


_NECReset_:
        cmp     word ptr ss:__PlotAct, 0    ; if graphics charger is on
        _if     e
          call    _TurnChargerOff            ; turn off charger
        _endif
        ret

;=========================================================================
;
;   Plotting primitives
;
;   Input       ES:_EDI      screen memory
;               AL          colour
;               CH          mask  (CL contains complement of mask)
;
;
;=========================================================================
_NECByteXor_:
        xor     es:[_edi],al     ; replace byte
        ret

_NECByteOr_:
        or      es:[_edi],al     ; replace byte
        ret

_NECByteAnd_:
        or      al,ch           ; mask on other bits
        and     es:0[_edi],al    ; do and with memory
        xor     al,ch           ; restore al
        ret

_NECByteRep_:
        mov     ah,es:[_edi]     ; get current byte
        and     ah,ch           ; mask out current colour
        or      ah,al           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte
        ret

        db      E_NECXor-_NECXor_
_NECXor_:                       ; xor in new pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _ebx             ; restore registers
        EndPlot
E_NECXor:
        ret

        db      E_NECAnd-_NECAnd_
_NECAnd_:                       ; and in new pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        pop     _ebx             ; . . .
        EndPlot
E_NECAnd:
        ret

        db      E_NECRep-_NECRep_
_NECRep_:                       ; replace pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        and     ah,ch           ; mask out current colour
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

;       NextPlane 0B800h, 010000h
        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        and     ah,ch           ; mask out current colour
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

;       NextPlane 0B000h, -08000h
        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        and     ah,ch           ; mask out current colour
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _ebx             ; . . .
        EndPlot
E_NECRep:
        ret

        db      E_NECOr-_NECOr_
_NECOr_:                        ; or in new pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _ebx             ; . . .
        EndPlot
E_NECOr:
        ret

        db      E_NEC16Xor-_NEC16Xor_
_NEC16Xor_:                     ; xor in new pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0E000h, 028000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _ebx             ; . . .
        EndPlot
E_NEC16Xor:
        ret

        db      E_NEC16And-_NEC16And_
_NEC16And_:                       ; and in new pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        NextPlane 0E000h, 028000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; keep other pixels
        and     es:[_edi],bl     ; AND in new colour

        pop     _ebx             ; . . .
        EndPlot
E_NEC16And:
        ret

        db      E_NEC16Or-_NEC16Or_
_NEC16Or_:                      ; or in new pixel
        StartPlot
        push    _ebx             ; . . .
        mov     bh,al           ; copy colour into bh

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B000h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0B800h, 08000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        NextPlane 0E000h, 028000h

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _ebx             ; . . .
        EndPlot
E_NEC16Or:
        ret

        db      E_NEC1120Xor-_NEC1120Xor_
_NEC1120Xor_:                   ; xor in new pixel
        push    _eax
        push    _ebx
        push    _edx

        mov     bh, al          ; copy colour into bh

        mov     dx, 0a4h        ; select plane 0
        mov     al, 0eh         ; . . .
        out     dx, al          ; . . .

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        mov     al, 1dh         ; Select plane 1
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        mov     al, 2bh         ; Select plane 2
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        mov     al, 37h         ; Select plane 3
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        xor     ah,bl           ; XOR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _edx
        pop     _ebx
        pop     _eax
E_NEC1120Xor:
        ret

        db      E_NEC1120Or-_NEC1120Or_
_NEC1120Or_:                   ; xor in new pixel
        push    _eax
        push    _ebx
        push    _edx

        mov     bh, al          ; copy colour into bh

        mov     dx, 0a4h        ; select plane 0
        mov     al, 0eh         ; . . .
        out     dx, al          ; . . .

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        and     bl,cl           ; and with ~mask to get colour bit

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        mov     al, 1dh         ; Select plane 1
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        mov     al, 2bh         ; Select plane 2
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        mov     al, 37h         ; Select plane 3
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        and     bl,cl           ; . . .

        mov     ah,es:[_edi]     ; get current byte
        or      ah,bl           ; OR in new colour
        mov     es:[_edi],ah     ; replace byte

        pop     _edx
        pop     _ebx
        pop     _eax
E_NEC1120Or:
        ret

        db      E_NEC1120And-_NEC1120And_
_NEC1120And_:                   ; xor in new pixel
        push    _eax
        push    _ebx
        push    _edx

        mov     bh, al          ; copy colour into bh

        mov     dx, 0a4h        ; select plane 0
        mov     al, 0eh         ; . . .
        out     dx, al          ; . . .

        shr     bh,1            ; get 1st bit of colour into carry
        sbb     bl,bl           ; get 0x00 or 0xff into bl
        or      bl,ch           ; or with mask

        and     es:[_edi], bl    ; AND in colour

        mov     al, 1dh         ; Select plane 1
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; or with mask

        and     es:[_edi], bl    ; AND in colour

        mov     al, 2bh         ; Select plane 2
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; or with mask

        and     es:[_edi], bl    ; AND in colour

        mov     al, 37h         ; Select plane 3
        out     dx, al          ; . . .

        shr     bh,1            ; get next bit
        sbb     bl,bl           ; . . .
        or      bl,ch           ; or with mask

        and     es:[_edi], bl    ; AND in colour

        pop     _edx
        pop     _ebx
        pop     _eax
E_NEC1120And:
        ret

;=========================================================================
;
;   Movement primitives
;
;   Input       ES:_EDI      screen memory
;               AL          colour
;               CH          mask    (CL is ~mask for 8 colour modes)
;
;   Output      same        altered as per move
;
;=========================================================================

        db      E_NECMoveRight-_NECMoveRight_
_NECMoveRight_:                 ; move right in high-res mode
        ror     cl,1            ; shift ~mask to the right
        ror     ch,1            ; shift mask to the right
        sbb     _edi,-1          ; move to next byte if it is time
E_NECMoveRight:
        ret                     ; return

        db      E_NECMoveLeft-_NECMoveLeft_
_NECMoveLeft_:                  ; move left in high-res mode
        rol     cl,1            ; shift ~mask to the left
        rol     ch,1            ; shift mask to the left
        adc     _edi,-1          ; move to next byte if it is time
E_NECMoveLeft:
        ret                     ; return

        db      E_NECMoveUp-_NECMoveUp_
_NECMoveUp_:                    ; move up 1 dot
        sub     _edi,80          ;
E_NECMoveUp:
        ret                     ; return

        db      E_NECMoveDown-_NECMoveDown_
_NECMoveDown_:                  ; move down 1 dot
        add     _edi,80          ;
E_NECMoveDown:
        ret                     ; return

        db      E_NEC1120MoveUp-_NEC1120MoveUp_
_NEC1120MoveUp_:
        sub     _edi,140         ; move up 1 dot
ifndef _386
        _if     s               ; adjust segment
          push    si
          add     di,8000h
          mov     si,es
          sub     si,0800h
          mov     es,si
          pop     si
        _endif
endif
E_NEC1120MoveUp:
        ret                     ; return

        db      E_NEC1120MoveDown-_NEC1120MoveDown_
_NEC1120MoveDown_:              ; move down 1 dot
        add     _edi,140         ;
ifndef _386
        _if     s               ; adjust segment
          push    si
          sub     di,8000h
          mov     si,es
          add     si,0800h
          mov     es,si
          pop     si
        _endif
endif
E_NEC1120MoveDown:
        ret                     ; return

        db      E_NEC1120MoveRight-_NEC1120MoveRight_
_NEC1120MoveRight_:                 ; move right in high-res mode
        ror     cl,1            ; shift ~mask to the right
        ror     ch,1            ; shift mask to the right
        sbb     _edi,-1          ; move to next byte if it is time
ifndef _386
        _if     s               ; adjust segment
          push    si
          sub     di,8000h
          mov     si,es
          add     si,0800h
          mov     es,si
          pop     si
        _endif
endif
E_NEC1120MoveRight:
        ret                     ; return

        db      E_NEC1120MoveLeft-_NEC1120MoveLeft_
_NEC1120MoveLeft_:                  ; move left in high-res mode
        rol     cl,1            ; shift ~mask to the left
        rol     ch,1            ; shift mask to the left
        adc     _edi,-1          ; move to next byte if it is time
ifndef _386
        _if     s               ; adjust segment
          push    si
          add     di,8000h
          mov     si,es
          sub     si,0800h
          mov     es,si
          pop     si
        _endif
endif
E_NEC1120MoveLeft:
        ret                     ; return

;=========================================================================
;
;   GetDot routines
;
;   Input       ES:_EDI      screen memory
;               CL          bit position
;
;   Output      AX          colour of pixel at location
;
;=========================================================================

_NECGetDot_:
        StartPlot
        push    _ebx             ; . . .
        sub     cl,7            ; shift byte by ( 7 - bit offset )
        neg     cl              ; . . .
        mov     al,es:[_edi]     ; get byte from first bit plane
        shr     al,cl           ; put in first position
        and     al,1            ; clear other bits

        NextPlane 0B000h, 08000h

        mov     ah,es:[_edi]     ; get byte from other plane
        shr     ah,cl           ; put in first position
        and     ah,1            ; clear other bits
        shl     ah,1            ; put in proper position
        or      al,ah           ; place in proper byte

        NextPlane 0B800h, 08000h

        mov     ah,es:[_edi]     ; get byte from other plane
        shr     ah,cl           ; put in first position
        and     ah,1            ; clear other bits
        shl     ah,1            ; put in proper position
        shl     ah,1            ; . . .
        or      al,ah           ; place in proper byte

        xor     ah,ah           ; clear high bits
        pop     _ebx             ; restore registers
        EndPlot
        ret

_NEC16GetDot_:
        StartPlot
        push    _ebx             ; . . .
        sub     cl,7            ; shift byte by ( 7 - bit offset )
        neg     cl              ; . . .
        mov     al,es:[_edi]     ; get byte from first bit plane
        shr     al,cl           ; put in first position
        and     al,1            ; clear other bits

        NextPlane 0B000h, 08000h

        mov     ah,es:[_edi]     ; get byte from other plane
        shr     ah,cl           ; put in first position
        and     ah,1            ; clear other bits
        shl     ah,1            ; put in proper position
        or      al,ah           ; place in proper byte

        NextPlane 0B800h, 08000h

        mov     ah,es:[_edi]     ; get byte from other plane
        shr     ah,cl           ; put in first position
        and     ah,1            ; clear other bits
        shl     ah,1            ; put in proper position
        shl     ah,1            ; . . .
        or      al,ah           ; place in proper byte

        NextPlane 0E000h, 028000h

        mov     ah,es:[_edi]     ; get byte from other plane
        shr     ah,cl           ; put in first position
        and     ah,1            ; clear other bits
        shl     ah,1            ; put in proper position
        shl     ah,1            ; . . .
        shl     ah,1            ; . . .
        or      al,ah           ; place in proper byte

        xor     ah,ah           ; clear high bits
        pop     _ebx             ; restore registers
        EndPlot
        ret

_NEC1120GetDot_:
        push    _ebx
        push    _edx

        mov     dx, 0a4h        ; select 1st bit plane
        mov     al, 00eh        ; . . .
        out     dx, al          ; . . .

        sub     cl,7            ; shift byte by ( 7 - bit offset )
        neg     cl              ; . . .
        mov     bl,es:[_edi]     ; get byte from first bit plane
        shr     bl,cl           ; put in first position
        and     bl,1            ; clear other bits

        mov     al, 01dh        ; select 2nd bit plane
        out     dx, al          ; . . .

        mov     bh,es:[_edi]     ; get byte from other plane
        shr     bh,cl           ; put in first position
        and     bh,1            ; clear other bits
        shl     bh,1            ; put in proper position
        or      bl,bh           ; place in proper byte

        mov     al, 02bh        ; select 3rd bit plane
        out     dx, al          ; . . .

        mov     bh,es:[_edi]     ; get byte from other plane
        shr     bh,cl           ; put in first position
        and     bh,1            ; clear other bits
        shl     bh,1            ; put in proper position
        shl     bh,1            ; . . .
        or      bl,bh           ; place in proper byte

        mov     al, 037h        ; select 4th bit plane
        out     dx, al          ; . . .

        mov     bh,es:[_edi]     ; get byte from other plane
        shr     bh,cl           ; put in first position
        and     bh,1            ; clear other bits
        shl     bh,1            ; put in proper position
        shl     bh,1            ; . . .
        shl     bh,1            ; . . .
        or      bl,bh           ; place in proper byte

        xor     bh,bh           ; clear high bits
        mov     ax,bx           ; place value in ax

        pop     _edx
        pop     _ebx
        ret

;==========================================================================
        ifdef _386
PixJmp dd _NECByteRep_,_NECByteXor_,_NECByteAnd_,_NECByteOr_
        else
PixJmp dw _NECByteRep_,_NECByteXor_,_NECByteAnd_,_NECByteOr_
        endif
;==========================================================================
;
;   PixCopy routines
;
;   Input       ES:_EDI,DH   screen memory
;               SI:_EAX,DL   buffer to copy from
;               CX          number of pixels to copy
;
;=========================================================================

_NEC1120Copy_:
        push    ds
        mov     ds,si           ; get source in ds:si
        mov     _esi,_eax         ; have si point to src buffer
        mov     _eax,_ebx         ; save plane length
        docall  SetupAction     ; set the plotting action
        mov     _ebx, 3          ; start at bit plane 3
        _loop                   ; loop through the different planes
          push      _edi         ; - . . .

          push      _edx
          push      _eax
          mov       dx, 0a4h                ; set port #
          mov       al, cs:Planetable[_ebx]  ; select plane
          out       dx, al                  ; . . .
          pop       _eax
          pop       _edx

          push      _ebx         ; - save registers
          push      _eax         ; - . . .
          push      _edx         ; - . . .
          push      _ecx         ; - . . .
          push      _esi
          docall    BitCopy     ; - call to read the plane
          pop       _esi
          pop       _ecx         ; - restore registers
          pop       _edx         ; - . . .
          pop       _eax         ; - . . .
          pop       _ebx         ; - . . .

          pop       _edi         ; - . . .
          add       _esi,_eax     ; - move to next plane
          dec       _ebx         ; - update pointer to Planetable
        _until    l             ; endloop
        docall  BitReplace      ; set the plotting action to replace
        pop     ds
        ret

_NECPixCopy_:
        push    _ebp             ; save registers
        push    ds              ; . . .
        mov     ds,si           ; get source in ds:si
        mov     _esi,_eax         ; have si point to src buffer
        mov     _ebp,3           ; number of bit planes
        jmp     short pcopy_common

_NEC16PixCopy_:
        push    _ebp             ; save registers
        push    ds              ; . . .
        mov     ds,si           ; get source in ds:si
        mov     _esi,_eax         ; have si point to src buffer
        mov     _ebp,4           ; number of bit planes

pcopy_common:
        mov     _eax,_ebx         ; save plane length
        docall  SetupAction     ; set the plotting action
        xor     _ebx,_ebx         ; clear out register
        _loop                   ; loop through the different planes
          push      _edi         ; - . . .
ifdef _386
          add       _edi,cs:Segtable[_ebx*2];point to the new plane
else
          mov       es,cs:Segtable[bx]; point to the new plane to 'read'
endif
          push      _ebx         ; - save registers
          push      _eax         ; - . . .
          push      _edx         ; - . . .
          push      _ecx         ; - . . .
          push      _esi         ; - . . .
          docall    BitCopy     ; - call to read the plane
          pop       _esi         ; - restore registers
          pop       _ecx         ; - . . .
          pop       _edx         ; - . . .
          pop       _eax         ; - . . .
          pop       _ebx         ; - . . .
          pop       _edi         ; - . . .
          dec       _ebp         ; - decrement the counter
          _quif     e           ; - if equal to zero then quit
          add       _esi,_eax     ; - move to next plane
          inc       _ebx         ; - update pointer to Segtable
          inc       _ebx         ; - . . .
        _endloop                ; endloop
        docall  BitReplace      ; set the plotting action to replace
        pop     ds              ; restore registers
        pop     _ebp             ; . . .
        ret


;=========================================================================
;
;   ReadRow routines
;
;   Input       ES:_EDI      buffer to copy into
;               SI:_EAX,DL   screen memory
;               CX          number of pixels to copy
;
;=========================================================================

_NEC1120Read_:
        push    ds
        mov     ds,si           ; get source into ds:_esi
        mov     _esi,_eax         ; . . .
        mov     _ebx, 3          ; start on bit plane 3
        _loop                   ; loop through the different planes
          push      _esi         ; - . . .

          push      _edx
          mov       dx, 0a4h                ; set port #
          mov       al, cs:Planetable[_ebx]  ; select plane
          out       dx, al                  ; . . .
          pop       _edx

          push      _ebx         ; - save registers
          push      _eax         ; - . . .
          push      _edx         ; - . . .
          push      _ecx         ; - . . .
          docall    BitCopy     ; - call to read the plane
          pop       _ecx         ; - . . .
          pop       _edx         ; - . . .
          pop       _eax         ; - . . .
          pop       _ebx         ; - . . .

          pop       _esi         ; - restore registers
          dec       _ebx         ; - decrement the counter
        _until    l             ; endloop
        pop     ds
        ret

_NECPixRead_:
        push    ds              ; save registers
        mov     ds,si           ;
        mov     _esi,_eax         ; . . .
        mov     ah,3            ; start on bit plane 4
        jmp     short get_common; start getting

_NEC16PixRead_:
        push    ds              ; save registers
        mov     ds,si           ;
        mov     _esi,_eax         ; . . .
        mov     ah,4            ; start on bit plane 4

get_common:
        xor     _ebx,_ebx         ; clear out register
        _loop                   ; loop through the different planes
          push      _esi         ; - . . .
ifdef _386
          add       _esi,cs:Segtable[_ebx*2]; point to the new plane
else
          mov       ds,cs:Segtable[bx]; point to the new plane to 'read'
endif
          push      _ebx         ; - save registers
          push      _eax         ; - . . .
          push      _edx         ; - . . .
          push      _ecx         ; - . . .
          docall    BitCopy     ; - call to read the plane
          pop       _ecx         ; - . . .
          pop       _edx         ; - . . .
          pop       _eax         ; - . . .
          pop       _ebx         ; - . . .
          pop       _esi         ; - restore registers
          dec       ah          ; - decrement the counter
          _quif     e           ; - if equal to zero then quit
          inc       _ebx         ; - update pointer to Segtable
          inc       _ebx         ; - . . .
        _endloop                ; endloop
        pop     ds              ; . . .
        ret

;========================================================================
        ifdef _386
PlotJmp dd BitReplace,BitXor,BitAnd,BitOr
        else
PlotJmp dw BitReplace,BitXor,BitAnd,BitOr
        endif

SetupAction:
ifdef _386
        movzx   _ebx,word ptr ss:__PlotAct
        jmp     cs:PlotJmp[_ebx*4]
else
        mov     bx,ss:__PlotAct
        shl     bx,1
        jmp     cs:PlotJmp[bx]
endif
;=========================================================================

;=========================================================================

        ifdef _386
FillJmp     dd _NECRep_,_NECXor_,_NECAnd_,_NECOr_
Fill16Jmp   dd _NECRep_,_NEC16Xor_,_NEC16And_,_NEC16Or_
Fill1120Jmp dd _NECRep_,_NEC1120Xor_,_NEC1120And_,_NEC1120Or_
        else
FillJmp     dw _NECRep_,_NECXor_,_NECAnd_,_NECOr_
Fill16Jmp   dw _NECRep_,_NEC16Xor_,_NEC16And_,_NEC16Or_
Fill1120Jmp dw _NECRep_,_NEC1120Xor_,_NEC1120And_,_NEC1120Or_
        endif

LoadPlt macro   tab
ifdef _386
        movzx   _esi,word ptr ss:__PlotAct
        mov     _esi,cs:tab[_esi*4]
else                                ; load address of plot function
        mov     si,ss:__PlotAct
        shl     si,1
        mov     si,cs:tab[si]
endif
        endm

;=========================================================================
;
;   Zap routines
;
;   Input       ES:_EDI,DH   screen memory
;               AL          colour (unmasked)
;               BX          not used
;               CX          number of pixels to fill
;
;=========================================================================
;
;   Fill routines
;
;   Input       ES:_EDI,DH   screen memory
;               AL          colour (unmasked)
;               BH,BL       mask offset, fill mask
;               CX          number of pixels to fill
;
;==========================================================================

_NEC16PixFill_:
        push    _esi
        mov     dl, cl              ; save count
        mov     cl, dh              ; rotate mask
        sub     cl, bh              ; . . .
        ror     bl, cl              ; . . .
        mov     cl, dl              ; restore count
        cmp     word ptr ss:__Transparent,0
        _if     e                   ; if _Transparent == 0
          mov     bh,0ffh           ; - bit mask is ff (affect all bits)
        _else                       ; else
          mov     bh,bl             ; - bit mask is fill mask (affect only the mask bits)
        _endif                      ; endif
        LoadPlt Fill16Jmp           ; load address of plot function
        jmp     fill_common

_NECPixFill_:
        push    _esi
        mov     dl, cl              ; save count
        mov     cl, dh              ; rotate mask
        sub     cl, bh              ; . . .
        ror     bl, cl              ; . . .
        mov     cl, dl              ; restore count
        cmp     word ptr ss:__Transparent,0
        _if     e                   ; if _Transparent == 0
          mov     bh,0ffh           ; - bit mask is ff (affect all bits)
        _else                       ; else
          mov     bh,bl             ; - bit mask is fill mask (affect only the mask bits)
        _endif                      ; endif
        LoadPlt FillJmp             ; load address of plot function
        jmp     short fill_common

_NEC1120Fill_:
        push    _esi
        mov     dl, cl              ; save count
        mov     cl, dh              ; rotate mask
        sub     cl, bh              ; . . .
        ror     bl, cl              ; . . .
        mov     cl, dl              ; restore count
        cmp     word ptr ss:__Transparent,0
        _if     e                   ; if _Transparent == 0
          mov     bh,0ffh           ; - bit mask is ff (affect all bits)
        _else                       ; else
          mov     bh,bl             ; - bit mask is fill mask (affect only the mask bits)
        _endif                      ; endif
        LoadPlt Fill1120Jmp         ; load address of plot function
        jmp     short fill_common

_NEC16PixZap_:
        push    _esi
        mov     bl,0ffh             ; set fill mask
        mov     bh,bl               ; mask is ff (affect all bits)
        LoadPlt Fill16Jmp           ; load address of plot function
        jmp     short fill_common

_NECPixZap_:
        push    _esi
        mov     bl,0ffh             ; set fill mask
        mov     bh,bl               ; mask is ff (affect all bits)
        LoadPlt FillJmp             ; load address of plot function
        jmp     short fill_common

_NEC1120Zap_:
        push    _esi
        mov     bl,0ffh             ; set fill mask
        mov     bh,bl               ; mask is ff (affect all bits)
        LoadPlt Fill1120Jmp         ; load address of plot function

fill_common:
        push    _ebp

        mov     _ebp,_ecx             ; get count in bp

        or      dh,dh               ; if bit_pos != 0
        _if     ne                  ; (doesn't start on byte boundary)
          mov     cl,dh             ; - get bit_pos
          mov     ah,80h            ; - initial value of mask
          shr     ah,cl             ; - shift mask into position
          xor     ch,ch             ; - ch will be mask for wanted bits
          _loop                     ; - loop
            or      ch,ah           ; - - put bit in
            dec     _ebp             ; - - count--
            _quif   e               ; - - quif count == 0
            shr     ah,1            ; - - move to next bit
          _until    c               ; - until bit comes out
          mov     cl,bl             ; - give fill mask
          and     cl,ch             ; - keep only mask bits
          and     ch,bh             ; - keep only mask bits
          not     ch                ; - bit mask is complement
          call    _esi               ; - plot the pixels
          inc     _edi               ; - move to next byte
        _endif                      ; endif

        push    _ebx                 ; save register
        mov     ah,al               ; keep real colour

        mov     _edx,_ebp             ; get count
        shr     _edx,1               ; get byte count
        shr     _edx,1               ; . . .
        shr     _edx,1               ; . . .
        _if     ne                  ; if byte count != 0
          mov     ch,bh             ; - get mask
          mov     bh,cl             ; - save bit plane number
          mov     cl,bl             ; - get fill mask
          not     ch                ; - . . .

          _guess                    ; - guess (can use fast method)
            cmp     word ptr ss:__PlotAct,0
            _quif   ne              ; - - quif if its not replace mode
            or      ch,ch           ; - -
            _quif   ne              ; - - quif if the mask is not zero

            mov     _ecx,_edx         ; - - - use fast fill
            mov     al, 0ffh        ; - - - mask output mask
            and     al, bl          ; - - - mask bits
            rep     stosb           ; - - - fill buffer until( --count == 0 )

          _admit                    ; - admit (use slow method)
            _loop                   ; - - loop
              call    _esi           ; - - - plot byte
              inc     _edi           ; - - - move to next byte
              dec     _edx           ; - - - count--
              _quif   e             ; - - - quif count == 0
            _endloop                ; - - endloop

          _endguess                 ; - endguess
        _endif                      ; endif

        pop     _ebx                 ; restore registers
        and     _ebp,7               ; if bit count != 0
        _if     ne                  ; then
          mov     _ecx,8             ; - mask = ff << ( 8 - bit count )
          sub     _ecx,_ebp           ; - . . .
          mov     ch,0ffh           ; - ch will be mask for wanted bits
          shl     ch,cl             ; - . . .
          mov     ah,al             ; - get colour
          mov     cl,bl             ; - get fill mask
          and     cl,ch             ; - keep only wanted mask bits
          and     ch,bh             ; - keep only wanted mask bits
          not     ch                ; - bit mask is complement
          call    _esi               ; - plot the pixels
        _endif                      ; endif

        pop     _ebp
        pop     _esi
        ret

;=========================================================================
;
;   Scan routines
;
;   Input       ES:_EDI      screen memory
;               AL          colour
;               CH          mask (CL may be bits per pixel)
;               BX          starting x-coordinate
;               SI          ending x value (viewport boundary)
;               DL          0 if paint until colour, 1 if paint while
;
;   Output      BX          updated x-coordinate
;
;=========================================================================

_NECScanLeft_:
        mov     dh,_ChargerOn       ; remember whether graphics charger is on
        or      dh, dh
        _if     ne
          call    _TurnChargerOff   ; turn off graphics charger
        _endif

        mov     ah,al               ; select colour
        mov     al,080h             ; select TCR mode
        call    _TurnChargerOn      ; turn on graphics charger

        inc     _ebx
        mov     ah,es:[_edi]         ; get starting byte
        _loop
          test    ah,cl             ; test if pixel is set
          _if     e                 ; bit is not set
            or      dl,dl           ; quit loop if paint while
            jne     short done_NECscanleft
          _else
            or      dl,dl           ; quit loop if paint until
            je      short done_NECscanleft
          _endif
          dec     _ebx               ; move to next pixel
          cmp     _esi,_ebx           ; check for viewport boundary
          _quif   ge
          rol     cl,1              ; rotate mask for new pixel
          _if     c
            dec     _edi             ; look at next byte
            mov     ah,es:[_edi]
          _endif
        _endloop

done_NECscanleft:
        call    _TurnChargerOff     ; turn graphics charger back off (reset)
        or      dh,dh               ; if the graphics charger was on
        _if     ne                  ; then
          mov     al,0c0h           ; - put it back into RMW mode
          mov     ah, byte ptr ss:__CurrColor
          call    _TurnChargerOn    ; - . . .
        _endif                      ; endif
        ret

_NECScanRight_:
        mov     dh,_ChargerOn       ; remember whether graphics charger is on
        or      dh, dh
        _if     ne
          call    _TurnChargerOff   ; turn off graphics charger
        _endif
        push    _edx                 ; store whether graphics charger was on

        mov     ah,al               ; select colour
        mov     al,080h             ; select TCR mode
        call    _TurnChargerOn      ; turn on graphics charger

        mov     dh,cl               ; build an extended right mask for 1st byte
        shl     dh,1
        neg     dh                  ; example : 00000100 -> 00000111
        not     dh
        _loop                       ; line up with byte boundary
          dec   _ebx
          shl   cl,1
        _until  c
        mov     ah,es:[_edi]         ; load first byte
        xor     al,al               ; build scan byte mask
        or      dl,dl               ; if( border_flag != 0 )
        _if     ne
          not     ax
        _endif
        and     ah,dh               ; border condition true in first byte
        jne     short done_NECscanright
        mov     _ecx,_esi             ; convert the pixel count inside
        sub     _ecx,_ebx             ; the viewport to a byte count
        dec     _ecx                 ; in order to scan full bytes
        and     cl,0F8h
        add     _ebx,_ecx
        shr     _ecx,1
        shr     _ecx,1
        shr     _ecx,1
        jle     short done_NECscanright   ; less than 8 pixels to scan
        inc     _edi
        repe    scasb
        shl     _ecx,1
        shl     _ecx,1
        shl     _ecx,1
        sub     _ebx,_ecx
        dec     _edi
        mov     ah,es:[_edi]
        or      dl,dl
        _if     ne
          not     ah
        _endif

done_NECscanright:
        _loop
          shl     ah,1
          _quif   c
          cmp     _esi,_ebx
          _quif   le
          inc     _ebx
        _endloop

        call    _TurnChargerOff     ; turn graphics charger back off (reset)
        pop     _edx                 ; remember if graphics charger was on
        or      dh,dh               ; if the graphics charger was on
        _if     ne                  ; then
          mov     al,0c0h           ; - put it back into RMW mode
          mov     ah, byte ptr __CurrColor
          call    _TurnChargerOn    ; - . . .
        _endif                      ; endif
        ret

        endmod necutils
        end
