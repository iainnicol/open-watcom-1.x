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
		PUBLIC	BiosBufferedUartOutput
;
; DECLARATION	int BiosBufferedUartOutput( int count, int portnumber,
;                                           void *buffer );
;
PROC		BiosBufferedUartOutput	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to write
		mov	ah,UART_BUFFERED_OUTPUT		; AH = function number
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
