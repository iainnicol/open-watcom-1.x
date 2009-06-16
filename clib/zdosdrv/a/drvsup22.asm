;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosConsolePrint
;
; DECLARATION	void DosConsolePrint( const char *message, ... );
;
PROC		DosConsolePrint		WATCOM_C
		jmp	[DWORD ConsolePrint]		; Display message
ENDP
		END
