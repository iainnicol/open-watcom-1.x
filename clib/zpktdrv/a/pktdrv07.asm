		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvSetReceiveMode
;
; DECLARATION	int DosPktDrvSetReceiveMode( int mode, int InterfaceNumber );
;
PROC		DosPktDrvSetReceiveMode	WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = receive mode
		mov	ebx,edx				; EBX = interface number
		mov	esi,edx				; ESI points to buffer
		mov	ah,PKTDRV_SET_RECEIVE_MODE	; Set receive mode
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		END
