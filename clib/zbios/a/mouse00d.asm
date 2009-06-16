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
		PUBLIC	BiosDisableMouse
;
; DECLARATION	int BiosDisableMouse( void );
;
PROC		BiosDisableMouse	WATCOM_C
		push	ebx				; Save context
		xor	bh,bh				; BH = disable flag
		mov	eax,MISC_MOUSE_SERVICES SHL 8 +\; AH = function number
			    MOUSE_ENABLE_DISABLE	; AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
