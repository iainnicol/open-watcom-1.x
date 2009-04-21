;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosGetCurrentDriveInfo
;
; DECLARATION	int DosGetCurrentDriveInfo( DRVINFO *info );
;
PROC		DosGetCurrentDriveInfo	WATCOM_C
		push	edi				; Save context
		mov	edi,eax				; EDI points to DRVINFO buffer
		mov	ah,DOS_GET_CURRENT_DRIVE_INFO	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edi				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
