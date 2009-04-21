;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetAndSetBreakFlag
;
; DECLARATION	int DosGetAndSetBreakFlag( int breakflag );
;
PROC		DosGetAndSetBreakFlag	WATCOM_C
		push	edx				; Save context
		mov	dl,al				; DL = new flag
		;
		; Get function and subfunction number in AH and AL
		;
		mov	eax,DOS_GET_SET_BREAK_FLAG SHL 8 + 2
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		movzx	eax,dl				; Yes, EAX = old break flag
		pop	edx				; Restore context
		ret
@@Error:	neg	eax				; Negate error code
		pop	edx				; Restore context
		ret
ENDP
		END
