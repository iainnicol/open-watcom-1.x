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
		PUBLIC	BiosUartInput
;
; DECLARATION	int BiosUartInput( int portnumber );
;
PROC		BiosUartInput		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = port number
		mov	ah,UART_INPUT			; AH = function number
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
		movzx	eax,ax				; Yes, return port status and read character
		ret
ENDP
		END
