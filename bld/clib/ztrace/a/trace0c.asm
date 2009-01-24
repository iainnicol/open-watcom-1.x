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
		PUBLIC	DosTraceGetDebugContext_
;
; DECLARATION	int DosTraceGetDebugContext( TDEBUG *debug );
;
PROC		DosTraceGetDebugContext_ STDCALL
		push	edi				; Save context
		mov	edi,eax				; EDI points to context buffer
		mov	ah,TRACE_GET_DEBUG_CONTEXT	; Get debug context
		int	TRACE
		pop	edi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
