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
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSocketListen
;
; DECLARATION	int DosSocketListen( unsigned handle );
;
PROC		DosSocketListen		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = handle
		mov	ah,SOCKET_LISTEN		; AH = function number
		;
		; Start listening on the socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
