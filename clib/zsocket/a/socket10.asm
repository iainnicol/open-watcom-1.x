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
		PUBLIC	socket
;
; DECLARATION	int socket( int af, int type, int protocol );
;
PROC		socket			WATCOM_C
		cmp	al,AF_INET			; Valid family ?
		jnz	SHORT @@BadValue		; No, error
		dec	dl				; Yes, convert to our type
		cmp	dl,SOCKET_RAW			; Valid type ?
		ja	SHORT @@BadValue		; No, error
		mov	al,dl				; Yes, AL = socket type
		mov	ah,SOCKET_OPEN			; AH = function number
		;
		; Create a socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	SocketError			; Error ?
		shr	eax,2				; No, we need to return an positive value
		ret
@@BadValue:	mov	eax,SOCKET_INVALID_TYPE		; EAX = proper error code
		jmp	SocketError			; Translate to errno code and return -1
ENDP
		END
