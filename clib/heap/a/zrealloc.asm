;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	realloc
		PUBLIC	WATCOM_C _nrealloc
		EXTRN	remalloc			: PROC
;
; DECLARATION	void *realloc( void *oldblock, size_t size );
;
PROC		realloc		WATCOM_C
LABEL		_nrealloc	PROC
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
