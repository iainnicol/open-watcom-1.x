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
		PUBLIC	accept
;
; DECLARATION	int accept( int s, struct sockaddr *addr, int *len );
;
PROC		accept			WATCOM_C
		mov	[DWORD edx],SIZE INET		; Store the length
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		mov	ah,SOCKET_ACCEPT		; AH = function number
		;
		; Accept a new connection
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	SocketError			; Process error code
		push	ecx				; Save context
		push	edx				; Save pointer to INET block
		mov	ebx,eax				; EBX = new socket handle
		mov	ah,SOCKET_REMOTE_ADDRESS	; AH = function number
		;
		; Get remote IP address and port number
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	eax				; EAX points to INET block
		mov	[(INET eax).Port],cx		; Store port address
		pop	ecx				; Restore context
		mov	[(INET eax).Address],edx	; Store IP address
		mov	[(INET eax).Family],AF_INET	; Store family
		mov	eax,ebx				; EAX = new socket handle
		shr	eax,2				; We need to return an positive value
		ret
ENDP
		END
