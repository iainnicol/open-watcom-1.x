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
		PUBLIC	DosSocketShutdown
;
; DECLARATION	int DosSocketShutdown( int how, unsigned handle );
;
PROC		DosSocketShutdown	WATCOM_C
		push	ebx				; Save context
		mov	ebx,edx				; EBX = handle
		mov	ah,SOCKET_SHUTDOWN		; AH = function number
		;
		; Shutdown socket functionality
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
