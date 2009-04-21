		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvWaitPacket
;
; DECLARATION	int DosPktDrvWaitPacket( int Handle, void *Buffer );
;
PROC		DosPktDrvWaitPacket	WATCOM_C
		push	ebx				; Save context
		lea	ebx,[eax + eax]			; EBX = handle
		mov	ah,PKTDRV_WAIT_PACKET		; Wait for a packet
		int	PKTDRV_CAPTURE
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return packet size
ENDP
		END
