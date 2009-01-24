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
		PUBLIC	DosLinkOpen_
;
; DECLARATION	int DosLinkOpen( int pktdrvno, unsigned gateway,
;                                unsigned ip, unsigned netmask );
;
PROC		DosLinkOpen_		STDCALL
		mov	ah,LINK_OPEN			; AH = function number
		;
		; Open a link to packet driver
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
