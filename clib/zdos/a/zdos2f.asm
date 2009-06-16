;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosResetEnvironment
;
; DECLARATION	void DosResetEnvironment( void );
;
PROC		DosResetEnvironment	WATCOM_C
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
