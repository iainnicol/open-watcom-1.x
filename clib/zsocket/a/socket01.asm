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
		PUBLIC	bind_
;
; DECLARATION	int bind( int s, struct sockaddr *addr, int *len );
;
PROC		bind_			STDCALL
		push	ecx				; Save context
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		movzx	ecx,[(INET edx).Port]		; ECX = port number
		mov	edx,[(INET edx).Address]	; EDX = IP address
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
		jc	SocketError			; Process error code
		ret
ENDP
		END
