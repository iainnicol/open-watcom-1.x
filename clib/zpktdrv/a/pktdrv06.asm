		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvGetReceiveMode
;
; DECLARATION	int DosPktDrvGetReceiveMode( int InterfaceNumber );
;
PROC		DosPktDrvGetReceiveMode	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = interface number
		mov	edi,edx				; EDI points to buffer
		mov	ah,PKTDRV_GET_RECEIVE_MODE	; Get receive mode
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return receive mode
ENDP
		END
