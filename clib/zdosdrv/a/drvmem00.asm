;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateHeapBlock_
;
; DECLARATION	int DosAllocateHeapBlock( int size, void **block );
;
PROC		DosAllocateHeapBlock_	STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = size of block
		call	[DWORD AllocateBlock]		; Allocate heap block
		mov	[edx],eax			; Update block pointer variable
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
