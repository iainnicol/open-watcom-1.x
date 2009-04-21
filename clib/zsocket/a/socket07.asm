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
		PUBLIC	ioctlsocket
;
; DECLARATION	int ioctlsocket( int s, long cmd, unsigned long *argp );
;
PROC		ioctlsocket		WATCOM_C
		push	ecx				; Save context
		push	ebx
		shl	eax,2				; EAX = socket handle
		mov	ecx,edx				; ECX = command
		mov	edx,[ebx]			; EDX = argument
		mov	ebx,eax				; EBX = socket handle
		mov	ah,SOCKET_IOCTL			; AH = function number
		;
		; Do IOCTL function
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jc	SocketError			; Error ?
		mov	[ebx],eax			; No, update callers variable
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
