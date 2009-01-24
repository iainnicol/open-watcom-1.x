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
		PUBLIC	DosSocketOpen_
;
; DECLARATION	int DosSocketOpen( int sockettype, int protocol,
;                                  unsigned *handle );
;
PROC		DosSocketOpen_		STDCALL
		push	ebx				; Save context
		mov	bl,dl				; BL = protocol
		mov	ah,SOCKET_OPEN			; AH = function number
		;
		; Open a socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		mov	[ebx],eax			; Yes, save handle in callers variable
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
