;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosKeyboardFlags
;
; DECLARATION	int BiosKeyboardFlags( void );
;
PROC		BiosKeyboardFlags	WATCOM_C
		mov	ah,KEYBOARD_FLAGS		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		jmp	BiosReturnAL			; Process return code
ENDP
		END
