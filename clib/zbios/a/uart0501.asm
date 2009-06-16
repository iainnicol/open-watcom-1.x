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
		PUBLIC	BiosSetModemControl
;
; DECLARATION	int BiosSetModemControl( int control, int portnumber );
;
PROC		BiosSetModemControl	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = control value
		;
		; Get function numbers in AH and AL
		;
		mov	eax,UART_GET_SET_CONTROL SHL 8 + 1
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		pop	ebx				; Restore context
		jc	BiosError			; Success ?
		movzx	eax,ax				; Yes, return port and modem status
		ret
ENDP
		END
