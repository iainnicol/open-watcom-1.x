		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvSetAddress
;
; DECLARATION	int DosPktDrvSetAddress( int Length, void *Buffer, int InterfaceNumber );
;
PROC		DosPktDrvSetAddress	WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = length
		mov	esi,edx				; ESI points to buffer
		mov	ah,PKTDRV_SET_ADDRESS		; Set address
		call	[DWORD DosPacketDriver]
		pop	ecx				; Restore context
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		END
