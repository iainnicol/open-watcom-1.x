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
		PUBLIC	DosFrameBufferCopyRectangle_
;
;		#pragma aux DosFrameBufferCopyRectangle parm [EAX][ECX][EDX][ESI][EDI][EBX];
; DECLARATION	int DosFrameBufferCopyRectangle( int rop, int fromX, int fromY, int height, int width, int toX, toY );
;
PROC		DosFrameBufferCopyRectangle_	STDCALL
		ARG	toY : DWORD
		mov	ebp,[toY]			; EBP = destination Y coordinate
		xchg	ebx,ebp				; EBX = destination Y, EBP = destination X
		;
		; Copy rectangle
		;
		mov	ah,FRAMEBUF_COPY_RECTANGLE
IFDEF __ZDOSDRV__
		call	[DWORD DosFrameBuffer]
ELSE
		int	FRAME_BUFFER
ENDIF
		mov	ebp,esp				; Restore EBP
		call	BiosReturnZero			; Process return code
		ret
ENDP
		END
