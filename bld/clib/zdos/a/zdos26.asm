;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosEnvironmentLength_
;
; DECLARATION	int DosEnvironmentLength( void );
;
PROC		DosEnvironmentLength_	STDCALL
		mov	ah,DOS_ENVIRONMENT_LENGTH	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret					; Return length
ENDP
		END
