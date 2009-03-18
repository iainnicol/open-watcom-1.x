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
		PUBLIC	select_
;
; DECLARATION	int select( int ndfs, fd_set *readfds, fd_set *writefds,
;                           fd_set *exceptfds, const struct timeval *timeout );
;
PROC		select_			STDCALL
		ARG	timeout : DWORD
		USES	esi
		mov	eax,[timeout]			; EAX points to timeout structure
		mov	esi,[eax]			; EAX = seconds
		shl	esi,10				; Convert to periodic ticks
		mov	eax,[eax + 4]			; EAX = microseconds
		add	eax,1095			; Round up to milliseconds
		shr	eax,10				; EAX = time in milliseconds
		add	esi,eax				; ESI = time to wait
		mov	ah,SOCKET_SELECT		; AH = function number
		;
		; Receive data
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
