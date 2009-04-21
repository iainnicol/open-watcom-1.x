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
		PUBLIC	DosTraceCopyFromClient
;
; DECLARATION	int DosTraceCopyFromClient( int count, unsigned from,
;                                           void *to );
;
PROC		DosTraceCopyFromClient	WATCOM_C
		push	edi				; Save context
		push	esi
		push	ecx
		mov	edi,ebx				; EDI points to callers buffer
		mov	esi,edx				; ESI = location to copy from
		mov	ecx,eax				; ECX = number of bytes to copy
		mov	ah,TRACE_COPY_FROM_CLIENT	; Copy data from client
		int	TRACE
		pop	ecx				; Restore context
		pop	esi
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
