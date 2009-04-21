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
		PUBLIC	DosClosePipe
;
; DECLARATION	int DosClosePipe( PIPE *pipe );
;
PROC		DosClosePipe		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to pipe
		;
		; Close pipe
		;
IFDEF __ZDOSDRV__
		call	[DWORD PipeClose]
ELSE
		mov	ah,IPC_CLOSE_PIPE
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of tasks waiting
ENDP
		END
