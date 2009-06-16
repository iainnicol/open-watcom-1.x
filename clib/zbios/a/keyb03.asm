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
		PUBLIC	BiosKeyboardRate
;
; DECLARATION	int BiosKeyboardRate( int rate, int delay );
;
PROC		BiosKeyboardRate	WATCOM_C
		push	ebx				; Save context
		mov	bl,al				; BL = repeat rate
		mov	bh,dl				; BH = repeat delay
		mov	eax,KEYBOARD_RATE SHL 8 + 5	; AH = function number, AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosKeyboard]
ELSE
		int	BIOS_KEYBOARD
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
