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
		PUBLIC	_dos_write
;
; DECLARATION	unsigned _dos_write( int handle, void * buffer,
;		                     unsigned count, unsigned *bytes );
;
PROC		_dos_write		WATCOM_C
		push	esi				; Save context
		mov	esi,ecx				; ESI points to number of bytes variable
		mov	ecx,ebx				; ECX = number of bytes to write
		mov	ebx,eax				; EBX = handle
		mov	ah,DOS_WRITE_FILE		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Exit			; Success ?
		mov	[esi],eax			; Yes, save number of bytes written
@@Exit:		pop	esi				; Restore context
		jmp	__doserror			; Process return code
ENDP
		END
