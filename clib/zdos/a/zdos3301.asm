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
		PUBLIC	DosSetBreakFlag
;
; DECLARATION	int DosSetBreakFlag( int newflag );
;
PROC		DosSetBreakFlag		WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = new flag
		;
		; Get function and subfunction number in AH and AL
		;
		mov	eax,DOS_GET_SET_BREAK_FLAG SHL 8 + 1
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
