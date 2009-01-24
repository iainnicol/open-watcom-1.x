;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosGetVideoMode_
;
; DECLARATION	int BiosGetVideoMode( VMODE *vmode );
;
PROC		BiosGetVideoMode_	STDCALL
		push	edx				; Save context
		push	ebx
		mov	edx,eax				; EDX points to VMODE block
		mov	ah,VIDEO_GET_MODE		; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosVideo]
ELSE
		int	BIOS_VIDEO
ENDIF
		mov	[WORD (VMODE edx).Mode],ax	; Store mode and columns
		mov	[WORD (VMODE edx).Rows],bx	; Store rows and page
		pop	ebx				; Restore context
		pop	edx
		jmp	BiosReturnZero			; Process return code
ENDP
		END
