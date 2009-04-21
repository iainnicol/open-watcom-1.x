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
		PUBLIC	DosDiskReset
;
; DECLARATION	int DosDiskReset( void );
;
PROC		DosDiskReset		WATCOM_C
		mov	ah,DOS_DISK_RESET		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
