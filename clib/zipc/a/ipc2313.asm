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
		PUBLIC	DosCreateGlobalPipe
;
; DECLARATION	int DosCreateGlobalPipe( char *name );
;
PROC		DosCreateGlobalPipe	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to pipes name
		mov	ah,IPC_CREATE_PIPE		; Create pipe
		int	GLOBAL_IPC
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
