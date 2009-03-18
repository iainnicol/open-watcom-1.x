;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	realloc_
		PUBLIC	_nrealloc_
		EXTRN	remalloc			: PROC
;
; DECLARATION	void *realloc( void *oldblock, size_t size );
;
PROC		realloc_		STDCALL
LABEL		_nrealloc_		PROC
		push	ecx				; Save context
		mov	ecx,edx				; ECX = number of bytes to allocate
		or	eax,eax				; Allocate new block ?
		jz	remalloc			; Yes, allocate new block
		call	[DWORD ReallocateBlock]		; No, reallocate block
		jnc	SHORT @@Exit			; Error ?
		xor	eax,eax				; Yes, clear EAX
@@Exit:		pop	ecx				; Restore context
		ret
ENDP
		END
