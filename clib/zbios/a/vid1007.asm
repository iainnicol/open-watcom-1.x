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
		PUBLIC	BiosGetPalette
;
; DECLARATION	int BiosGetPalette( int index );
;
PROC		BiosGetPalette		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	bl,al				; BL = register index
		mov	eax,VIDEO_GET_PALETTE		; AH = video function, AL = subfunction
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	cl,[VideoPage]			; CL = console number
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		mov	al,bh				; AL = color
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnAL			; Process return code
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
