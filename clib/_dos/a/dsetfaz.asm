;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	WATCOM_C __doserror		: PROC
		PUBLIC	_dos_setfileattr
;
; DECLARATION	unsigned _dos_setfileattr( char * path, unsigned attr );
;
PROC		_dos_setfileattr	WATCOM_C
		push	ecx				; Save context
		mov	ecx,edx				; ECX = file attributes
		mov	edx,eax				; EDX points to path
		;
		; Get function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_FILE_ATTRIBUTES SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jmp	__doserror			; Process return code
ENDP
		END
