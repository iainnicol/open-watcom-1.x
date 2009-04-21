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
		PUBLIC	BiosDeviceInformation
;
; DECLARATION	int BiosDeviceInformation( IDEINFO *buffer, int drive );
;
PROC		BiosDeviceInformation	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to buffer
		mov	ah,DISK_DEVICE_INFORMATION	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
