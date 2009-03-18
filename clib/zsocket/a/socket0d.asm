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
		PUBLIC	sendto_
;
; DECLARATION	int sendto( int s, char *buf, int len, int flags,
;                           const struct sockaddr *addr, int tolen );
;
PROC		sendto_			STDCALL
		ARG	ipaddr : DWORD, tolen : DWORD
		USES	edi,esi
		shl	eax,2				; EAX = socket handle
		xchg	ebx,ecx				; EBX = flags, ECX = len
		xchg	eax,ebx				; EAX = flags, EBX = socket handle
		mov	edi,[ipaddr]			; EDI points to INET block
		mov	esi,[(INET edi).Address]	; ESI = destination IP address
		movzx	edi,[(INET edi).Port]		; EDI = destination port number
		mov	ah,SOCKET_SEND_TO		; AH = function number
		;
		; Send data
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jnc	SHORT @@Exit			; Error ?
		call	SocketError			; Yes, process error code
@@Exit:		ret
ENDP
		END
