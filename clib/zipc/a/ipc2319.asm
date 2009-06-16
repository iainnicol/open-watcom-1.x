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
		PUBLIC	DosWriteGlobalPipeTimeOut
;
; DECLARATION	int DosWriteGlobalPipeTimeOut( int bytes, void *buffer,
;		                               int handle, unsigned timeout);
;
PROC		DosWriteGlobalPipeTimeOut WATCOM_C
		push	esi				; Save context
		mov	esi,edx				; ESI points to buffer
		mov	edx,ecx				; EDX = timeout
		mov	ecx,eax				; ECX number of bytes to write
		mov	ah,IPC_WRITE_PIPE_TIME_OUT	; Write pipe
		int	GLOBAL_IPC
		pop	esi				; Restore context
		jc	DosError			; Success ?
		mov	eax,ecx				; Yes, return number of bytes written
		ret
ENDP
		END
