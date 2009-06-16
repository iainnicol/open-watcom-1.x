;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosValidateUserBlock
;
; DECLARATION	int DosValidateUserBlock( void *block, unsigned size );
;
PROC		DosValidateUserBlock	WATCOM_C
		push	ecx				; Save context
		mov	ecx,edx				; ECX = size of block
		call	[DWORD ValidateBlock]		; Validate block
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
