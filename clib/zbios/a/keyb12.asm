;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosError			: PROC
		PUBLIC	BiosFullKeyboardFlags
;
; DECLARATION	int BiosFullKeyboardFlags( void );
;
PROC		BiosFullKeyboardFlags	WATCOM_C
		mov	ah,KEYBOARD_FULL_FLAGS		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		jc	BiosError			; Success ?
		ret					; Yes, return flags
ENDP
		END
