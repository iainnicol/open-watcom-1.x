		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosPktDrvCloseSession_
;
; DECLARATION	int DosPktDrvCloseSession( int InterfaceNumber, int Handle );
;
PROC		DosPktDrvCloseSession_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = interface number
		mov	ah,PKTDRV_CLOSE_SESSION		; Close session
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		mov	eax,[PktDrvCallBack + edx * 4]	; Yes, EAX points to callback handle
		call	[DWORD FreeBlock]		; Free block
		xor	eax,eax				; EAX = return code
		ret
ENDP
		UDATASEG
		EXTRN	PktDrvCallBack			: DWORD
		END
