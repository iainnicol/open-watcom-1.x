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
		PUBLIC	DosCloseFile
;
; DECLARATION	int DosCloseFile( int handle );
;
PROC		DosCloseFile		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = file handle
		mov	ah,DOS_CLOSE_FILE		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
