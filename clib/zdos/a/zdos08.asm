;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		PUBLIC	DosConsoleInputNoEcho
;
; DECLARATION	int DosConsoleInputNoEcho( void );
;
PROC		DosConsoleInputNoEcho	WATCOM_C
		mov	ah,DOS_CONSOLE_INPUT_NO_ECHO	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	DosReturnAL			; Process return code
ENDP
		END
