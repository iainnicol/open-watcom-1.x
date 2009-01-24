;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosTerminateProcess_
;
; DECLARATION	void DosTerminateProcess( void );
;
PROC		DosTerminateProcess_	STDCALL
IFDEF __ZDOSDRV__
		ret
ELSE
		mov	ah,DOS_TERMINATE_PROCESS	; AH = DOS function
		int	DOS
ENDIF
ENDP
		END
