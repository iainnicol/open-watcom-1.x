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
		PUBLIC	DosCloseGlobalPipe_
;
; DECLARATION	int DosCloseGlobalPipe( int handle );
;
PROC		DosCloseGlobalPipe_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = message buffer handle
		mov	ah,IPC_CLOSE_PIPE		; Close message buffer
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of waiting tasks
ENDP
		END
