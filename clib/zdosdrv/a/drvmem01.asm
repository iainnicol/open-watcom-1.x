;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateHeapBlocks_
;
; DECLARATION	int DosAllocateHeapBlocks(int size,void **block,int count);
;
PROC		DosAllocateHeapBlocks_	STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = size of each block
		call	[DWORD AllocateBlocks]		; Allocate heap blocks
		mov	[edx],eax			; Update block pointer variable
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
