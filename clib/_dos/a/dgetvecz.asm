;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_dos_getvect
;
; DECLARATION	void ( __cdecl *_dos_getvect( int i ) ) ( struct context_t );
;
PROC		_dos_getvect		WATCOM_C
		USES	ebx
		mov	ah,DOS_GET_VECTOR		; AH = DOS function
		;
		; Get vector
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,al				; EAX = interrupt vector number
		xchg	eax,ebx				; EAX = interrupt vector, EBX = interrupt vector number
		cmp	eax,[OurVector + ebx * 4]	; Our interrupt vector ?
		jnz	SHORT @@Exit			; No, we are done
		mov	eax,[UserVector + ebx * 4]	; Yes, return pointer to user handler
@@Exit:		ret
ENDP
		DATASEG
		EXTRN	OurVector			: DWORD
		UDATASEG
		EXTRN	UserVector			: DWORD
		END
