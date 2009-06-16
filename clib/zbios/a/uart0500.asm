;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosGetModemControl
;
; DECLARATION	int BiosGetModemControl( int portnumber );
;
PROC		BiosGetModemControl	WATCOM_C
		push	edx				; Save context
		push	ebx
		mov	edx,eax				; EDX = port number
		mov	eax,UART_GET_SET_CONTROL SHL 8	; AH = function number, AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosCom]
ELSE
		int	BIOS_COM
ENDIF
		mov	al,bl				; AL = modem control register setting
		pop	ebx				; Restore context
		pop	edx
		jmp	BiosReturnAL			; Process return code
ENDP
		END
