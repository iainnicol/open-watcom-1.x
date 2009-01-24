;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	getche_
;
; DECLARATION	int getche( void );
;
PROC		getche_			STDCALL
		xor	eax,eax				; Clear EAX
		xchg	eax,[_cbyte]			; Clear and get buffered byte
		or	eax,eax				; Character available ?
		jnz	SHORT @@Exit			; Yes, we are done
		mov	ah,DOS_CONSOLE_INPUT		; No, AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,al				; EAX = character
@@Exit:		ret
ENDP
		UDATASEG
		EXTRN	C _cbyte			: DWORD
		END
