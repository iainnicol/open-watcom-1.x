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
		PUBLIC	DosWaitGlobalEventTimeOut
;
; DECLARATION	int DosWaitGlobalEventTimeOut( int flags, unsigned bitmask,
;		                               int handle, unsigned timeout );
;
PROC		DosWaitGlobalEventTimeOut WATCOM_C
		xchg	ecx,edx				; ECX = bit mask, EDX = timeout
		mov	ah,IPC_WAIT_EVENT_TIME_OUT	; Wait event
		int	GLOBAL_IPC
		jc	DosError			; Success ?
		ret					; Yes, return event flags
ENDP
		END
