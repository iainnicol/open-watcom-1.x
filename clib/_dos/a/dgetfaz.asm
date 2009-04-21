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
		PUBLIC	_dos_getfileattr
;
; DECLARATION	unsigned _dos_getfileattr( char * path, unsigned *attr );
;
PROC		_dos_getfileattr	WATCOM_C
		push	ebx				; Save context
		mov	ebx,edx				; EBX points to attribute variable
		mov	edx,eax				; EDX points to path
		;
		; Get DOS function numbers in AH and AL
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
		jc	SHORT @@Exit			; Success ?
		mov	[ebx],ecx			; Yes, store file attributes
@@Exit:		pop	ebx				; No, restore context
		jmp	__doserror			; Process return code
ENDP
		END
