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
		PUBLIC	BiosFindPciDevice_
;
; DECLARATION	int BiosFindPciDevice( int index, int vendor, int device,
;		                       PCIFIND *pcifind );
;
PROC		BiosFindPciDevice_	STDCALL
		push	edi				; Save context
		push	esi
		mov	esi,eax				; ESI = index
		mov	edi,ecx				; EDI points to PCIFIND block
		mov	ecx,ebx				; ECX = device ID
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_FIND_DEVICE		; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		jc	SHORT @@Exit			; Success ?
		mov	[(PCIFIND edi).Bus],bh		; Yes, store bus number
		mov	[(PCIFIND edi).Function],bl	; Store device and function number
		shr	bl,3				; BL = device number
		mov	[(PCIFIND edi).Device],bl	; Store device number
		and	[(PCIFIND edi).Function],7	; Isolate function number
@@Exit:		pop	esi				; Restore context
		pop	edi
		jmp	BiosReturnZero			; Process return code
ENDP
		END
