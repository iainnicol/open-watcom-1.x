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
		PUBLIC	DosFrameBufferDisableConsole
;
; DECLARATION	int DosFrameBufferDisableConsole( void );
;
PROC		DosFrameBufferDisableConsole	WATCOM_C
		;
		; Disable console emulator
		;
		mov	ah,FRAMEBUF_DISABLE_CONSOLE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
