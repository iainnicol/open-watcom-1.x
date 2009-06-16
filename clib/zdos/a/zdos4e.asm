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
		PUBLIC	DosFindFirstFile
;
; DECLARATION	int DosFindFirstFile( int attr, char *path, FIND *find );
;
PROC		DosFindFirstFile	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = search attributes
		mov	ah,DOS_FIND_FIRST_FILE		; AH = DOS function number
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
