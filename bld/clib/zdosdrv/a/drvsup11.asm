;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosFreeDmaBuffer_
;
; DECLARATION	int DosFreeDmaBuffer( int handle );
;
PROC		DosFreeDmaBuffer_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = handle
		call	[DWORD DmaFreeBuffer]		; Free DMA buffer
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
