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
		PUBLIC	BiosPrinterStatus_
;
; DECLARATION	int BiosPrinterStatus( int printerport );
;
PROC		BiosPrinterStatus_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX = printer port number
		mov	ah,PRINTER_STATUS		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosPrinter]
ELSE
		int	BIOS_PRINTER
ENDIF
		pop	edx				; Restore context
		mov	al,ah				; AL = status
		jmp	BiosReturnAL			; Process return code
ENDP
		END
