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
		PUBLIC	DosTraceCopyToClient_
;
; DECLARATION	int DosTraceCopyToClient( int count, void *from,
;                                         unsigned to );
;
PROC		DosTraceCopyToClient_	STDCALL
		push	edi				; Save context
		push	esi
		push	ecx
		mov	edi,ebx				; EDI = location to copy to
		mov	esi,edx				; ESI points to callers buffer
		mov	ecx,eax				; ECX = number of bytes to copy
		mov	ah,TRACE_COPY_TO_CLIENT		; Copy data to client
		int	TRACE
		pop	ecx				; Restore context
		pop	esi
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
