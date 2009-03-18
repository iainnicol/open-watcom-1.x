;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'SOCKET.INC'
		INCLUDE	'ERRNO.INC'
		CODESEG
		PUBLIC	SocketError
;
; PROCEDURE	SocketError
;
; INPUT		EAX = error code
;
; OUTPUT	EAX = -1
;
; DESCRIPTION	Converts error code to socket compatible values, saves it in
;		errno and returns -1.
;
PROC		SocketError
		cmp	eax,SOCKET_INVALID_POINTER	; Above highest socket error ?
		jbe	SHORT @@Translate		; No, translate error code
		mov	eax,SOCKET_INVALID_POINTER + 1	; Yes, use highest socket error + 1
@@Translate:	movzx	eax,[ErrorTable + eax]		; EAX = translated error code
@@SetErrno:	mov	[errno],eax			; Update errno
		mov	eax,-1				; EAX = return value
		ret
ENDP
		DATASEG
ErrorTable	DB	EZERO				; 00h = ?
		DB	ENOSYS				; 01h = SOCKET_INVALID_FUNCTION
		DB	EINVAL				; 02h =	SOCKET_INVALID_TYPE
		DB	EIO				; 03h = SOCKET_NO_ROUTE
		DB	EEXIST				; 04h = SOCKET_IN_USE
		DB	EIO				; 05h = SOCKET_TRANSMIT_FAILED
		DB	EIO				; 06h = SOCKET_FRAGMENT_ERROR
		DB	EINVAL				; 07h = SOCKET_INVALID_STATE
		DB	EBADF				; 08h = SOCKET_NOT_IN_USE
		DB	EINVAL				; 09h = SOCKET_INVALID_ADDRESS
		DB	EBADF				; 0ah = SOCKET_INVALID_HANDLE
		DB	EINVAL				; 0bh = SOCKET_INVALID_PORT
		DB	EINVAL				; 0ch = SOCKET_NOT_BOUND
		DB	EINVAL				; 0dh = SOCKET_ALREADY_BOUND
		DB	EIO				; 0eh = SOCKET_CONNECTION_FAILED
		DB	EIO				; 0fh = SOCKET_CANT_READ
		DB	EIO				; 10h = SOCKET_CANT_WRITE
		DB	EFAULT				; 11h = SOCKET_INVALID_POINTER
		DB	ENOMEM				; 12h = any error
		UDATASEG
		EXTRN	C errno				: DWORD
		END
