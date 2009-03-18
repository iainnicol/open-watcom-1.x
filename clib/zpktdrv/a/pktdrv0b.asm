		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvGetStatistics_
;
; DECLARATION	int DosPktDrvGetStatistics( int InterfaceNumber, PKTDRV_STATS *Buffer );
;
PROC		DosPktDrvGetStatistics_	STDCALL
		push	edi				; Save context
		push	ebx
		mov	ebx,eax				; EBX = interface number
		mov	edi,edx				; EDI points to buffer
		mov	ah,PKTDRV_GET_STATISTICS	; Get statistics
		call	[DWORD DosPacketDriver]
		pop	ebx				; Restore context
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
