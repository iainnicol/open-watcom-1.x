;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	WATCOM_C __doserror		: PROC
		PUBLIC	_dos_creat
;
; DECLARATION	unsigned _dos_creat( char * path, unsigned attribute,
;		                     int *handle );
;
PROC		_dos_creat		WATCOM_C
		push	ecx				; Save context
		mov	ecx,edx				; ECX = attribute
		mov	edx,eax				; EDX points to path
		mov	ah,DOS_CREATE_FILE		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jc	__doserror			; Success ?
		mov	[ebx],eax			; Yes, save handle
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
