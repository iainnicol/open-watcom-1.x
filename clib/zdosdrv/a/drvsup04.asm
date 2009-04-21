;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetKernelVector
;
; DECLARATION	void ( __cdecl *DosGetKernelVector( int i ) )(struct context_t);
;
PROC		DosGetKernelVector	WATCOM_C
		USES	ecx,ebx
		movzx	ecx,al				; ECX = vector number
		call	[DWORD GetVector]		; Get vector
		mov	eax,ebx				; EAX = interrupt vector
		cmp	eax,[OurVector + ecx * 4]	; Our interrupt vector ?
		jnz	SHORT @@Exit			; No, we are done
		mov	eax,[UserVector + ecx * 4]	; Yes, return pointer to user handler
@@Exit:		ret
ENDP
		DATASEG
		EXTRN	OurVector			: DWORD
		UDATASEG
		EXTRN	UserVector			: DWORD
		END
