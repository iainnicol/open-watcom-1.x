;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateIrq_
;
; DECLARATION	int DosAllocateIrq( int irq, void ( *handler )() );
;
PROC		DosAllocateIrq_		STDCALL
		call	[DWORD AllocateIrq]		; Allocate IRQ and install handler
		jmp	DosReturnZero			; Process return code
ENDP
		END
