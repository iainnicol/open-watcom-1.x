;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosBootStrap_
;
; DECLARATION	void BiosBootStrap( void );
;
PROC		BiosBootStrap_		STDCALL
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD BiosBootStrap]
ELSE
		int	BIOS_BOOT_STRAP
		ret
ENDIF
ENDP
		END
