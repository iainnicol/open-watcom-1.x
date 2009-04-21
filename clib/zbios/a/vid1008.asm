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
		PUBLIC	BiosGetBorder
;
; DECLARATION	int BiosGetBorder( void );
;
PROC		BiosGetBorder		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	eax,VIDEO_GET_OVERSCAN		; AH = video function, AL = subfunction
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	cl,[VideoPage]			; CL = console number
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		mov	al,bh				; AL = border color
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnAL			; Process return code
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	WATCOM_C VideoPage		: BYTE
ENDIF
		END
