;
; Copyright (C) 2007 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'FRAMEBUF.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFrameBufferInformation_
;
;		#pragma aux DosFrameBufferInformation parm [EDI];
; DECLARATION	int DosFrameBufferInformation( FRAMEBUF_INFO *info );
;
PROC		DosFrameBufferInformation_	STDCALL
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
