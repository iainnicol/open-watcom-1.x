		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvGetParameters
;
; DECLARATION	int DosPktDrvGetParameters( int InterfaceNumber, PKTDRV_PARAM **Buffer );
;
PROC		DosPktDrvGetParameters	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = interface number
		mov	ah,PKTDRV_GET_PARAMETERS	; Get pointer to parameters
		call	[DWORD DosPacketDriver]
		mov	[edx],eax			; Store pointer to parameters
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
