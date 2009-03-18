		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvSetMulticastList_
;
; DECLARATION	int DosPktDrvSetMulticastList( int NumberOfEntries, void *Buffer, int InterfaceNumber );
;
PROC		DosPktDrvSetMulticastList_ STDCALL
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = number of multicast entries
		mov	esi,edx				; ESI points to buffer
		mov	ah,PKTDRV_SET_MULTICAST_LIST	; Set multicast list
		call	[DWORD DosPacketDriver]
		pop	ecx				; Restore context
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		END
