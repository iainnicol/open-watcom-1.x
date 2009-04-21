;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosError			: PROC
		PUBLIC	BiosUartOutput
;
; DECLARATION	int BiosUartOutput( int byte, int portnumber );
;
PROC		BiosUartOutput		WATCOM_C
		mov	ah,UART_OUTPUT			; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		jc	BiosError			; Success ?
		movzx	eax,ax				; Yes, return port status and written character
		ret
ENDP
		END
