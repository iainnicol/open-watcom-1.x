		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvRemoveInterface
;
; DECLARATION	int DosPktDrvRemoveInterface( int InterfaceNumber );
;
PROC		DosPktDrvRemoveInterface	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = interface number
		mov	ah,PKTDRV_REMOVE_INTERFACE	; Remove packet driver interface
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
