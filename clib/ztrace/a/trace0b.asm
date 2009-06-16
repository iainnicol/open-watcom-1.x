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
		PUBLIC	DosTraceSetFpuContext
;
; DECLARATION	int DosTraceSetFpuContext( TFPU *fpu );
;
PROC		DosTraceSetFpuContext	WATCOM_C
		push	esi				; Save context
		mov	esi,eax				; ESI points to context buffer
		mov	ah,TRACE_SET_FPU_CONTEXT	; Set FPU context
		int	TRACE
		pop	esi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
