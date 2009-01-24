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
		PUBLIC	BiosDiskEmulatorPresent_
;
; DECLARATION	int BiosDiskEmulatorPresent( int drive );
;
PROC		BiosDiskEmulatorPresent_ STDCALL
		push	edx				; Save context
		mov	dl,al				; DL = drive
		mov	ah,DISK_EMULATOR_PRESENT	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	edx				; Restore context
		jmp	BiosReturnAL			; Process return code
ENDP
		END
