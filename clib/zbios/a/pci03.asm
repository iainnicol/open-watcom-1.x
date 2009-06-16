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
		PUBLIC	BiosFindPciClass
;
; DECLARATION	int BiosFindPciClass (int index, int class,
;                                     PCIFIND *pcifind );
;
PROC		BiosFindPciClass	WATCOM_C
		push	edi				; Save context
		push	esi
		push	ecx
		mov	esi,eax				; ESI = index
		mov	edi,ebx				; EDI points to PCIFIND block
		mov	ecx,edx				; ECX = class
		mov	eax,PCI_SERVICES SHL 8 + \	; AH = function number
			    PCI_FIND_CLASS		; AL = subfunction number
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
@@Exit:		pop	ecx				; Restore context
		pop	esi
		pop	edi
		jmp	BiosReturnZero			; Process return code
ENDP
		END
