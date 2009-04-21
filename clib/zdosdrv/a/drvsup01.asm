;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosUnhookIsaPorts
;
; DECLARATION	int DosUnhookIsaPorts( unsigned iobase );
;
PROC		DosUnhookIsaPorts	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = I/O base address
		call	[DWORD UnhookIsaPorts]		; Unhook ISA I/O ports
		pop	edx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
