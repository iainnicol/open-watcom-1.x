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
		PUBLIC	DosWaitEvent_
;
; DECLARATION	int DosWaitEvent(int flags, unsigned bitmask, EVENT *event);
;
PROC		DosWaitEvent_		STDCALL
		push	ecx				; Save context
		mov	ecx,edx				; ECX = bitmask
		;
		; Wait event
		;
IFDEF __ZDOSDRV__
		mov	edx,eax				; EDX = flags
		call	[DWORD EventWait]
ELSE
		mov	ah,IPC_WAIT_EVENT
		int	LOCAL_IPC
ENDIF
		pop	ecx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return event flags
ENDP
		END
