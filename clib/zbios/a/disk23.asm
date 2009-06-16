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
		PUBLIC	BiosWriteDiskBlock
;
; DECLARATION	int BiosWriteDiskBlock( int count, int drive, void *buffer,
;		                        unsigned LBA );
;
PROC		BiosWriteDiskBlock	WATCOM_C
		mov	ah,DISK_WRITE_SECTOR_LBA	; AH = disk function
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
