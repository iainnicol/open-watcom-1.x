;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	ungetch_
;
; DECLARATION	int ungetch( int c );
;
PROC		ungetch_		STDCALL
		movzx	eax,al				; EAX = character
		test	[_cbyte],-1			; Character buffer full ?
		jnz	SHORT @@EndOfFile		; Yes, we are at end of file
		mov	[_cbyte],eax			; No, store character
		ret
@@EndOfFile:	mov	eax,-1				; EAX = end of file return code
		ret
ENDP
		UDATASEG
		EXTRN	C _cbyte			: DWORD
		END
