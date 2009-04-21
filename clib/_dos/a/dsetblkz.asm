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
		PUBLIC	_dos_setblock
;
; DECLARATION	unsigned _dos_setblock( unsigned pages, void *block );
;
PROC		_dos_setblock		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = size of block
		mov	ebx,edx				; EBX points to block
		mov	ah,DOS_RESIZE_MEMORY_BLOCK	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	__doserror			; Process return code
ENDP
		END
