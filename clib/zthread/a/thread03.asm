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
		PUBLIC	DosSleepThread
;
; DECLARATION	int DosSleepThread( unsigned ticks );
;
PROC		DosSleepThread		WATCOM_C
IFDEF __ZDOSDRV__
		call	[DWORD ThreadSleep]		; Sleep
ELSE
		push	edx				; Save context
		mov	edx,eax				; EDX = ticks
		mov	ah,THREAD_SLEEP			; Sleep
		int	THREAD
		pop	edx				; Restore context
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
