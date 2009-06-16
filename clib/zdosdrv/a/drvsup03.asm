;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosUnhookPciPorts
;
; DECLARATION	int DosUnhookIsaPorts( unsigned iobase );
;
PROC		DosUnhookPciPorts	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = I/O base address
		call	[DWORD UnhookPciPorts]		; Unhook PCI I/O ports
		pop	edx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
