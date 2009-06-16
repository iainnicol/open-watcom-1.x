;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateHeapBlocks
;
; DECLARATION	int DosAllocateHeapBlocks(int size,void **block,int count);
;
PROC		DosAllocateHeapBlocks	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = size of each block
		call	[DWORD AllocateBlocks]		; Allocate heap blocks
		mov	[edx],eax			; Update block pointer variable
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
