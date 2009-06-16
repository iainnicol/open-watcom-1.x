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
		PUBLIC	BiosUartStatus
;
; DECLARATION	int BiosUartStatus( int portnumber );
;
PROC		BiosUartStatus		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = port number
		mov	ah,UART_STATUS			; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		pop	edx				; Restore context
		jc	BiosError			; Success ?
		movzx	eax,ax				; Yes, return port and modem status
		ret
ENDP
		END
