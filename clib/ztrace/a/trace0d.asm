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
		PUBLIC	DosTraceSetDebugContext
;
; DECLARATION	int DosTraceSetDebugContext( TDEBUG *debug );
;
PROC		DosTraceSetDebugContext WATCOM_C
		push	esi				; Save context
		mov	esi,eax				; ESI points to context buffer
		mov	ah,TRACE_SET_DEBUG_CONTEXT	; Set debug context
		int	TRACE
		pop	esi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
