;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateMemoryBlock

;
; DECLARATION	int DosAllocateMemoryBlock( int pages, void **block );
;
PROC		DosAllocateMemoryBlock	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = size of block
		mov	ah,DOS_ALLOCATE_MEMORY_BLOCK	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		mov	[edx],eax			; Save pointer to block
		jmp	DosReturnZero			; Process return code
ENDP
		END
