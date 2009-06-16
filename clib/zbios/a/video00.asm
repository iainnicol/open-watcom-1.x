;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosSetVideoMode
;
; DECLARATION	int BiosSetVideoMode( int mode );
;
PROC		BiosSetVideoMode	WATCOM_C
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
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
