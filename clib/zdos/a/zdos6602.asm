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
		PUBLIC	DosSetActiveCodePage
;
; DECLARATION	int DosSetActiveCodePage( int codepage );
;
PROC		DosSetActiveCodePage	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = new active code page
		;
		; Get function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_CODE_PAGE SHL 8 + 2
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
