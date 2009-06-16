;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosShareIrq
;
; DECLARATION	int DosShareIrq( int irq, void ( *handler )(),
;                                void ( **OldHandler )() );
;
PROC		DosShareIrq		WATCOM_C
		call	[DWORD ShareIrq]		; Install shared IRQ handler
		jmp	DosReturnZero			; Process return code
ENDP
		END
