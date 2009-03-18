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
		PUBLIC	BiosSetBorderColor_
;
; DECLARATION	int BiosSetBorderColor( int color );
;
PROC		BiosSetBorderColor_	STDCALL
		push	ebx				; Save context
		movzx	ebx,al				; BL = color, BH = 0
		mov	ah,VIDEO_SET_BORDER		; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	al,[VideoPage]			; AL = console number
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	C VideoPage			: BYTE
ENDIF
		END
