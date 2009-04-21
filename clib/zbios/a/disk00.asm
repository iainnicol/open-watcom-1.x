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
		PUBLIC	BiosDiskReset
;
; DECLARATION	int BiosDiskReset( int drive );
;
PROC		BiosDiskReset		WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = drive
		mov	ah,DISK_RESET			; AH = disk function
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
