;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_memsize
;
; DECLARATION	unsigned _bios_memsize( void );
;
PROC		_bios_memsize		WATCOM_C
		;
		; Call BIOS memsize service
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosBaseMemory]
ELSE
		int	BIOS_BASE_MEM
ENDIF
		ret
ENDP
		END
