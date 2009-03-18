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
		PUBLIC	DosCloseGlobalSemaphore_
;
; DECLARATION	int DosCloseGlobalSemaphore( int handle );
;
PROC		DosCloseGlobalSemaphore_ STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = semaphore handle
		mov	ah,IPC_CLOSE_SEMAPHORE		; Close semaphore
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of tasks waiting
ENDP
		END
