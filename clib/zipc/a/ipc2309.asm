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
		PUBLIC	DosWaitGlobalSemaphore
;
; DECLARATION	int DosWaitGlobalSemaphore( int handle );
;
PROC		DosWaitGlobalSemaphore	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = semaphore handle
		mov	ah,IPC_WAIT_SEMAPHORE		; Wait semaphore
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
