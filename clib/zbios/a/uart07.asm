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
		PUBLIC	BiosCloseUart
;
; DECLARATION	int BiosCloseUart( int portnumber );
;
PROC		BiosCloseUart		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = port number
		mov	ah,UART_CLOSE			; AH = function number
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
