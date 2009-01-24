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
		PUBLIC	BiosGetMedia_
;
; DECLARATION	int BiosGetMedia( int drive );
;
PROC		BiosGetMedia_		STDCALL
		push	edx				; Save context
		mov	dl,al				; DL = drive
		xor	al,al				; Clear AL
		mov	ah,DISK_GET_SET_DRIVE_TYPE	; AH = disk function
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
