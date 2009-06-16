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
		PUBLIC	DosSetEnvVariable
;
; DECLARATION	int DosSetEnvVariable( char *string );
;
PROC		DosSetEnvVariable	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to string
		mov	ah,DOS_SET_ENVIRONMENT_VARIABLE	; AH = DOS function
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
