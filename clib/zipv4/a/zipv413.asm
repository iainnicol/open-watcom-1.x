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
		PUBLIC	DosLinkInformation
;
; DECLARATION	int DosLinkInformation( int linkno, LINKINFO *linkinfo );
;
PROC		DosLinkInformation	WATCOM_C
		mov	ah,LINK_INFORMATION		; AH = function number
		;
		; Get link information
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
