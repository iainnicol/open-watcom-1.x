;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosAbortProcess
;
; DECLARATION	int DosAbortProcess( int PID );
;
PROC		DosAbortProcess		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = PID
		mov	ah,DOS_ABORT_PROCESS		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
