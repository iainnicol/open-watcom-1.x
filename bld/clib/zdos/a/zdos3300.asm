;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosGetBreakFlag_
;
; DECLARATION	int DosGetBreakFlag( void );
;
PROC		DosGetBreakFlag_		STDCALL
		push	edx				; Save context
		mov	eax,DOS_GET_SET_BREAK_FLAG SHL 8; AH = DOS function, AL = subfunction
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		movzx	eax,dl				; Yes, EAX = break flag
		pop	edx				; Restore context
		ret
@@Error:	neg	eax				; Negate error code
		pop	edx				; Restore context
		ret
ENDP
		END
