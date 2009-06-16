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
		PUBLIC	_dos_read
;
; DECLARATION	unsigned _dos_read( int handle, void *buffer,
;		                    unsigned count, unsigned *bytes );
;
PROC		_dos_read		WATCOM_C
		push	esi				; Save context
		mov	esi,ecx				; ESI points to number of bytes variable
		mov	ecx,ebx				; ECX = number of bytes to read
		mov	ebx,eax				; EBX = handle
		mov	ah,DOS_READ_FILE		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Exit			; Success ?
		mov	[esi],eax			; Yes, save number of bytes read
@@Exit:		pop	esi				; Restore context
		jmp	__doserror			; Process return code
ENDP
		END
