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
		PUBLIC	DosFrameBufferDisableCursor
;
; DECLARATION	int DosFrameBufferDisableCursor( void );
;
PROC		DosFrameBufferDisableCursor	WATCOM_C
		;
		; Disable cursor
		;
		mov	eax,FRAMEBUF_CURSOR_OPERATION SHL 8 + FRAMEBUF_CURSOR_OFF
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
