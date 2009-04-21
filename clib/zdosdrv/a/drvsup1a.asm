;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeIrq
;
; DECLARATION	int DosFreeIrq( int irq );
;
PROC		DosFreeIrq		WATCOM_C
		call	[DWORD FreeIrq]			; Free IRQ
		jmp	DosReturnZero			; Process return code
ENDP
		END
