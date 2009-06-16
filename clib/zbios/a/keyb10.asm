;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosError			: PROC
		PUBLIC	BiosFullKeyboardWait
;
; DECLARATION	int BiosFullKeyboardWait( void );
;
PROC		BiosFullKeyboardWait	WATCOM_C
		mov	ah,KEYBOARD_WAIT_FULL_KEY	; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		jc	BiosError			; Success ?
		movzx	eax,ax				; Yes, return scan code and character code
		ret
ENDP
		END
