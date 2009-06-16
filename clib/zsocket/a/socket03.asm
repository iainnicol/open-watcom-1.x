;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'SOCKET.INC'
		INCLUDE	'ZSOCKET.INC'
		CODESEG
		EXTRN	SocketError			: PROC
		PUBLIC	connect
;
; DECLARATION	int connect( int s, struct sockaddr *addr, int *len );
;
PROC		connect			WATCOM_C
		push	ecx				; Save context
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		movzx	ecx,[(INET edx).Port]		; ECX = port number
		mov	edx,[(INET edx).Address]	; EDX = IP address
		mov	ah,SOCKET_CONNECT		; AH = function number
		;
		; Connect the socket
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
