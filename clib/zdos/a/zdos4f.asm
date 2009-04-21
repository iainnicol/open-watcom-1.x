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
		PUBLIC	DosFindNextFile
;
; DECLARATION	int DosFindNextFile( FIND *find );
;
PROC		DosFindNextFile		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to FIND block
		mov	ah,DOS_FIND_NEXT_FILE		; AH = DOS function number
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
