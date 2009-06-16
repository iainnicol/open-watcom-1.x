;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosOpenFile
;
; DECLARATION	int DosOpenFile( int mode, char *path );
;
PROC		DosOpenFile		WATCOM_C
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
