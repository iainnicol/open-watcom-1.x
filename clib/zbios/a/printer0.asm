;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosPrinterOutput
;
; DECLARATION	int BiosPrinterOutput( int character, int printerport );
;
PROC		BiosPrinterOutput	WATCOM_C
		mov	ah,PRINTER_OUTPUT		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosPrinter]
ELSE
		int	BIOS_PRINTER
ENDIF
		mov	al,ah				; AL = status
		jmp	BiosReturnAL			; Process return code
ENDP
		END
