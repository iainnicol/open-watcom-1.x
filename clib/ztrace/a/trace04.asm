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
		PUBLIC	DosTraceSetBreakPoints
;
; DECLARATION	int DosTraceSetBreakPoints( int count, unsigned char *values,
;		                             void *locations );
;
PROC		DosTraceSetBreakPoints	WATCOM_C
		push	edi				; Save context
		push	ecx
		mov	edi,ebx				; EDI points to location list
		mov	ecx,eax				; ECX = number of break points to set
		mov	ah,TRACE_SET_BREAKPOINTS	; Set break points
		int	TRACE
		pop	ecx				; Restore context
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
