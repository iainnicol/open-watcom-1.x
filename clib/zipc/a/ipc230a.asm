;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosWaitGlobalSemaphoreTimeOut
;
; DECLARATION	int DosWaitGlobalSemaphoreTimeOut( int handle,
;		                                   unsigned timeout );
;
PROC		DosWaitGlobalSemaphoreTimeOut WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = semaphore handle
		mov	ecx,edx				; ECX = timeout value
		mov	ah,IPC_WAIT_SEMAPHORE_TIME_OUT
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		pop	ecx
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
