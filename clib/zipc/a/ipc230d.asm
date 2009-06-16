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
		PUBLIC	DosOpenGlobalEvent
;
; DECLARATION	int DosOpenGlobalEvent( char *name );
;
PROC		DosOpenGlobalEvent	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to event name
		mov	ah,IPC_OPEN_EVENT		; Open event
		int	GLOBAL_IPC
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return handle
ENDP
		END
