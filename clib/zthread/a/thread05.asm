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
		PUBLIC	DosDelayTicks
;
; DECLARATION	int DosDelayTicks( unsigned ticks );
;
PROC		DosDelayTicks		WATCOM_C
IFDEF __ZDOSDRV__
		call	[DWORD ThreadDelayTick]		; Sleep
ELSE
		push	edx				; Save context
		mov	edx,eax				; EDX = ticks
		mov	ah,THREAD_DELAY_TICKS		; Sleep
		int	THREAD
		pop	edx				; Restore context
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
