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
		PUBLIC	DosOpenGlobalMutex
;
; DECLARATION	int DosOpenGlobalMutex( char *name );
;
PROC		DosOpenGlobalMutex	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to mutex name
		mov	ah,IPC_OPEN_MUTEX		; Open mutex
		int	GLOBAL_IPC
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
