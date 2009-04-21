;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosFinishDmaTransfer
;
; DECLARATION	int DosFinishDmaTransfer( int channel );
;
PROC		DosFinishDmaTransfer	WATCOM_C
		call	[DWORD DmaFinish]		; Finish DMA transfer
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
