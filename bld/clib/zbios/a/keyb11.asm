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
		PUBLIC	BiosFullKeyboardStatus_
;
; DECLARATION	int BiosFullKeyboardStatus( void );
;
PROC		BiosFullKeyboardStatus_	STDCALL
		mov	ah,KEYBOARD_FULL_STATUS		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		jbe	BiosReturnZero			; Success ?
		movzx	eax,ax				; Yes, return scan code and character code
		ret
ENDP
		END
