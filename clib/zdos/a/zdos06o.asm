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
		PUBLIC	DosDirectConsoleOutput
;
; DECLARATION	int DosDirectConsoleOutput( int character );
;
PROC		DosDirectConsoleOutput	WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = character to write
		mov	ah,DOS_DIRECT_CONSOLEIO		; AH = DOS function

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
