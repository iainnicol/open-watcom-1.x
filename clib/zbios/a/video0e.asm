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
		PUBLIC	BiosWriteTeletype
;
; DECLARATION	int BiosWriteTeletype( int character );
;
PROC		BiosWriteTeletype	WATCOM_C
		push	ebx				; Save context
		mov	ah,VIDEO_WRITE_TELETYPE		; AH = video function
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
		jmp	BiosReturnZero			; Process return code
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
