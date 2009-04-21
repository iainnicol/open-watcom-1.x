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
		PUBLIC	DosFrameBufferEnableConsole
;
; DECLARATION	int DosFrameBufferEnableConsole( void );
;
PROC		DosFrameBufferEnableConsole	WATCOM_C
		;
		; Enable console emulator
		;
		mov	ah,FRAMEBUF_ENABLE_CONSOLE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
