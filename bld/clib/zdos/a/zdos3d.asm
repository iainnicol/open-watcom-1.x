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
		PUBLIC	DosOpenFile_
;
; DECLARATION	int DosOpenFile( int mode, char *path );
;
PROC		DosOpenFile_		STDCALL
		mov	ah,DOS_OPEN_FILE		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return file handle
ENDP
		END
