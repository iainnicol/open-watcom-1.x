;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosResetEnvironment_
;
; DECLARATION	void DosResetEnvironment( void );
;
PROC		DosResetEnvironment_	STDCALL
		USES	eax
		mov	ah,DOS_RESET_ENVIRONMENT	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret
ENDP
		END
