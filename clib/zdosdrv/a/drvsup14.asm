;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosCloseDmaChannel
;
; DECLARATION	int DosCloseDmaChannel( int channel );
;
PROC		DosCloseDmaChannel	WATCOM_C
		call	[DWORD DmaCloseChannel]		; Close DMA channel
		jmp	DosReturnZero			; Process return code
ENDP
		END
