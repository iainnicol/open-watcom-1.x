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
		PUBLIC	shutdown
;
; DECLARATION	int shutdown( int s, int how );
;
PROC		shutdown		WATCOM_C
		shl	eax,2				; EAX = socket handle
		mov	ebx,eax				; EBX = socket handle
		mov	al,dl				; AL = socket operation(s) to shutdown
		mov	ah,SOCKET_SHUTDOWN		; AH = function number
		;
		; Shutdown socket operation(s)
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
