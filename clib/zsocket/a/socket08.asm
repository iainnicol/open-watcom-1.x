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
		PUBLIC	listen
;
; DECLARATION	int listen( int s, int backlog );
;
PROC		listen			WATCOM_C
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		mov	ah,SOCKET_LISTEN		; AH = function number
		;
		; Start listening
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	SocketError			; Error ?
		ret
ENDP
		END
