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
		PUBLIC	BiosSetCursorType
;
; DECLARATION	int BiosSetCursorType( int startingline, int endingline );
;
PROC		BiosSetCursorType	WATCOM_C
		push	ecx				; Save context
IFDEF _ZDOSDRV__
		push	ebx				; Save EBX
		mov	bh,[VideoPage]			; BH = console number
ENDIF
		mov	ch,al				; CH = starting line
		mov	cl,dl				; CL = ending line
		mov	ah,VIDEO_SET_CURSOR_TYPE	; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosVideo]
		pop	ebx				; Restore EBX
ELSE
		int	BIOS_VIDEO
ENDIF
		pop	ecx				; Restore context
		jmp	BiosReturnZero
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
