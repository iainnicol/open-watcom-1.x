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
		PUBLIC	BiosBufferedUartInput
;
; DECLARATION	int BiosBufferedUartInput( int count, int portnumber,
;                                          void *buffer );
;
PROC		BiosBufferedUartInput	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to read
		mov	ah,UART_BUFFERED_INPUT		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		pop	ecx				; Restore context
		jc	BiosError			; Success ?
		movzx	eax,ax				; Yes, return port and modem status
		ret
ENDP
		END
