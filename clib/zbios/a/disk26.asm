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
		PUBLIC	BiosAtapiPacketCommand
;
; DECLARATION	int BiosAtapiPacketCommand( void *command, int drive,
;                                           void *buffer, int count );
;
PROC		BiosAtapiPacketCommand	WATCOM_C
		push	esi				; Save context
		mov	esi,eax				; ESI points to command packet
		mov	ah,DISK_PACKET_COMMAND		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	esi				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
