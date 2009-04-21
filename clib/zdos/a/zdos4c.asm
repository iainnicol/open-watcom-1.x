;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosExitProcess
;
; DECLARATION	void DosExitProcess( int exitcode );
;
PROC		DosExitProcess		WATCOM_C
IFDEF __ZDOSDRV__
		ret
ELSE
		mov	ah,DOS_EXIT_PROCESS		; AH = DOS function
		int	DOS
ENDIF
ENDP
		END
