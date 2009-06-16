;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	break_on
;
; DECLARATION	void break_on( void );
;
PROC		break_on		WATCOM_C
		USES	edx,eax
		;
		; Get function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_BREAK_FLAG SHL 8 + 1
		mov	dl,1				; DL = new break flag
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret
ENDP
		END
