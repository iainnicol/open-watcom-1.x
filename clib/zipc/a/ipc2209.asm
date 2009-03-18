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
		PUBLIC	DosWaitSemaphore_
;
; DECLARATION	int DosWaitSemaphore( SEMAPHORE *semaphore );
;
PROC		DosWaitSemaphore_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to semaphore
		;
		; Wait semaphore
		;
IFDEF __ZDOSDRV__
		call	[DWORD SemaphoreLock]
ELSE
		mov	ah,IPC_WAIT_SEMAPHORE
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
