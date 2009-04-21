;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZIPV4.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSocketBind
;
; DECLARATION	int DosSocketBind( int port, unsigned ip, unsigned handle );
;
PROC		DosSocketBind		WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = port number
		mov	ah,SOCKET_BIND			; AH = function number
		;
		; Bind the socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
