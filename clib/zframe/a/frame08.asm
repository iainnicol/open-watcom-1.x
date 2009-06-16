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
		PUBLIC	DosFrameBufferSetPalette
;
; DECLARATION	int DosFrameBufferSetPalette( int index, int blue, int red, int green );
;
PROC		DosFrameBufferSetPalette	WATCOM_C
		;
		; Set palette register
		;
		mov	ah,FRAMEBUF_SET_PALETTE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
