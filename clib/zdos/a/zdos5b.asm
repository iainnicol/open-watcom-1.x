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
		PUBLIC	DosCreateNewFile
;
; DECLARATION	int DosCreateNewFile( int attributes, char *path );
;
PROC		DosCreateNewFile	WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = file attributes
		mov	ah,DOS_CREATE_NEW_FILE		; AH = DOS function
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
