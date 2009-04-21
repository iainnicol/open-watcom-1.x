;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSignalSemaphore
;
; DECLARATION	int DosSignalSemaphore( SEMAPHORE *semaphore );
;
PROC		DosSignalSemaphore	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to semaphore
IFDEF __ZDOSDRV__
		clc					; Clear carry flag
		call	[DWORD SemaphoreUnlock]		; Signal semaphore
ELSE
		mov	ah,IPC_SIGNAL_SEMAPHORE		; Signal semaphore
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
