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
		PUBLIC	DosWritePipeTimeOut
;
; DECLARATION	int DosWritePipeTimeOut( int bytes, void *buffer,
; 		                         PIPE *pipe, unsigned timeout );
;
PROC		DosWritePipeTimeOut	WATCOM_C
		push	esi				; Save context
		mov	esi,edx				; ESI points to buffer
IFDEF __ZDOSDRV__
		xchg	eax,ecx				; EAX = timeout value, ECX = number of bytes to write
		call	[DWORD PipeWriteTO]		; Write pipe
ELSE
		mov	edx,ecx				; EDX = timeout
		mov	ecx,eax				; ECX number of bytes to write
		mov	ah,IPC_WRITE_PIPE_TIME_OUT	; Write pipe
		int	LOCAL_IPC
ENDIF
		pop	esi				; Restore context
		jc	DosError			; Success ?
		mov	eax,ecx				; Yes, return number of bytes written
		ret
ENDP
		END
