;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	break_on_
;
; DECLARATION	void break_on( void );
;
PROC		break_on_		STDCALL
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
