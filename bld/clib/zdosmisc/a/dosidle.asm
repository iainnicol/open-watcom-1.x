;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosIdle_
;
; DECLARATION	void DosIdle( void );
;
PROC		DosIdle_		STDCALL
		;
		; Let others run
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD DosIdle]
ELSE
		int	IDLE
		ret
ENDIF
ENDP
		END
