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
		PUBLIC	DosSignalGlobalMutex
;
; DECLARATION	int DosSignalGlobalMutex( int handle );
;
PROC		DosSignalGlobalMutex	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = mutex handle
		mov	ah,IPC_SIGNAL_MUTEX		; Signal mutex
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
