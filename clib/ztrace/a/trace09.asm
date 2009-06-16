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
		PUBLIC	DosTraceSetCpuContext
;
; DECLARATION	int DosTraceSetCpuContext( TCPU *context );
;
PROC		DosTraceSetCpuContext	WATCOM_C
		push	esi				; Save context
		mov	esi,eax				; ESI points to context buffer
		mov	ah,TRACE_SET_CPU_CONTEXT	; Set CPU context
		int	TRACE
		pop	esi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
