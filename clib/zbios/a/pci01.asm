;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosPciInformation
;
; DECLARATION	int BiosPciInformation( PCIDATA *pcidata );
;
PROC		BiosPciInformation	WATCOM_C
		push	esi				; Save context
		push	edx
		push	ecx
		push	ebx
		mov	esi,eax				; ESI points to PCIDATA block
		xor	ecx,ecx				; Clear ECX
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_INSTALLATION_CHECK	; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	[(PCIDATA esi).Hardware],ax	; Store hardware bits
		mov	[(PCIDATA esi).Major],bh	; Store major version number
		mov	[(PCIDATA esi).Minor],bl	; Store minor version number
		mov	[(PCIDATA esi).LastBus],ecx	; Store last bus
		mov	[(PCIDATA esi).ID],edx		; Store ID
		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		pop	esi
		jmp	BiosReturnZero			; Process return code
ENDP
		END
