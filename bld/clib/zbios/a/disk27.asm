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
		PUBLIC	BiosSeekDiskBlock_
;
; DECLARATION	int BiosSeekDiskBlock( unsigned LBA, int drive );
;
PROC		BiosSeekDiskBlock_	STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = LBA
		mov	ah,DISK_SEEK_LBA		; AH = disk function
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
