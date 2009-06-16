;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocatePciBuffer
;
; DECLARATION	int DosAllocatePciBuffer( int numpages, unsigned *physical,
;                                         void **linear );
;
PROC		DosAllocatePciBuffer	WATCOM_C
		push	esi				; Save context
		push	ecx
		mov	ecx,eax				; ECX = size of block
		mov	esi,edx				; ESI points to physical variable
		call	[DWORD AllocPciBlock]		; Allocate block
		jc	SHORT @@Exit			; Success ?
		mov	[ebx],edx			; Yes, save linear address
		mov	[esi],eax			; Save physical adress
@@Exit:		pop	ecx				; Restore context
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		END
