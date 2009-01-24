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
		PUBLIC	DosSocketSend_
;
; DECLARATION	int DosSocketSend( int flags, void *buffer,
;		                   unsigned handle, int length );
;
PROC		DosSocketSend_		STDCALL
		mov	ah,SOCKET_SEND			; AH = function number
		;
		; Send data
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	DosError			; Success ?
		ret
ENDP
		END
