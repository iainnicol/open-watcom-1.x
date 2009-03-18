;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BuildFileSystemName_
;
; DECLARATION	int BuildFileSystemName( void *buffer, char *name );
;
PROC		BuildFileSystemName_	STDCALL
		push	edi				; Save context
		push	esi
		push	ecx
		push	ebx
		push	eax
		mov	esi,edx				; ESI = pointer to zero terminated name
		mov	edi,eax				; EDI points to buffer
		mov	eax,20202020h			; EAX = padded value
		mov	[edi],eax			; Fill buffer with spaces
		mov	[edi + 4],eax
		mov	ebx,OFFSET AlphaNumericMap	; EBX points to character translation map
		mov	ah,8				; AH = maximum character count
@@NextChar:	lodsb					; Get next character in AL
		xlatb					; Translate it
		or	al,al				; End of string ?
		jz	SHORT @@EndOfName		; Yes, we are done
		stosb					; No, store character in buffer
		dec	ah				; AH = number of characters left to check
		jnz	@@NextChar			; Get next character
@@EndOfName:	pop	eax				; EAX points to buffer
		cmp	edi,eax				; Number of characters = 0 ?
		jnz	SHORT @@Exit			; No, we are done
		mov	eax,94				; Yes, EAX = DOS error code
		stc					; Set carry flag
@@Exit:		pop	ebx				; Restore context
		pop	ecx
		pop	esi
		pop	edi
		ret
ENDP
		DATASEG
AlphaNumericMap	DB	48 DUP (0)			; Ascii 00h - 2fh
		DB	'0123456789',0,0,0,0,0,0	; Ascii 30h - 3fh
		DB	0,'ABCDEFGHIJKLMNO'		; Ascii 40h - 4fh
		DB	'PQRSTUVWXYZ',0,0,0,0,0		; Ascii 50h - 5fh
		DB	0,'ABCDEFGHIJKLMNO'		; Ascii 60h - 6fh
		DB	'PQRSTUVWXYZ',0,0,0,0,0		; Ascii 70h - 7fh
		DB	128 DUP (0)			; Ascii 80h - ffh
		END
