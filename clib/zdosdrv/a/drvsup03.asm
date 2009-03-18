;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosUnhookPciPorts_
;
; DECLARATION	int DosUnhookIsaPorts( unsigned iobase );
;
PROC		DosUnhookPciPorts_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX = I/O base address
		call	[DWORD UnhookPciPorts]		; Unhook PCI I/O ports
		pop	edx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
