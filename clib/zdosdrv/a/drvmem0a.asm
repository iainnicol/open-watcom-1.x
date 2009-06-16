;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosLinearToPhysical
;
; DECLARATION	int DosLinearToPhysical( void *linear, unsigned *physical );
;
PROC		DosLinearToPhysical	WATCOM_C
		call	[DWORD PhysicalAddress]		; Get physical address
		mov	[edx],eax			; Assume success
		jmp	DosReturnZero			; Process return code
ENDP
		END
