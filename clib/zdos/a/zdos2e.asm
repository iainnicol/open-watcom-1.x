;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSetVerifyFlag
;
; DECLARATION	int DosSetVerifyFlag( int onoff );
;
PROC		DosSetVerifyFlag	WATCOM_C
		mov	ah,DOS_SET_VERIFY_FLAG		; AH = DOS function
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
