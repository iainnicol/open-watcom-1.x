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
		PUBLIC	DosTraceCloseSession_
;
; DECLARATION	int DosTraceCloseSession( void );
;
PROC		DosTraceCloseSession_	STDCALL
		mov	ah,TRACE_CLOSE_SESSION		; Close trace session
		int	TRACE
		jmp	DosReturnZero			; Process return code
ENDP
		END
