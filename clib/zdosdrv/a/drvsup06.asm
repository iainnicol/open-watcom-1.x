;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetUserVector
;
; DECLARATION	void ( *DosGetUserVector( int i ) )(EXCEPTION *);
;
PROC		DosGetUserVector	WATCOM_C
		USES	ecx,ebx
		movzx	ecx,al				; ECX = vector number
		call	[DWORD GetUserVector]		; Get vector
		mov	eax,ebx				; EAX = interrupt vector
		cmp	eax,[OurApiVector + ecx * 4]	; Our interrupt vector ?
		jnz	SHORT @@Exit			; No, we are done
		mov	eax,[UserApiVector + ecx * 4]	; Yes, return pointer to user handler
@@Exit:		ret
ENDP
		DATASEG
		EXTRN	OurApiVector			: DWORD
		UDATASEG
		EXTRN	UserApiVector			: DWORD
		END
