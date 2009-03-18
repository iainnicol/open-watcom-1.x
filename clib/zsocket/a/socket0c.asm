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
		PUBLIC	send_
;
; DECLARATION	int send( int s, char *buf, int len, int flags );
;
PROC		send_			STDCALL
		shl	eax,2				; EAX = socket handle
		xchg	ebx,ecx				; EBX = flags, ECX = len
		xchg	eax,ebx				; EAX = flags, EBX = socket handle
		mov	ah,SOCKET_SEND			; AH = function number
		;
		; Send data
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
