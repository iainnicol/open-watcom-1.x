;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosOpenPipe
;
; DECLARATION	int DosOpenPipe( PIPE *pipe );
;
PROC		DosOpenPipe		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to pipe
		;
		; Open pipe
		;
IFDEF __ZDOSDRV__
		call	[DWORD PipeOpen]
ELSE
		mov	ah,IPC_OPEN_PIPE
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
