;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	malloc
		PUBLIC	WATCOM_C _nmalloc
		PUBLIC	remalloc
;
; DECLARATION	void *malloc( size_t size );
;
PROC		malloc			WATCOM_C
LABEL		_nmalloc		PROC
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to allocate
LABEL		remalloc		PROC
		call	[DWORD AllocateBlock]		; Allocate block
		jnc	SHORT @@Exit			; Error ?
		xor	eax,eax				; Yes, clear EAX
@@Exit:		pop	ecx				; Restore context
		ret
ENDP
		END
