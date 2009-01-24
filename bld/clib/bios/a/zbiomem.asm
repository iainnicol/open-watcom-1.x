;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_memsize_
;
; DECLARATION	unsigned _bios_memsize( void );
;
PROC		_bios_memsize_		STDCALL
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
