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
		PUBLIC	DosCloseGlobalEvent
;
; DECLARATION	int DosCloseGlobalEvent( int handle );
;
PROC		DosCloseGlobalEvent	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = event handle
		mov	ah,IPC_CLOSE_EVENT		; Close event
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of waiting tasks
ENDP
		END
