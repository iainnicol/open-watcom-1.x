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
		PUBLIC	DosDuplicateHandle
;
; DECLARATION	int DosDuplicateHandle( int handle );
;
PROC		DosDuplicateHandle	WATCOM_C
		push	ebx				; Save context
		mov	ah,DOS_DUPLICATE_HANDLE		; AH = DOS function number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return new handle
ENDP
		END
