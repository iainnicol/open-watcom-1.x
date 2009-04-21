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
		PUBLIC	_dos_freemem
;
; DECLARATION	unsigned _dos_freemem( void *block );
;
PROC		_dos_freemem		WATCOM_C
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
		jmp	__doserror			; Process return code
ENDP
		END
