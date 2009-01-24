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
		PUBLIC	_dos_setblock_
;
; DECLARATION	unsigned _dos_setblock( unsigned pages, void *block );
;
PROC		_dos_setblock_		STDCALL
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
		jmp	__doserror_			; Process return code
ENDP
		END
