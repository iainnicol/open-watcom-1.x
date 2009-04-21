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
		PUBLIC	_dos_allocmem
;
; DECLARATION	unsigned _dos_allocmem( unsigned pages, void **block );
;
PROC		_dos_allocmem		WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = size of block
		mov	ah,DOS_ALLOCATE_MEMORY_BLOCK	; AH = DOS function
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
		mov	[edx],eax			; Yes, save pointer to block
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
