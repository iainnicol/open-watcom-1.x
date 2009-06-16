;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosReallocatePages
;
; DECLARATION	int DosReallocatePages( void *block, int pages );
;
PROC		DosReallocatePages	WATCOM_C
		push	ecx				; Save context
		mov	ecx,edx				; ECX = new size of block
		call	[DWORD ReallocatePages]		; Reallocate block
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
