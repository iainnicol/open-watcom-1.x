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
		PUBLIC	DosSocketSendTo_
;
; DECLARATION	int DosSocketSendTo( int flags, void *buffer,
;		                     unsigned handle, int length,
;		                     unsigned ip, int port );
;
PROC		DosSocketSendTo_	STDCALL
		ARG	ip : DWORD, port : DWORD
		push	edi				; Save context
		push	esi
		mov	esi,[ip]			; ESI = IP address
		mov	edi,[port]			; EDI = port number
		mov	ah,SOCKET_SEND_TO		; AH = function number
		;
		; Send data
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	esi				; Restore context
		pop	edi
		call	DosReturnZero			; Process return code
		ret
ENDP
		END
