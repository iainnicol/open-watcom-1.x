;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetVector_
;
; DECLARATION	void ( __cdecl *DosGetVector( int i ) )( CONTEXT );
;
PROC		DosGetVector_		STDCALL
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
