;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosTerminateProcess
;
; DECLARATION	void DosTerminateProcess( void );
;
PROC		DosTerminateProcess	WATCOM_C
IFDEF __ZDOSDRV__
		ret
ELSE
		mov	ah,DOS_TERMINATE_PROCESS	; AH = DOS function
		int	DOS
ENDIF
ENDP
		END
