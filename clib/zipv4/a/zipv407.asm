;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZIPV4.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosSocketReceive
;
; DECLARATION	int DosSocketReceive( int flags, void *buffer,
;		                      unsigned handle, int length );
;
PROC		DosSocketReceive	WATCOM_C
		mov	ah,SOCKET_RECEIVE		; AH = function number
		;
		; Receive data
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
