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
		PUBLIC	DosTraceOpenSession_
;
; DECLARATION	int DosTraceOpenSession( TCPU *context );
;
PROC		DosTraceOpenSession_	STDCALL
		push	edi				; Save context
		mov	edi,eax				; EDI points to context buffer
		mov	ah,TRACE_OPEN_SESSION		; Open trace session
		int	TRACE
		pop	edi				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return thread ID
ENDP
		END
