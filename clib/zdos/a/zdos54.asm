;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		PUBLIC	DosGetVerifyFlag
;
; DECLARATION	int DosGetVerifyFlag( void );
;
PROC		DosGetVerifyFlag	WATCOM_C
		mov	ah,DOS_GET_VERIFY_FLAG		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	DosReturnAL			; Process return code
ENDP
		END
