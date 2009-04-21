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
		PUBLIC	DosOpenGlobalSemaphore
;
; DECLARATION	int DosOpenGlobalSemaphore( char *name );
;
PROC		DosOpenGlobalSemaphore WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to semaphore name
		mov	ah,IPC_OPEN_SEMAPHORE		; Open semaphore
		int	GLOBAL_IPC
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
