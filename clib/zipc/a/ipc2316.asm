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
		PUBLIC	DosReadGlobalPipe
;
; DECLARATION	int DosReadGlobalPipe( int bytes, void *buffer, int handle );
;
PROC		DosReadGlobalPipe	WATCOM_C
		push	edi				; Save context
		push	ecx
		mov	ecx,eax				; ECX number of bytes to read
		mov	edi,edx				; EDI points to buffer
		mov	ah,IPC_READ_PIPE		; Read pipe
		int	GLOBAL_IPC
		mov	edx,ecx				; EDX = number of bytes read
		pop	ecx				; Restore context
		pop	edi
		jc	DosError			; Success ?
		mov	eax,edx				; Yes, return number of bytes read
		ret
ENDP
		END
