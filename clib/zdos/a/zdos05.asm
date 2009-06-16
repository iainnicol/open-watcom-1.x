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
		PUBLIC	DosPrinterOutput
;
; DECLARATION	int DosPrinterOutput( int character );
;
PROC		DosPrinterOutput	WATCOM_C
		push	edx				; Save context
		mov	ah,DOS_PRINTER_OUTPUT		; AH = DOS function
		mov	dl,al				; DL = character to write
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
