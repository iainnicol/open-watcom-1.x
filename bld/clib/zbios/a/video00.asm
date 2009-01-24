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
		PUBLIC	BiosSetVideoMode_
;
; DECLARATION	int BiosSetVideoMode( int mode );
;
PROC		BiosSetVideoMode_	STDCALL
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	bh,[VideoPage]			; BH = console number
ENDIF
		mov	ah,VIDEO_SET_MODE		; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosVideo]
		pop	ebx				; Restore context
ELSE
		int	BIOS_VIDEO
ENDIF
		jmp	BiosReturnZero
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	C VideoPage			: BYTE
ENDIF
		END
