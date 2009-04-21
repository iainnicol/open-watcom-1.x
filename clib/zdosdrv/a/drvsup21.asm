;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosConsoleMessage
;
; DECLARATION	void DosConsoleMessage( const char *message );
;
PROC		DosConsoleMessage	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to message
		call	[DWORD ConsoleMessage]		; Display message
		pop	edx				; Restore context
		ret
ENDP
		END
