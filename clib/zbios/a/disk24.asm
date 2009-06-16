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
		PUBLIC	BiosVerifyDiskBlock
;
; DECLARATION	int BiosVerifyDiskBlock(int count, int drive, unsigned LBA);
;
PROC		BiosVerifyDiskBlock	WATCOM_C
		push	ecx				; Save context
		mov	ecx,ebx				; ECX = LBA
		mov	ah,DISK_VERIFY_SECTOR_LBA	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	ecx				; Restore context
		jmp	BiosReturnAL			; Process return code
ENDP
		END
