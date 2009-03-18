;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosSetBlinkBit_
;
; DECLARATION	int BiosSetBlinkBit( int blinkbit );
;
PROC		BiosSetBlinkBit_	STDCALL
		push	ecx				; Save context
		push	ebx
		movzx	ebx,al				; EBX = blink bit
		mov	eax,VIDEO_CHANGE_BLINK_BIT	; AH = video function, AL = subfunction
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	cl,[VideoPage]			; CL = console number
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnZero			; Process return code
ENDP
		UDATASEG
		EXTRN	C VideoPage			: BYTE
		END
