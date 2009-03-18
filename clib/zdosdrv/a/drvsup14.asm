;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosCloseDmaChannel_
;
; DECLARATION	int DosCloseDmaChannel( int channel );
;
PROC		DosCloseDmaChannel_	STDCALL
		call	[DWORD DmaCloseChannel]		; Close DMA channel
		jmp	DosReturnZero			; Process return code
ENDP
		END
