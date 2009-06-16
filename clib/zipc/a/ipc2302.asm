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
		PUBLIC	DosCloseGlobalMutex
;
; DECLARATION	int DosCloseGlobalMutex( int handle );
;
PROC		DosCloseGlobalMutex	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = mutex handle
		mov	ah,IPC_CLOSE_MUTEX		; Close mutex
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of tasks waiting
ENDP
		END
