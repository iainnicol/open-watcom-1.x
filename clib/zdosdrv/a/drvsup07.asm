;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetUserVector
;
; DECLARATION	void DosSetUserVector( int intnum,
;                                      void ( *h ) (EXCEPTION *) );
;
PROC		DosSetUserVector	WATCOM_C
		USES	ecx,ebx
		mov	ebx,edx				; EBX points to ISR
		xor	edx,edx				; Clear EDX
		;
		; Get vector index in EAX
		;
		and	eax,0ffh
		cmp	[UserApiVector + eax * 4],edx	; User vector already installed ?
		jnz	SHORT @@SetVector		; No, set vector
		mov	edx,[OurApiVector + eax * 4]	; Yes, EDX points to our service routine
		xchg	ebx,edx				; EDX = user pointer, EBX = our pointer
@@SetVector:	mov	[UserApiVector + eax * 4],edx	; Save pointer to user handler
		mov	cl,al				; CL = vector index
		call	[DWORD SetUserVector]		; Set vector
		ret
ENDP
		DATASEG
		EXTRN	OurApiVector			: DWORD
		UDATASEG
		EXTRN	UserApiVector			: DWORD
		END
