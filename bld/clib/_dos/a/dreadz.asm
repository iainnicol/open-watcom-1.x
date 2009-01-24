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
		PUBLIC	_dos_read_
;
; DECLARATION	unsigned _dos_read( int handle, void *buffer,
;		                    unsigned count, unsigned *bytes );
;
PROC		_dos_read_		STDCALL
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
		jmp	__doserror_			; Process return code
ENDP
		END
