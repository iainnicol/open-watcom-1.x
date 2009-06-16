;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosConsoleBufferedInput
;
; DECLARATION	int DosConsoleBufferedInput( char * buffer );
;
PROC		DosConsoleBufferedInput	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to string
		mov	ah,DOS_CONSOLE_BUFFERED_INPUT	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
