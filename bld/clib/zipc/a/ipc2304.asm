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
		PUBLIC	DosWaitGlobalMutexTimeOut_
;
; DECLARATION	int DosWaitGlobalMutexTimeOut( int handle, unsigned timeout );
;
PROC		DosWaitGlobalMutexTimeOut_ STDCALL
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = mutex handle
		mov	ecx,edx				; ECX = timeout value
		mov	ah,IPC_WAIT_MUTEX_TIME_OUT	; Wait mutex
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		pop	ecx
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
