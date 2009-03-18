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
		PUBLIC	getsockname_
;
; DECLARATION	int getsockname( int s, struct sockaddr *addr, int *len );
;
PROC		getsockname_		STDCALL
		push	ecx				; Save context
		push	edx				; Save pointer to INET block
		mov	[DWORD ebx],SIZE INET		; Store the length
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		mov	ah,SOCKET_LOCAL_ADDRESS		; AH = function number
		;
		; Get local IP address and port number
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ebx				; EBX points to INET block
		mov	[(INET ebx).Port],cx		; Store port address
		mov	[(INET ebx).Address],edx	; Store IP address
		mov	[(INET ebx).Family],AF_INET	; Store family
		pop	ecx				; Restore context
		jc	SocketError			; Process error code
		ret
ENDP
		END
