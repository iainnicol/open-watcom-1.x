;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	__doserror_			: PROC
		PUBLIC	_dos_findfirst_
;
; DECLARATION	unsigned int _dos_findfirst( char * path,
;		                             unsigned attributes,
;		                             struct find_t *buffer );
;
PROC		_dos_findfirst_		STDCALL
		mov	ecx,edx				; ECX = attributes
		mov	edx,eax				; EDX points to path
		mov	ah,DOS_FIND_FIRST_FILE		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	__doserror_			; Process return code
ENDP
		END
