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
		PUBLIC	BiosSetBlinkBit
;
; DECLARATION	int BiosSetBlinkBit( int blinkbit );
;
PROC		BiosSetBlinkBit		WATCOM_C
		push	ecx				; Save context
		push	ebx
		movzx	ebx,al				; EBX = blink bit
		mov	eax,VIDEO_CHANGE_BLINK_BIT	; AH = video function, AL = subfunction
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	cl,[VideoPage]			; CL = console number
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnZero			; Process return code
ENDP
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
		END
