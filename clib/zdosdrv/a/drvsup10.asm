;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosAllocateDmaBuffer_
;
; DECLARATION	int DosAllocateDmaBuffer( int pages );
;
PROC		DosAllocateDmaBuffer_	STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of pages to allocate
		call	[DWORD DmaAllocBuffer]		; Allocate DMA buffer
		pop	ecx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return DMA handle
ENDP
		END
