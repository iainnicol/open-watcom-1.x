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
		PUBLIC	DosWriteGlobalPipe
;
; DECLARATION	int DosWriteGlobalPipe( int bytes, void *buffer, in handle );
;
PROC		DosWriteGlobalPipe	WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX number of bytes to write
		mov	esi,edx				; ESI points to buffer
		mov	ah,IPC_WRITE_PIPE		; Write pipe
		int	GLOBAL_IPC
		mov	edx,ecx				; EDX = number of bytes written
		pop	ecx				; Restore context
		pop	edi
		jc	DosError			; Success ?
		mov	eax,edx				; Yes, return number of bytes written
		ret
ENDP
		END
