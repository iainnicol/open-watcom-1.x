;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosGeneratePciCycle_
;
; DECLARATION	int BiosGeneratePciCycle( int bus, unsigned cycledata );
;
PROC		BiosGeneratePciCycle_	STDCALL
		push	ebx				; Save context
		mov	bh,al				; BH = bus number
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_GENERATE_CYCLE		; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
