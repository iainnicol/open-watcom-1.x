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
		EXTRN	WATCOM_C __doserror		: PROC
		PUBLIC	_dos_open
;
; DECLARATION	unsigned _dos_open( char * path, unsigned mode,
;		                    int *handle );
;
PROC		_dos_open		WATCOM_C
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
		jc	__doserror			; Success ?
		mov	[ebx],eax			; Yes, save handle
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
