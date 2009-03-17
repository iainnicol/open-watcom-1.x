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
		PUBLIC	_dos_commit_
;
; DECLARATION	unsigned _dos_commit( int handle );
;
PROC		_dos_commit_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = handle
		mov	ah,DOS_COMMIT_FILE		; AH = DOS function
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
