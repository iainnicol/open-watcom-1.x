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
		PUBLIC	DosGetCurrentDirectory
;
; DECLARATION	int DosGetCurrentDirectory( int drive, char *buffer );
;
PROC		DosGetCurrentDirectory	WATCOM_C
		push	esi				; Save context
		push	edx
		mov	esi,edx				; ESI points to buffer
		mov	dl,al				; DL = logical drive number
		mov	ah,DOS_GET_CURRENT_DIRECTORY	; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		pop	esi
		jmp	DosReturnZero			; Process return code
ENDP
		END
