;
; ZDOS run time library function.
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
PROC		BiosBootStrap_
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
