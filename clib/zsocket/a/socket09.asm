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
		PUBLIC	recv
;
; DECLARATION	int recv( int s, char *buf, int len, int flags );
;
PROC		recv			WATCOM_C
		shl	eax,2				; EAX = socket handle
		xchg	ebx,ecx				; EBX = flags, ECX = len
		xchg	eax,ebx				; EAX = flags, EBX = socket handle
		mov	ah,SOCKET_RECEIVE		; AH = function number
		;
		; Receive data
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
