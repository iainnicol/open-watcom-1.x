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
		PUBLIC	DosWaitSemaphoreTimeOut
;
; DECLARATION	int DosWaitSemaphoreTimeOut( SEMAPHORE *semaphore,
;		                             unsigned timeout );
;
PROC		DosWaitSemaphoreTimeOut WATCOM_C
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to semaphore
		mov	eax,edx				; EAX = time out value
		call	[DWORD SemaphoreLockTO]		; Wait semaphore
		pop	ebx				; Restore context
ELSE
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX points to semaphore
		mov	ecx,edx				; ECX = timeout value
		mov	ah,IPC_WAIT_SEMAPHORE_TIME_OUT	; Wait semaphore
		int	LOCAL_IPC
		pop	ebx				; Restore context
		pop	ecx
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
