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
		PUBLIC	DosCreateGlobalPipe_
;
; DECLARATION	int DosCreateGlobalPipe( char *name );
;
PROC		DosCreateGlobalPipe_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX points to pipes name
		mov	ah,IPC_CREATE_PIPE		; Create pipe
		int	GLOBAL_IPC
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
