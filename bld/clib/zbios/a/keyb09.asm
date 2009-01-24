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
		PUBLIC	BiosKeyboardCapabilities_
;
; DECLARATION	int BiosKeyboardCapabilities( void );
;
PROC		BiosKeyboardCapabilities_ STDCALL
		mov	ah,KEYBOARD_CAPABILITIES	; AH = function number
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
