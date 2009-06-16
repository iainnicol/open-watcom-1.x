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
		PUBLIC	BiosSetMouseResolution
;
; DECLARATION	int BiosSetMouseResolution( int resolution );
;
PROC		BiosSetMouseResolution	WATCOM_C
		push	ebx				; Save context
		mov	bh,al				; BH = resolution
		mov	eax,MISC_MOUSE_SERVICES SHL 8 +\; AH = function number
			    MOUSE_SET_RESOLUTION	; AL = subfunction number
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
