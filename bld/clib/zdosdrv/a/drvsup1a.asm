;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeIrq_
;
; DECLARATION	int DosFreeIrq( int irq );
;
PROC		DosFreeIrq_		STDCALL
		call	[DWORD FreeIrq]			; Free IRQ
		jmp	DosReturnZero			; Process return code
ENDP
		END
