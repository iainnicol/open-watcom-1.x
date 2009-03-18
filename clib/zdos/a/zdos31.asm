;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosTerminateResident_
;
; DECLARATION	void DosTerminateResident( int retcode, int memsize );
;
PROC		DosTerminateResident_	STDCALL
		;
		; Get function number in AH
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
