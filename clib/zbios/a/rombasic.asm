;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosRomBasic_
;
; DECLARATION	void BiosRomBasic( void );
;
PROC		BiosRomBasic_
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD BiosRomBasic]
ELSE
		int	BIOS_ROM_BASIC
		ret
ENDIF
ENDP
		END
