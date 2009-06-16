;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'FRAMEBUF.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFrameBufferInformation
;
;		#pragma aux DosFrameBufferInformation parm [EDI];
; DECLARATION	int DosFrameBufferInformation( FRAMEBUF_INFO *info );
;
PROC		DosFrameBufferInformation	WATCOM_C
		;
		; Get frame buffer information
		;
		mov	ah,FRAMEBUF_INFORMATION
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
