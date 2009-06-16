;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSignalGlobalSemaphore
;
; DECLARATION	int DosSignalGlobalSemaphore( int handle );
;
PROC		DosSignalGlobalSemaphore WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = semaphore handle
		mov	ah,IPC_SIGNAL_SEMAPHORE		; Signal semaphore
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
