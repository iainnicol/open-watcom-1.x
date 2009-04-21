;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	break_off
;
; DECLARATION	void break_off( void );
;
PROC		break_off		WATCOM_C
		USES	edx,eax
		;
		; Get function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_BREAK_FLAG SHL 8 + 1
		xor	dl,dl				; DL = new break flag
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
