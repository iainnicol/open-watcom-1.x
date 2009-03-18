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
		PUBLIC	DosFrameBufferCursorPosition_
;
;		#pragma aux DosFrameBufferCursorPosition parm [ECX][EDX];
; DECLARATION	int DosFrameBufferCursorPosition( int X, int Y );
;
PROC		DosFrameBufferCursorPosition_	STDCALL
		;
		; Set cursor position
		;
		mov	eax,FRAMEBUF_CURSOR_OPERATION SHL 8 + FRAMEBUF_CURSOR_POSITION
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
