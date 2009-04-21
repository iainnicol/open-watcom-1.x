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
		PUBLIC	BiosReadPciRegisterWORD
;
; DECLARATION	int BiosReadPciRegisterWORD( int bus, int device,
;                                            int function, int register,
;		                             unsigned short *value );
;
PROC		BiosReadPciRegisterWORD	WATCOM_C
		ARG	Bus : DWORD, Device : DWORD, Function : DWORD, \
			Register : DWORD, Value : DWORD
		USES	edi,esi
		mov	bh,al				; BH = bus number
		shl	dl,3				; Get device bits in proper position
		or	bl,dl				; BL = device and function bits
		mov	edi,ecx				; EDI = register number
		mov	esi,[Value]			; ESI points to variable
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_READ_CONFIG_WORD	; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	[esi],cx			; Store register value
		call	BiosReturnZero			; Process return code
		ret
ENDP
		END
