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
		PUBLIC	DosSocketGetOption_
;
; DECLARATION	int DosSocketGetOption( int level, unsigned *value,
;		                        unsigned handle, int option );
;
PROC		DosSocketGetOption_	STDCALL
		mov	ah,SOCKET_GET_OPTION		; AH = function number
		;
		; Get socket option
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		jc	DosError			; Success ?
		mov	[edx],eax			; Yes, store option value in callers variable
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
