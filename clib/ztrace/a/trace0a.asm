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
		PUBLIC	DosTraceGetFpuContext
;
; DECLARATION	int DosTraceGetFpuContext( TFPU *context );
;
PROC		DosTraceGetFpuContext	WATCOM_C
		push	edi				; Save context
		mov	edi,eax				; EDI points to context buffer
		mov	ah,TRACE_GET_FPU_CONTEXT	; Get FPU context
		int	TRACE
		pop	edi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
