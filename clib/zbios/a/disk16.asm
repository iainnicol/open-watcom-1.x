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
		PUBLIC	BiosChangeLineStatus
;
; DECLARATION	int BiosChangeLineStatus( int drive );
;
PROC		BiosChangeLineStatus	WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = drive
		mov	ah,DISK_CHANGE_LINE_STATUS	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	edx				; Restore context
		mov	al,ah				; Get status in AL
		jmp	BiosReturnAL			; Process return code
ENDP
		END
