;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	kbhit_
;
; DECLARATION	int kbhit( void );
;
PROC		kbhit_			STDCALL
		xor	eax,eax				; Clear EAX
		xchg	eax,[_cbyte]			; Clear and get buffered byte
		or	eax,eax				; Character available ?
		jnz	SHORT @@Exit			; Yes, we are done
		mov	ah,DOS_CHECK_INPUT_STATUS	; No, AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,al				; EAX = status
@@Exit:		ret
ENDP
		UDATASEG
		EXTRN	C _cbyte			: DWORD
		END
