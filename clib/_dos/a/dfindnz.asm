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
		PUBLIC	_dos_findnext
;
; DECLARATION	unsigned int _dos_findnext( struct find_t *buffer );
;
PROC		_dos_findnext		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to find_t strructure
		mov	ah,DOS_FIND_NEXT_FILE		; AH = DOS function
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
