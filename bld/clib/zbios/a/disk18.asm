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
		PUBLIC	BiosSetMediaType_
;
; DECLARATION	int BiosSetMediaType( int drive, int maxtrack, int sectors );
;
PROC		BiosSetMediaType_	STDCALL
		push	ecx				; Save context
		mov	ch,dl				; CH = maximum track number
		mov	cl,bl				; CL = sectors/track
		mov	dl,al				; DL = drive
		mov	ah,DISK_SET_MEDIA_TYPE		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	ecx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
