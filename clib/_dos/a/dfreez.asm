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
		PUBLIC	_dos_freemem_
;
; DECLARATION	unsigned _dos_freemem( void *block );
;
PROC		_dos_freemem_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to block
		mov	ah,DOS_FREE_MEMORY_BLOCK	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		jmp	__doserror_			; Process return code
ENDP
		END
