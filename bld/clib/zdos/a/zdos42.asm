;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSetFilePosition_
;
; DECLARATION	int DosSetFilePosition( int method, unsigned long offset,
;		                        int handle, unsigned long *position );
;
PROC		DosSetFilePosition_	STDCALL
		mov	ah,DOS_SET_FILE_POSITION	; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[ecx],eax			; Set resulting position
		jmp	DosReturnZero			; Process return code
ENDP
		END
