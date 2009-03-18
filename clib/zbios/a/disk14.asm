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
		PUBLIC	BiosDiskDiagnostics_
;
; DECLARATION	int BiosDiskDiagnostics( void );
;
PROC		BiosDiskDiagnostics_	STDCALL
		push	edx				; Save context
		mov	dl,80h				; DL = fixed disk drive
		mov	ah,DISK_DIAGNOSTICS		; AH = disk function
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
