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
		PUBLIC	DosSocketConnect
;
; DECLARATION	int DosSocketConnect( int port, unsigned ip, unsigned handle );
;
PROC		DosSocketConnect	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = port number
		mov	ah,SOCKET_CONNECT		; AH = function number
		;
		; Connect the socket
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosSocketDriver]
ELSE
		int	SOCKET
ENDIF
		pop	ecx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
