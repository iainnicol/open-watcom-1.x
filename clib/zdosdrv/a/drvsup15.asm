;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosStartDmaTransfer_
;
; DECLARATION	int DosStartDmaTransfer( int channel, int type, int mode,
;		                         int count, void *buffer );
;
PROC		DosStartDmaTransfer_	STDCALL
		ARG	Buffer : DWORD
		USES	esi
		mov	dh,bl				; DH = transfer mode
		mov	esi,[Buffer]			; ESI points to buffer
		call	[DWORD DmaStart]		; Start DMA transfer
		jnc	SHORT @@Exit			; Success ?
		neg	eax				; No, negate error code
@@Exit:		ret
ENDP
		END
