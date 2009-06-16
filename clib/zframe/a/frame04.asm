;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'FRAMEBUF.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	DosFrameBufferFillRectangle
;
;		#pragma aux DosFrameBufferFillRectangle parm [EAX][EBX][ECX][EDX][ESI][EDI];
; DECLARATION	int DosFrameBufferFillRectangle( int rop, int color, int x, int y, int height, int width );
;
PROC		DosFrameBufferFillRectangle WATCOM_C
		;
		; Fill rectangle
		;
		mov	ah,FRAMEBUF_FILL_RECTANGLE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
