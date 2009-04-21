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
		PUBLIC	DosFrameBufferDrawImage
;
;		#pragma aux DosFrameBufferDrawImage parm [EAX][ECX][EDX][ESI][EDI][EBX];
; DECLARATION	int DosFrameBufferDrawImage( int rop, int X, int Y, int height, int width, FRAMEBUF_IMAGE *image );
;
PROC		DosFrameBufferDrawImage	WATCOM_C
		;
		; Draw image
		;
		mov	ah,FRAMEBUF_DRAW_IMAGE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
