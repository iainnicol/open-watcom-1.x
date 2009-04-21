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
		PUBLIC	DosDeleteDirectory
;
; DECLARATION	int DosDeleteDirectory( char *path );
;
PROC		DosDeleteDirectory	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to path
		mov	ah,DOS_DELETE_DIRECTORY		; AH = DOS function number
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
