;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosLockDmaBuffer
;
; DECLARATION	int DosLockDmaBuffer( int handle, DMABUF *dmabuf );
;
PROC		DosLockDmaBuffer	WATCOM_C
		push	esi				; Save context
		push	ecx
		push	ebx
		mov	esi,edx				; ESI points to DMABUF block
		mov	ebx,eax				; EBX = DMA handle
		call	[DWORD DmaLockBuffer]		; Lock DMA buffer
		mov	[(DMABUF esi).Linear],edx	; Store linear address of buffer
		mov	[(DMABUF esi).Physical],eax	; Store physical address of buffer
		mov	[(DMABUF esi).Size],ecx		; Store size of buffer
		pop	ebx				; Restore context
		pop	ecx
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		END
