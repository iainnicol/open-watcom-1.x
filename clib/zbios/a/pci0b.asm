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
		PUBLIC	BiosWritePciRegisterBYTE
;
; DECLARATION	int BiosWritePciRegisterBYTE( int bus, int device,
;                                             int function, int register,
;		                              unsigned char value );
;
PROC		BiosWritePciRegisterBYTE WATCOM_C
		ARG	Bus : DWORD, Device : DWORD, Function : DWORD, \
			Register : DWORD, Value : DWORD
		USES	edi
		mov	bh,al				; BH = bus number
		shl	dl,3				; Get device bits in proper position
		or	bl,dl				; BL = device and function bits
		mov	edi,ecx				; EDI = register number
		mov	ecx,[Value]			; CL = value to write
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_WRITE_CONFIG_BYTE	; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		call	BiosReturnZero			; Process return code
		ret
ENDP
		END
