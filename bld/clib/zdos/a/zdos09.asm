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
		PUBLIC	DosConsoleDisplayString_
;
; DECLARATION	int DosConsoleDisplayString( char *dos_message );
;
PROC		DosConsoleDisplayString_ STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX points to string
		mov	ah,DOS_CONSOLE_DISPLAY_STRING	; AH = DOS function
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
