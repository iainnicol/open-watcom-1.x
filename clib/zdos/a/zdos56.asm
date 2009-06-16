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
		PUBLIC	DosRenameFile
;
; DECLARATION	int DosRenameFile( char *current, char *new );
;
PROC		DosRenameFile		WATCOM_C
		push	edi				; Save context
		push	edx
		mov	edi,edx				; EDI points to new name
		mov	edx,eax				; EDX points to current name
		mov	ah,DOS_RENAME_FILE		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
