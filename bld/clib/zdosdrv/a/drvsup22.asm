;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_DosConsolePrint
;
; DECLARATION	void __cdecl DosConsolePrint( const char *message, ... );
;
PROC		_DosConsolePrint
		jmp	[DWORD ConsolePrint]		; Display message
ENDP
		END
