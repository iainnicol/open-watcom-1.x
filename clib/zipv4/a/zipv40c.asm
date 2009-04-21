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
		PUBLIC	DosSocketSetOption
;
; DECLARATION	int DosSocketSetOption( int level, unsigned value,
;		                        unsigned handle, int option );
;
PROC		DosSocketSetOption	WATCOM_C
		mov	ah,SOCKET_SET_OPTION		; AH = function number
		;
		; Set socket option
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
