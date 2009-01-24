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
		PUBLIC	_dos_creatnew_
;
; DECLARATION	unsigned _dos_creatnew( char * path, unsigned attribute,
;		                        int *handle );
;
PROC		_dos_creatnew_		STDCALL
		push	ecx				; Save context
		mov	ecx,edx				; ECX = attribute
		mov	edx,eax				; EDX points to path
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
		jc	__doserror_			; Success ?
		mov	[ebx],eax			; Yes, save handle
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
