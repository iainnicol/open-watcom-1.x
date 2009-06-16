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
		PUBLIC	DosSetCurrentDirectory
;
; DECLARATION	int DosSetCurrentDirectory( char *path );
;
PROC		DosSetCurrentDirectory	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to path
		mov	ah,DOS_SET_CURRENT_DIRECTORY	; AH = DOS function number
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
