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
		PUBLIC	DosWaitGlobalMutex_
;
; DECLARATION	int DosWaitGlobalMutex( int handle );
;
PROC		DosWaitGlobalMutex_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = mutex handle
		mov	ah,IPC_WAIT_MUTEX		; Wait mutex
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
