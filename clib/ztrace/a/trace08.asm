;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosTraceGetCpuContext
;
; DECLARATION	int DosTraceGetCpuContext( TCPU *context );
;
PROC		DosTraceGetCpuContext	WATCOM_C
		push	edi				; Save context
		mov	edi,eax				; EDI points to context buffer
		mov	ah,TRACE_GET_CPU_CONTEXT	; Get CPU context
		int	TRACE
		pop	edi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
