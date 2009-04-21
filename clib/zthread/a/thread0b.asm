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
		PUBLIC	DosWaitThread
;
; DECLARATION	int DosWaitThread( int TID );
;
PROC		DosWaitThread		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = thread ID
		;
		; Wait for thread termination
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadWait]
ELSE
		mov	ah,THREAD_WAIT
		int	THREAD
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return thread exit status
ENDP
		END
