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
		PUBLIC	BiosReadDiskBlock
;
; DECLARATION	int BiosReadDiskBlock( int count, int drive, void *buffer,
;		                       unsigned LBA );
;
PROC		BiosReadDiskBlock	WATCOM_C
		mov	ah,DISK_READ_SECTOR_LBA		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		jmp	BiosReturnAL			; Process return code
ENDP
		END
