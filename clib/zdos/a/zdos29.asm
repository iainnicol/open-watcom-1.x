;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosGetCommandLine
;
; DECLARATION	int DosGetCommandLine( char *buffer );
;
PROC		DosGetCommandLine	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to buffer
		mov	ah,DOS_GET_COMMAND_LINE		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return length
ENDP
		END
