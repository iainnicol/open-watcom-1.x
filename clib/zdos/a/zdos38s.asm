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
		PUBLIC	DosSetCountryInformation
;
; DECLARATION	int DosSetCountryInformation( int code );
;
PROC		DosSetCountryInformation WATCOM_C
		push	edx				; Save context
		push	ebx
		mov	edx,-1				; EDX = -1
		mov	ebx,eax				; Assume code > 255
		test	ebx,NOT 255			; Code < 255 ?
		jz	SHORT @@DoFunction		; No, do function
		mov	al,-1				; Yes, indicate code in EBX
		;
		; Get DOS function number in AH
		;
@@DoFunction:	mov	ah,DOS_GET_SET_COUNTRY_INFORMATION
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		pop	edx
		jmp	DosReturnZero			; Process return code
ENDP
		END
