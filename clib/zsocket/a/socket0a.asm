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
		PUBLIC	recvfrom
;
; DECLARATION	int recvfrom( int s, char *buf, int len, int flags,
;                             struct sockaddr *addr, int *fromlen );
;
PROC		recvfrom		WATCOM_C
		ARG	s : DWORD, buf : DWORD, len : DWORD, \
			flags : DWORD, ipaddr : DWORD, fromlen : DWORD
		shl	eax,2				; EAX = socket handle
		xchg	ebx,ecx				; EBX = flags, ECX = len
		xchg	eax,ebx				; EAX = flags, EBX = socket handle
		mov	ah,SOCKET_RECEIVE_FROM		; AH = function number
		;
		; Receive data
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	SHORT @@Error			; Error ?
		mov	ebx,[fromlen]			; No, EBX points to fromlen variable
		mov	[DWORD ebx],SIZE INET		; Store length of INET block
		mov	ebx,[ipaddr]			; EBX points to ipaddr variable
		mov	[(INET ebx).Port],cx		; Store port number
		mov	[(INET ebx).Address],edx	; Store IP address
		mov	[(INET ebx).Family],AF_INET	; Store family
@@Exit:		ret
@@Error:	call	SocketError			; Process error code
		jmp	@@Exit				; We are done
ENDP
		END
