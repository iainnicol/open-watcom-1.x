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
		PUBLIC	BiosSetBorder
;
; DECLARATION	int BiosSetBorder( int color );
;
PROC		BiosSetBorder		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	bh,al				; BH = color
		mov	eax,VIDEO_SET_OVERSCAN		; AH = video function, AL = subfunction
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
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
