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
		PUBLIC	BiosReadPciRegisterBYTE
;
; DECLARATION	int BiosReadPciRegisterBYTE( int bus, int device,
;                                            int function, int register,
;		                             unsigned char *value );
;
PROC		BiosReadPciRegisterBYTE	WATCOM_C
		ARG	Bus : DWORD, Device : DWORD, Function : DWORD, \
			Register : DWORD, Value : DWORD
		USES	edi,esi
		mov	bh,al				; BH = bus number
		shl	dl,3				; Get device bits in proper position
		or	bl,dl				; BL = device and function bits
		mov	edi,ecx				; EDI = register number
		mov	esi,[Value]			; ESI points to variable
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_READ_CONFIG_BYTE	; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	[esi],cl			; Store register value
		call	BiosReturnZero			; Process return code
		ret
ENDP
		END
