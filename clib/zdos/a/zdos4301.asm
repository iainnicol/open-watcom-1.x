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
		PUBLIC	DosSetFileAttributes
;
; DECLARATION	int DosSetFileAttributes( int attributes, char *path );
;
PROC		DosSetFileAttributes	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = new file attributes
		;
		; Get function numbers in EAX
		;
		mov	eax,DOS_GET_SET_FILE_ATTRIBUTES SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
