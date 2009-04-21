;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosReallocateHeapBlock
;
; DECLARATION	int DosReallocateHeapBlock( void *oldblock, int newsize,
;		                            void **newblock );
;
PROC		DosReallocateHeapBlock	WATCOM_C
		push	ecx				; Save context
		mov	ecx,edx				; ECX = new size of block
		call	[DWORD ReallocateBlock]		; Reallocate heap block
		mov	[ebx],eax			; Update new block pointer variable
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
