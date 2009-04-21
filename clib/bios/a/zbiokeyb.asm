;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_bios_keybrd
;
; DECLARATION	unsigned _bios_keybrd( unsigned service );
;
PROC		_bios_keybrd		WATCOM_C
		USES	edx
		mov	ah,al				; AH = BIOS function
		mov	dl,al				; Save copy in DL
		;
		; Call BIOS keyboard services
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		xchg	eax,edx				; Swap return code and EDX
		lahf					; Save flags in AH
		and	al,1				; Keyboard status function called ?
		jz	SHORT @@Exit			; No, we are done
		test	ah,40h				; ZF set ?
		jz	SHORT @@Exit			; No, we are done
		xor	edx,edx				; Yes, clear EDX
@@Exit:		mov	eax,edx				; Update callers EAX with result
		ret
ENDP
		END
