		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvInformation_
;
; DECLARATION	int DosPktDrvInformation( PKTDRV_INFO *info, int handle, int interfacenumber );
;
PROC		DosPktDrvInformation_	STDCALL
		push	edi				; Save context
		push	ecx
		mov	edi,eax				; EDI points to PKTDRV_INFO block
		mov	ah,PKTDRV_GET_INFORMATION	; Get packet driver information
		call	[DWORD DosPacketDriver]
		jc	SHORT @@Exit			; Success ?
		mov	[(PKTDRV_INFO edi).Version],eax	; Yes, store driver version in callers structure
		;
		; Store pointer to name in callers structure
		;
		mov	[(PKTDRV_INFO edi).PointerToName],ebx
		;
		; Store interface class in callers structure
		;
		mov	[(PKTDRV_INFO edi).InterfaceClass],ecx
@@Exit:		pop	ecx				; Restore context
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
