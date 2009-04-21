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
		PUBLIC	BiosGetPciResourceSize
;
; DECLARATION	int BiosGetPciResourceSize( int bus, int device,
;                                           int function, int register,
;		                            unsigned *value );
;
PROC		BiosGetPciResourceSize	WATCOM_C
		ARG	Bus : DWORD, Device : DWORD, Function : DWORD, \
			Register : DWORD, Value : DWORD
		USES	edi,esi
		mov	bh,al				; BH = bus number
		shl	dl,3				; Get device bits in proper position
		or	bl,dl				; BL = device and function bits
		mov	edi,ecx				; EDI = register number
		mov	esi,[Value]			; ESI = pointer to value
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_READ_CONFIG_DWORD	; AL = subfunction number
		;
		; Get device base address from base register
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		jc	SHORT @@Exit			; Error ?
		mov	edx,ecx				; No, save value in EDX
		mov	ecx,-1				; ECX = value to write
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_WRITE_CONFIG_DWORD	; AL = subfunction number
		;
		; Write base register
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_READ_CONFIG_DWORD	; AL = subfunction number
		;
		; Read base register again
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	al,11111100b			; Assume I/O resource
		test	cl,1				; Is it ?
		jnz	SHORT @@GetSize			; Yes, get resource size
		mov	al,11110000b			; No, it's a memory resource
@@GetSize:	and	cl,al				; ECX = two's complement of resource size
		neg	ecx				; ECX = resource size in bytes
		mov	[esi],ecx			; Store result in callers variable
		mov	ecx,edx				; ECX = previous value
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_WRITE_CONFIG_DWORD	; AL = subfunction number
		;
		; Restore device base address
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
@@Exit:		call	BiosReturnZero			; Process return code
		ret
ENDP
		END
