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
		PUBLIC	DosCreateGlobalEvent_
;
; DECLARATION	int DosCreateGlobalEvent( char *name, unsigned value );
;
PROC		DosCreateGlobalEvent_	STDCALL
		push	edx				; Save context
		push	ecx
		mov	ecx,edx				; ECX = initial value
		mov	edx,eax				; EDX points to event name
		mov	ah,IPC_CREATE_EVENT		; Create event
		int	GLOBAL_IPC
		pop	ecx				; Restore context
		pop	edx
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
