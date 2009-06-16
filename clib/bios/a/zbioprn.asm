;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_printer
;
; DECLARATION	unsigned _bios_printer( unsigned service, unsigned port,
;		                        unsigned data );
;
PROC		_bios_printer		WATCOM_C
		mov	ah,al				; AH = BIOS function
		mov	al,bl				; AL = data
		;
		; Call BIOS printer services
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosPrinter]
ELSE
		int	BIOS_PRINTER
ENDIF
		movzx	eax,ah				; EAX = status
		ret
ENDP
		END
