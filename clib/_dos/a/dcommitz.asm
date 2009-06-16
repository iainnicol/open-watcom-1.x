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
		PUBLIC	_dos_commit
;
; DECLARATION	unsigned _dos_commit( int handle );
;
PROC		_dos_commit		WATCOM_C
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
		jmp	__doserror			; Process return code
ENDP
		END
