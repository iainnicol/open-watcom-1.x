;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosBaseMemorySize
;
; DECLARATION	int BiosBaseMemorySize( void );
;
PROC		BiosBaseMemorySize	WATCOM_C
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
