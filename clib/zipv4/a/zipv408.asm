;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZIPV4.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosSocketReceiveFrom
;
; DECLARATION	int DosSocketReceiveFrom( int flags, void *buffer,
;		                          unsigned handle, int length,
;		                          unsigned *ip, int *port );
;
PROC		DosSocketReceiveFrom	WATCOM_C
		ARG	flags : DWORD, buffer : DWORD, handle : DWORD, \
			len : DWORD, ip : DWORD, port : DWORD
		mov	ah,SOCKET_RECEIVE_FROM		; AH = function number
		;
		; Receive data
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]		; Receive from socket
ELSE
		int	SOCKET
ENDIF
		jc	SHORT @@Exit			; Success ?
		mov	ebx,[ip]			; Yes, EBX points to ip variable
		mov	[ebx],edx			; Store ip address in variable
		mov	ebx,[port]			; EBX points to port variable
		mov	[ebx],ecx			; Store port number in variable
		ret
@@Exit:		call    DosError			; Process return code
		ret
ENDP
		END
