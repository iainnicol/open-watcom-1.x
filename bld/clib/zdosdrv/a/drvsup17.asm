;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosAllocateDeviceBlock_
;
; DECLARATION	int DosAllocateDeviceBlock( unsigned physical, int pages,
;                                           void **block );
;
PROC		DosAllocateDeviceBlock_	STDCALL
		push	ecx				; Save context
		mov	ecx,edx				; ECX = number of pages to map
		call	[DWORD DeviceMap]		; Map device block
		mov	[ebx],eax			; Save linear address of mapped block
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
