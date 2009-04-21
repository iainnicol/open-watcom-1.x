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
		PUBLIC	DosOpenGlobalPipe
;
; DECLARATION	int DosOpenGlobalPipe( char *name );
;
PROC		DosOpenGlobalPipe	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to pipes name
		mov	ah,IPC_OPEN_PIPE		; Open pipe
		int	GLOBAL_IPC
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
