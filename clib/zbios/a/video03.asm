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
		PUBLIC	BiosGetCursor
;
; DECLARATION	int BiosGetCursor( CURSOR *cursor );
;
PROC		BiosGetCursor		WATCOM_C
		push	esi				; Save context
		push	edx
		push	ecx
		push	ebx
		mov	esi,eax				; ESI points to CURSOR block
		mov	ah,VIDEO_GET_CURSOR		; AH = video function
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
		mov	[WORD (CURSOR esi).Column],dx	; Save column and row
		mov	[WORD (CURSOR esi).StartLine],cx; Save starting and ending line
		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		pop	esi
		jmp	BiosReturnZero
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
