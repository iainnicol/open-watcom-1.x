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
		PUBLIC	BiosSetCursor
;
; DECLARATION	int BiosSetCursor( int row, int column );
;
PROC		BiosSetCursor		WATCOM_C
		push	ebx				; Save context
		mov	dh,al				; DH = row
		mov	ah,VIDEO_SET_CURSOR		; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	bh,[VideoPage]			; BH = console number
		call	[DWORD DosVideo]
ELSE
		xor	bh,bh				; BH = video page
		int	BIOS_VIDEO
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
