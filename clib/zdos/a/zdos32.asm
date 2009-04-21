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
		PUBLIC	DosGetDriveInfo
;
; DECLARATION	int DosGetDriveInfo( int drive, DRVINFO *info );
;
PROC		DosGetDriveInfo		WATCOM_C
		push	edi				; Save context
		mov	edi,edx				; EDI points to DRVINFO buffer
		mov	dl,al				; DL = logical drive number
		mov	ah,DOS_GET_DRIVE_INFO		; AH = DOS function
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
