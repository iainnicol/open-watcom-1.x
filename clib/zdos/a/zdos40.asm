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
		PUBLIC	DosWriteFile
;
; DECLARATION	int DosWriteFile( int bytes, void *buffer, int handle );
;
PROC		DosWriteFile		WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to write
		mov	ah,DOS_WRITE_FILE		; AH = DOS function number
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
		ret					; Yes, return number of bytes written
ENDP
		END
