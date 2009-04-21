;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetDefaultCodePage
;
; DECLARATION	int DosGetDefaultCodePage( void );
;
PROC		DosGetDefaultCodePage	WATCOM_C
		USES	edx,ebx
		;
		; Get function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_CODE_PAGE SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		mov	eax,edx				; Yes, return default code page
		ret
@@Error:	neg	eax				; Return negated DOS error code
		ret
ENDP
		END
