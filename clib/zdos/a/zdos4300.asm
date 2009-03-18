;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetFileAttributes_
;
; DECLARATION	int DosGetFileAttributes( char *path );
;
PROC		DosGetFileAttributes_	STDCALL
		USES	edx,ecx
		mov	edx,eax				; EDX points to path
		;
		; Get function numbers in EAX
		;
		mov	eax,DOS_GET_SET_FILE_ATTRIBUTES SHL 8
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		mov	eax,ecx				; Yes, return file attributes
		ret
@@Error:	neg	eax				; Return negated DOS error code
		ret
ENDP
		END
