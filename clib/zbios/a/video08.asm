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
		PUBLIC	BiosReadCharAndAttribute_
;
; DECLARATION	int BiosReadCharAndAttribute( int *character, int *attribute );
;
PROC		BiosReadCharAndAttribute_ STDCALL
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX points to character variable
		mov	ah,VIDEO_READ_CHAR_ATTRIB	; AH = video function
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
		movzx	ebx,al				; EBX = character
		mov	[ecx],ebx			; Store character
		movzx	ebx,ah				; EBX = attribute
		mov	[edx],ebx			; Store attribute
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnZero			; Process return code
ENDP
IFDEF __ZDOSDRV__
		UDATASEG
		EXTRN	C VideoPage			: BYTE
ENDIF
		END
