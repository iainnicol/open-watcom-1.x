;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_serialcom
;
; DECLARATION	unsigned _bios_serialcom( unsigned service, unsigned port,
;		                          unsigned data );
;
PROC		_bios_serialcom		WATCOM_C
		mov	ah,al				; AH = BIOS function
		mov	al,bl				; AL = data
		;
		; Call BIOS serial communication services
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		ret
ENDP
		END
