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
		PUBLIC	DosFrameBufferWaitEngine2D
;
; DECLARATION	int DosFrameBufferWaitEngine2D( void );
;
PROC		DosFrameBufferWaitEngine2D	WATCOM_C
		;
		; Set palette register
		;
		mov	ah,FRAMEBUF_WAIT_ENGINE_2D
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
