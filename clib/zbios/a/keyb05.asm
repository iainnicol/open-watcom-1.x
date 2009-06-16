;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosKeyboardPutKey
;
; DECLARATION	int BiosKeyboardPutKey( int character, int scancode );
;
PROC		BiosKeyboardPutKey	WATCOM_C
		push	ecx				; Save context
		mov	cl,al				; CL = character code
		mov	ch,dl				; CH = scan code
		mov	ah,KEYBOARD_PUT_KEY		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		pop	ecx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
