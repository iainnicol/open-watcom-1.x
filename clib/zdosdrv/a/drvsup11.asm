;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosFreeDmaBuffer
;
; DECLARATION	int DosFreeDmaBuffer( int handle );
;
PROC		DosFreeDmaBuffer	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = handle
		call	[DWORD DmaFreeBuffer]		; Free DMA buffer
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
