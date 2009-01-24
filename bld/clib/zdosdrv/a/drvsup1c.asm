;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosShareIrq_
;
; DECLARATION	int DosShareIrq( int irq, void ( *handler )(),
;                                void ( **OldHandler )() );
;
PROC		DosShareIrq_		STDCALL
		call	[DWORD ShareIrq]		; Install shared IRQ handler
		jmp	DosReturnZero			; Process return code
ENDP
		END
