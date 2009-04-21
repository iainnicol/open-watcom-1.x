;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosKeyboardFlush
;
; DECLARATION	int BiosKeyboardFlush( void );
;
PROC		BiosKeyboardFlush	WATCOM_C
		mov	ah,KEYBOARD_FLUSH		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
