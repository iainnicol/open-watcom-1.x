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
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSocketClose_
;
; DECLARATION	int DosSocketClose( unsigned handle );
;
PROC		DosSocketClose_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = handle
		mov	ah,SOCKET_CLOSE			; AH = function number
		;
		; Close the socket
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
