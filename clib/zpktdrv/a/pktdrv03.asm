		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvSendPacket
;
; DECLARATION	int DosPktDrvSendPacket( int Length, void *Buffer, int InterfaceNumber );
;
PROC		DosPktDrvSendPacket	WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = length
		mov	esi,edx				; ESI points to buffer
		mov	ah,PKTDRV_SEND_PACKET		; Send packet
		call	[DWORD DosPacketDriver]
		pop	ecx				; Restore context
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		END
