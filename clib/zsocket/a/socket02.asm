;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'SOCKET.INC'
		INCLUDE	'ZSOCKET.INC'
		CODESEG
		EXTRN	SocketError			: PROC
		PUBLIC	closesocket
;
; DECLARATION	int closesocket( int s );
;
PROC		closesocket		WATCOM_C
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		mov	ah,SOCKET_CLOSE			; AH = function number
		;
		; Close the socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	SocketError			; Process error code
		ret
ENDP
		END
