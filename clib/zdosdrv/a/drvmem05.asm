;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreePages
;
; DECLARATION	int DosFreePages( void *block );
;
PROC		DosFreePages		WATCOM_C
		call	[DWORD ReallocatePages]		; Reallocate block
		jmp	DosReturnZero			; Process return code
ENDP
		END
