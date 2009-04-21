;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocatePages
;
; DECLARATION	int DosAllocatePages( int pages, void **block );
;
PROC		DosAllocatePages	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of pages to allocate
		call	[DWORD AllocatePages]		; Allocate block
		mov	[edx],eax			; Update block pointer variable
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
