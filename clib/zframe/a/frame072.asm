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
		PUBLIC	DosFrameBufferCursorShape
;
;		#pragma aux DosFrameBufferCursorShape parm [EBX][EAX][ECX][EDX][ESI][EDI];
; DECLARATION	int DosFrameBufferCursorShape( int hotspotX, int hotspotY, int color0, int color1, void *bitmap, int size );
;
PROC		DosFrameBufferCursorShape	WATCOM_C
		mov	bh,al				; BH = hot spot Y
		;
		; Set cursor shape and hot spots
		;
		mov	eax,FRAMEBUF_CURSOR_OPERATION SHL 8 + FRAMEBUF_CURSOR_SHAPE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
