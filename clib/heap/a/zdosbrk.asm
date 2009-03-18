;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ERRNO.INC'
		INCLUDE	'HEAP.INC'
		CODESEG
		EXTRN	MemoryStart			: BYTE
		PUBLIC	sbrk_
		PUBLIC	__brk_
;
; DECLARATION	void *sbrk( int increment );
;
PROC		sbrk_			STDCALL
		or	eax,eax				; Valid increment ?
		jnz	SHORT @@GrowMemory		; Yes, grow memory
		mov	eax,EINVAL			; No, EAX = errno
@@Error:	mov	[errno],eax			; Set errno
		mov	eax,-1				; Return -1
		ret
@@GrowMemory:	add	eax,[_curbrk]			; EAX = new break address
;
; DECLARATION	void *__brk ( unsigned breakvalue );
;
LABEL		__brk_			PROC
		push	ecx				; Save context
		push	ebx
		mov	ebx,OFFSET MemoryStart		; EDX points to memory start
		mov	ecx,eax				; ECX = new break address
		or	ecx,4095			; Round up to next page
		inc	ecx
		sub	ecx,ebx				; ECX = resulting memory size in bytes
		shr	ecx,12				; ECX = new block size
		mov	ah,DOS_RESIZE_MEMORY_BLOCK	; Resize memory block
		int	DOS
		jc	SHORT @@NoMemory		; Error ?
		shl	ecx,12				; No, ECX = size of reallocated area in bytes
		lea	eax,[ebx + ecx]			; EAX = new break address
		xchg	[_curbrk],eax			; Update break address and get previous
		pop	ebx				; Restore context
		pop	ecx
		ret
@@NoMemory:	mov	eax,ENOMEM			; EAX = errno
		pop	ebx				; Restore context
		pop	ecx
		jmp	@@Error				; Set errno and return -1
ENDP
		UDATASEG
		EXTRN	C errno				: DWORD
		EXTRN	C _curbrk			: DWORD
		END
