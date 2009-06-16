;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosKeyboardCapabilities
;
; DECLARATION	int BiosKeyboardCapabilities( void );
;
PROC		BiosKeyboardCapabilities WATCOM_C
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
