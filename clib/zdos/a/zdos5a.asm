;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosCreateTemporaryFile_
;
; DECLARATION	int DosCreateTemporaryFile( int attributes, char *path );
;
PROC		DosCreateTemporaryFile_	STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = file attributes
		mov	ah,DOS_CREATE_TEMPORARY_FILE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return file handle
ENDP
		END
