		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvGetAddress
;
; DECLARATION	int DosPktDrvGetAddress( int Length, void *Buffer, int InterfaceNumber );
;
PROC		DosPktDrvGetAddress	WATCOM_C
		push	edi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = length
		mov	edi,edx				; EDI points to buffer
		mov	ah,PKTDRV_GET_ADDRESS		; Get address
		call	[DWORD DosPacketDriver]
		pop	ecx				; Restore context
		pop	edi
		jc	DosError			; Success ?
		ret					; Yes, return length
ENDP
		END
