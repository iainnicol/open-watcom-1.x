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
		PUBLIC	DosReadPipeTimeOut
;
; DECLARATION	int DosReadPipeTimeOut( int bytes, void *buffer,
; 		                        PIPE *pipe, unsigned timeout );
;
PROC		DosReadPipeTimeOut	WATCOM_C
		push	edi				; Save context
		mov	edi,edx				; EDI points to buffer
IFDEF __ZDOSDRV__
		xchg	eax,ecx				; EAX = timeout value, ECX = number of bytes to read
		call	[DWORD PipeReadTO]		; Read pipe
ELSE
		mov	edx,ecx				; EDX = timeout
		mov	ecx,eax				; ECX number of bytes to read
		mov	ah,IPC_READ_PIPE_TIME_OUT	; Read pipe
		int	LOCAL_IPC
ENDIF
		pop	edi				; Restore context
		jc	DosError			; Success ?
		mov	eax,ecx				; Yes, return number of bytes read
		ret
ENDP
		END
