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
		PUBLIC	DosWakeUpThread_
;
; DECLARATION	int DosWakeUpThread( int TID );
;
PROC		DosWakeUpThread_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX = TID
		;
		; Wake up thread
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadWakeUp]
ELSE
		mov	ah,THREAD_WAKE_UP
		int	THREAD
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
