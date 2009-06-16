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
		PUBLIC	DosLinkClose
;
; DECLARATION	int DosLinkClose( int linkno );
;
PROC		DosLinkClose		WATCOM_C
		mov	ah,LINK_CLOSE			; AH = function number
		;
		; Close the link to packet driver
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
