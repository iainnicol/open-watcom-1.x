;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateHeapBlock
;
; DECLARATION	int DosAllocateHeapBlock( int size, void **block );
;
PROC		DosAllocateHeapBlock	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = size of block
		call	[DWORD AllocateBlock]		; Allocate heap block
		mov	[edx],eax			; Update block pointer variable
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
