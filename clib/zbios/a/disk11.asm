;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosRecalibrateDrive
;
; DECLARATION	int BiosRecalibrateDrive( int drive );
;
PROC		BiosRecalibrateDrive	WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = drive
		mov	ah,DISK_DRIVE_STATUS		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	edx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
