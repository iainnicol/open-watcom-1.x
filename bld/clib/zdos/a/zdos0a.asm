;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosConsoleBufferedInput_
;
; DECLARATION	int DosConsoleBufferedInput( char * buffer );
;
PROC		DosConsoleBufferedInput_ STDCALL
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
