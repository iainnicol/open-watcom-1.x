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
		PUBLIC	BiosWriteCharAndAttribute_
;
; DECLARATION	int BiosWriteCharAndAttribute( int character, int attribute,
;		                               int count );
;
PROC		BiosWriteCharAndAttribute_ STDCALL
		push	ecx				; Save context
		push	ebx
		mov	ecx,ebx				; ECX = replication count
		mov	bl,dl				; BL = attribute
		mov	ah,VIDEO_WRITE_CHAR_ATTRIB	; AH = video function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		mov	bh,[VideoPage]			; BH = console number
		call	[DWORD DosVideo]
ELSE
		xor	bh,bh				; BH = video page
		int	BIOS_VIDEO
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnZero			; Process return code
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	C VideoPage			: BYTE
ENDIF
		END
