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
		PUBLIC	BiosEnhancedMemorySize
;
; DECLARATION	int BiosEnhancedMemorySize( unsigned *isa, unsigned *above );
;
PROC		BiosEnhancedMemorySize	WATCOM_C
		push	edi				; Save context
		push	esi
		push	edx
		push	ecx
		push	ebx
		mov	esi,eax				; ESI points to isa variable
		mov	edi,edx				; EDI points to above variable
		mov	ah,MISC_ENHANCED_MEMSIZE	; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		mov	[esi],ecx			; Store isa memory size
		mov	[edi],edx			; Store above memory size
		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		pop	esi
		pop	edi
		jmp	BiosReturnZero			; Process return code
ENDP
		END
