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
		PUBLIC	DosReadGlobalPipeTimeOut_
;
; DECLARATION	int DosReadGlobalPipeTimeOut( int bytes, void *buffer,
;		                              int handle, unsigned timeout );
;
PROC		DosReadGlobalPipeTimeOut_ STDCALL
		push	edi				; Save context
		mov	edi,edx				; EDI points to buffer
		mov	edx,ecx				; EDX = timeout
		mov	ecx,eax				; ECX number of bytes to read
		mov	ah,IPC_READ_PIPE_TIME_OUT	; Read pipe
		int	GLOBAL_IPC
		pop	edi				; Restore context
		jc	DosError			; Success ?
		mov	eax,ecx				; Yes, return number of bytes read
		ret
ENDP
		END
