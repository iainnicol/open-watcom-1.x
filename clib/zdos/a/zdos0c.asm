;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFlushBeforeInput
;
; DECLARATION	int DosFlushBeforeInput( int function, char *buffer );
;
PROC		DosFlushBeforeInput	WATCOM_C
		push	ebx				; Save context
		mov	ebx,OFFSET DosReturnZero	; Assume buffered input
		cmp	al,DOS_CONSOLE_BUFFERED_INPUT	; Buffered input ?
		jz	SHORT @@DoFunction		; Yes, do function
		mov	ebx,OFFSET DosReturnAL		; No, it's non buffered input
@@DoFunction:	xchg	ebx,[esp]			; Restore EBX and put return code processer on stack
		mov	ah,DOS_FLUSH_BEFORE_INPUT	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret					; Process return code
ENDP
		END
