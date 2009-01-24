;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosFastConsoleOutput_
;
; DECLARATION	void DosConsoleFastOutput( char ch );
;
PROC		DosFastConsoleOutput_	STDCALL
		;
		; Write character to console device
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD DosFastOutput]
ELSE
		int	FAST_OUTPUT
		ret
ENDIF
ENDP
		END
