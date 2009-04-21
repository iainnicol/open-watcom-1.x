;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetVector
;
; DECLARATION	void DosSetVector( int intnum,
;		                   void ( __cdecl *handler )( CONTEXT ) );
;
PROC		DosSetVector		WATCOM_C
		USES	ebx
		xor	ebx,ebx				; Clear EBX
		;
		; Get vector index in EAX
		;
IFDEF __ZDOSDRV__
		and	eax,0ffh
ELSE
		and	eax,1fh
ENDIF
		cmp	[UserVector + eax * 4],ebx	; User vector already installed ?
		jnz	SHORT @@SetVector		; No, set vector
		mov	ebx,[OurVector + eax * 4]	; Yes, EBX points to our service routine
		xchg	ebx,edx				; EBX = user pointer, EDX = our pointer
@@SetVector:	mov	[UserVector + eax * 4],ebx	; Save pointer to user handler
		mov	ah,DOS_SET_VECTOR		; AH = DOS function number
		;
		; Set vector
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret
ENDP
		DATASEG
		EXTRN	OurVector			: DWORD
		UDATASEG
		EXTRN	UserVector			: DWORD
		END
