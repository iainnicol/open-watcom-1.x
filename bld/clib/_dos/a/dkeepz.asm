;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_dos_keep_
;
; DECLARATION	void _dos_keep( unsigned retcode, unsigned memsize );
;
PROC		_dos_keep_		STDCALL
		;
		; Get DOS function number in AH
		;
		mov	ah,DOS_TERMINATE_AND_STAY_RESIDENT
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
ENDP
		END
