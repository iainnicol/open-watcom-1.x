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
		PUBLIC	DosOpenSemaphore
;
; DECLARATION	int DosOpenSemaphore( SEMAPHORE *semaphore, unsigned value );
;
PROC		DosOpenSemaphore	WATCOM_C
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to semaphore
		mov	eax,edx				; EAX = initial semaphore value
		call	[DWORD SemaphoreOpen]		; Open semaphore
		pop	ebx				; Restore context
ELSE
		push	ecx				; Save context
		push	ebx
		mov	ecx,edx				; ECX = initial semaphore value
		mov	ebx,eax				; EBX points to semaphore
		mov	ah,IPC_OPEN_SEMAPHORE		; Open semaphore
		int	LOCAL_IPC
		pop	ebx				; Restore context
		pop	ecx
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
