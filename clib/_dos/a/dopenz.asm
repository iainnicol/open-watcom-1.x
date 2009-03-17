;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	ConvertOpenFlags		: PROC
		EXTRN	__doserror_			: PROC
		PUBLIC	_dos_open_
;
; DECLARATION	unsigned _dos_open( char * path, unsigned mode,
;		                    int *handle );
;
PROC		_dos_open_		STDCALL
		xchg	eax,edx				; EAX = mode, EDX points to path
		call	ConvertOpenFlags		; Convert open flags to ZDOS convention
		mov	ah,DOS_OPEN_FILE		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	__doserror_			; Success ?
		mov	[ebx],eax			; Yes, save handle
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
