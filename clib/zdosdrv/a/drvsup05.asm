;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetKernelVector
;
; DECLARATION	void DosSetKernelVector( int intnum,
;		                         void (__cdecl *h)(struct context_t) );
;
PROC		DosSetKernelVector	WATCOM_C
		USES	ecx,ebx
		mov	ebx,edx				; EBX points to ISR
		xor	edx,edx				; Clear EDX
		;
		; Get vector index in EAX
		;
		and	eax,0ffh
		cmp	[UserVector + eax * 4],edx	; User vector already installed ?
		jnz	SHORT @@SetVector		; No, set vector
		mov	edx,[OurVector + eax * 4]	; Yes, EDX points to our service routine
		xchg	ebx,edx				; EDX = user pointer, EBX = our pointer
@@SetVector:	mov	[UserVector + eax * 4],edx	; Save pointer to user handler
		mov	cl,al				; CL = vector index
		call	[DWORD SetVector]		; Set vector
		ret
ENDP
		DATASEG
		EXTRN	OurVector			: DWORD
		UDATASEG
		EXTRN	UserVector			: DWORD
		END
