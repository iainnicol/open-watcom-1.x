;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosTraceCloseSession
;
; DECLARATION	int DosTraceCloseSession( void );
;
PROC		DosTraceCloseSession	WATCOM_C
		mov	ah,TRACE_CLOSE_SESSION		; Close trace session
		int	TRACE
		jmp	DosReturnZero			; Process return code
ENDP
		END
