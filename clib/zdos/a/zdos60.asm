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
		PUBLIC	DosGetActualFileName
;
; DECLARATION	int DosGetActualFileName( char *path, char *buffer );
;
PROC		DosGetActualFileName	WATCOM_C
		push	edi				; Save context
		push	esi
		mov	esi,eax				; ESI points to path to expand
		mov	edi,edx				; EDI points to buffer
		mov	ah,DOS_GET_ACTUAL_FILENAME	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	esi				; Restore context
		pop	edi
		jmp	DosReturnZero			; Process return code
ENDP
		END
