		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvGetMulticastList_
;
; DECLARATION	int DosPktDrvGetMulticastList( int InterfaceNumber, void *Buffer );
;
PROC		DosPktDrvGetMulticastList_ STDCALL
		push	edi				; Save context
		push	ebx
		mov	ebx,eax				; EBX = interface number
		mov	edi,edx				; EDI points to buffer
		mov	ah,PKTDRV_GET_MULTICAST_LIST	; Get multicast list
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		pop	edi
		jc	DosError			; Success ?
		ret					; Yes, return number of muilticast entries
ENDP
		END
