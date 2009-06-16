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
		PUBLIC	DosReadPipe
;
; DECLARATION	int DosReadPipe( int bytes, void *buffer, PIPE *pipe );
;
PROC		DosReadPipe		WATCOM_C
		push	edi				; Save context
		push	ecx
		mov	ecx,eax				; ECX number of bytes to read
		mov	edi,edx				; EDI points to buffer
		;
		; Read pipe
		;
IFDEF __ZDOSDRV__
		call	[DWORD PipeRead]
ELSE
		mov	ah,IPC_READ_PIPE
		int	LOCAL_IPC
ENDIF
		mov	edx,ecx				; EDX = number of bytes read
		pop	ecx				; Restore context
		pop	edi
		jc	DosError			; Success ?
		mov	eax,edx				; Yes, return number of bytes read
		ret
ENDP
		END
