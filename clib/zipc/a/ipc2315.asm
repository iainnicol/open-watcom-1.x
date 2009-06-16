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
		PUBLIC	DosCloseGlobalPipe
;
; DECLARATION	int DosCloseGlobalPipe( int handle );
;
PROC		DosCloseGlobalPipe	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = message buffer handle
		mov	ah,IPC_CLOSE_PIPE		; Close message buffer
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of waiting tasks
ENDP
		END
