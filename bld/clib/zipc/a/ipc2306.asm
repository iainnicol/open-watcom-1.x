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
		PUBLIC	DosCreateGlobalSemaphore_
;
; DECLARATION	int DosCreateGlobalSemaphore( char *name, unsigned value );
;
PROC		DosCreateGlobalSemaphore_ STDCALL
		push	edx				; Save context
		push	ecx
		mov	ecx,edx				; ECX = initial semaphore count
		mov	edx,eax				; EDX points to semaphore name
		mov	ah,IPC_CREATE_SEMAPHORE		; Create semaphore
		int	GLOBAL_IPC
		pop	ecx				; Restore context
		pop	edx
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
