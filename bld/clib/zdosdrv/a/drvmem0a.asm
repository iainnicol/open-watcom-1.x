;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosLinearToPhysical_
;
; DECLARATION	int DosLinearToPhysical( void *linear, unsigned *physical );
;
PROC		DosLinearToPhysical_	STDCALL
		call	[DWORD PhysicalAddress]		; Get physical address
		mov	[edx],eax			; Assume success
		jmp	DosReturnZero			; Process return code
ENDP
		END
