;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosError			: PROC
		PUBLIC	BiosUartSetup
;
; DECLARATION	int BiosUartSetup( int parameter, int portnumber );
;
PROC		BiosUartSetup		WATCOM_C
		mov	ah,UART_SETUP			; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		jc	BiosError			; Success ?
		movzx	eax,ax				; Yes, return port and modem status
		ret
ENDP
		END
