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
		PUBLIC	DosWaitGlobalEvent_
;
; DECLARATION	int DosWaitGlobalEvent( int flags, unsigned bitmask,
;		                        int handle );
;
PROC		DosWaitGlobalEvent_	STDCALL
		push	ecx				; Save context
		mov	ecx,edx				; ECX = bitmask
		mov	ah,IPC_WAIT_EVENT		; Wait event
		int	GLOBAL_IPC
		pop	ecx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return event flags
ENDP
		END
