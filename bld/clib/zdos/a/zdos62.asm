;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetPID_
;
; DECLARATION	int DosGetPID( void );
;
PROC		DosGetPID_		STDCALL
		mov	ah,DOS_GET_PID			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD DosApi]
ELSE
		int	DOS
		ret
ENDIF
ENDP
		END
