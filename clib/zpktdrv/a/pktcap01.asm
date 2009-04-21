		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZPKTDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosPktDrvCloseCapture
;
; DECLARATION	int DosPktDrvCloseCapture( int Handle );
;
PROC		DosPktDrvCloseCapture	WATCOM_C
		push	ebx				; Save context
		lea	ebx,[eax + eax]			; EBX = handle
		mov	ah,PKTDRV_CLOSE_CAPTURE		; Close capture session
		int	PKTDRV_CAPTURE
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
