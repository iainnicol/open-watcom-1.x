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
		PUBLIC	DosSetCurrentDrive
;
; DECLARATION	int DosSetCurrentDrive( int drive );
;
PROC		DosSetCurrentDrive	WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = drive number
		mov	ah,DOS_SET_CURRENT_DRIVE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
