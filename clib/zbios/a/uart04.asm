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
		PUBLIC	BiosExtendedUartSetup
;
; DECLARATION	int BiosExtendedUartSetup( int break, int portnumber,
;		                           int stopbits, int baudrate,
;		                           int parity, int databits );
;
PROC		BiosExtendedUartSetup	WATCOM_C
		ARG	Break : DWORD, PortNumber : DWORD, StopBits : DWORD, \
			BaudRate : DWORD, Parity : DWORD, DataBits : DWORD
		mov	bh,[BYTE Parity]		; BH = parity
		mov	ch,[BYTE DataBits]		; CH = data bits
		mov	ah,UART_EXTENDED_SETUP		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		jc	SHORT @@Error			; Success
		movzx	eax,ax				; Yes, return port and modem status
		ret
@@Error:	call	BiosError			; Process return code
		ret
ENDP
		END
