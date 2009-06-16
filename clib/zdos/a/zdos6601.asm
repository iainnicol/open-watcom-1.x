;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetActiveCodePage
;
; DECLARATION	int DosGetActiveCodePage( void );
;
PROC		DosGetActiveCodePage	WATCOM_C
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
		mov	eax,ebx				; Yes, return active code page
		ret
@@Error:	neg	eax				; Return negated DOS error code
		ret
ENDP
		END
