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
		PUBLIC	DosResizeMemoryBlock
;
; DECLARATION	int DosResizeMemoryBlock( int numpages, void *block );
;
PROC		DosResizeMemoryBlock	WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = size of block
		mov	ebx,edx				; EBX points to block
		mov	ah,DOS_RESIZE_MEMORY_BLOCK	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		END
