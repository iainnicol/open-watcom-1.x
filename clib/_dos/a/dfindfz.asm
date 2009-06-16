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
		PUBLIC	_dos_findfirst
;
; DECLARATION	unsigned int _dos_findfirst( char * path,
;		                             unsigned attributes,
;		                             struct find_t *buffer );
;
PROC		_dos_findfirst		WATCOM_C
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
		jmp	__doserror			; Process return code
ENDP
		END
