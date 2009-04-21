;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	putch
;
; DECLARATION	int putch( int c );
;
PROC		putch			WATCOM_C
		USES	edx
		mov	ah,DOS_DIRECT_CONSOLEIO		; AH = DOS function
		mov	dl,al				; DL = character to write

		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,dl				; EAX = character written
		ret
ENDP
		END
