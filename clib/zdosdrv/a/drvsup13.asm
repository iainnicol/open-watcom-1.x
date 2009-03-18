;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosOpenDmaChannel_
;
; DECLARATION	int DosOpenDmaChannel(int channel,DMABUF **dmabuf,int size);
;
PROC		DosOpenDmaChannel_	STDCALL
		push	ecx				; Save context
		mov	ecx,ebx				; ECX = size of DMA buffer
		call	[DWORD DmaOpenChannel]		; Open DMA channel
		mov	[edx],eax			; Store pointer to DMABUF block
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
