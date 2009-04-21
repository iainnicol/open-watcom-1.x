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
		PUBLIC	DosTraceClearBreakPoints
;
; DECLARATION	int DosTraceClearBreakPoints( int count,unsigned char *values,
;		                              void *locations);
;
PROC		DosTraceClearBreakPoints WATCOM_C
		push	edi				; Save context
		push	ecx
		mov	edi,ebx				; EDI points to location list
		mov	ecx,eax				; ECX = number of break points to clear
		mov	ah,TRACE_CLEAR_BREAKPOINTS	; Clear break points
		int	TRACE
		pop	ecx				; Restore context
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
