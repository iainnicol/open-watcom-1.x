;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateIrq
;
; DECLARATION	int DosAllocateIrq( int irq, void ( *handler )() );
;
PROC		DosAllocateIrq		WATCOM_C
		call	[DWORD AllocateIrq]		; Allocate IRQ and install handler
		jmp	DosReturnZero			; Process return code
ENDP
		END
