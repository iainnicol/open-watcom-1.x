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
		PUBLIC	DosCloseSemaphore
;
; DECLARATION	int DosCloseSemaphore( SEMAPHORE *semaphore );
;
PROC		DosCloseSemaphore	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to semaphore
		;
		; Close semaphore
		;
IFDEF __ZDOSDRV__
		call	[DWORD SemaphoreClose]
ELSE
		mov	ah,IPC_CLOSE_SEMAPHORE
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of tasks waiting
ENDP
		END
