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
		PUBLIC	DosWaitEventTimeOut
;
; DECLARATION	int DosWaitEventTimeOut( int flags, unsigned bitmask,
;		                         EVENT *event, unsigned timeout );
;
PROC		DosWaitEventTimeOut	WATCOM_C
		xchg	ecx,edx				; ECX = bitmask, EDX = timeout value
IFDEF __ZDOSDRV__
		xchg	eax,edx				; EAX = timeout value, EDX = flags
		call	[DWORD EventWaitTO]		; Wait event
ELSE
		mov	ah,IPC_WAIT_EVENT_TIME_OUT	; Wait event
		int	LOCAL_IPC
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return event flags
ENDP
		END
