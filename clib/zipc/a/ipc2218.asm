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
		PUBLIC	DosWritePipe
;
; DECLARATION	int DosWritePipe( int bytes, void *buffer, PIPE *pipe );
;
PROC		DosWritePipe		WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX number of bytes to write
		mov	esi,edx				; ESI points to buffer
		;
		; Write pipe
		;
IFDEF __ZDOSDRV__
		call	[DWORD PipeWrite]
ELSE
		mov	ah,IPC_WRITE_PIPE
		int	LOCAL_IPC
ENDIF
		mov	edx,ecx				; EDX = number of bytes written
		pop	ecx				; Restore context
		pop	esi
		jc	DosError			; Success ?
		mov	eax,edx				; Yes, return number of bytes written
		ret
ENDP
		END
