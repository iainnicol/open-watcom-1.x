;
; Copyright (C) 2007 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'FRAMEBUF.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	DosFrameBufferSetConsoleWindow
;
; DECLARATION	int DosFrameBufferSetConsoleWindow( int LowerY, LowerX, UpperY, UpperX );
;
PROC		DosFrameBufferSetConsoleWindow WATCOM_C
		mov	ch,bl				; CH = upper Y coordinate
		mov	dh,al				; DH = lower Y coordinate
		;
		; Set console window
		;
		mov	ah,FRAMEBUF_SET_CONSOLE_WINDOW
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
