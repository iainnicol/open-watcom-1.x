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
		PUBLIC	DosCommitFile_
;
; DECLARATION	int DosCommitFile( int handle );
;
PROC		DosCommitFile_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = file handle
		mov	ah,DOS_COMMIT_FILE		; AH = DOS fucntion
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
