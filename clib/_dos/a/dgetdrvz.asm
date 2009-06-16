;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_dos_getdrive
;
; DECLARATION	void _dos_getdrive( unsigned *drive );
;
PROC		_dos_getdrive		WATCOM_C
		USES	edx
		mov	edx,eax				; EDX points to drive variable
		mov	ah,DOS_GET_CURRENT_DRIVE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		inc	al				; Increment drive number
		movzx	eax,al				; Convert to 32-bit value
		mov	[edx],eax			; Store in callers variable
		ret
ENDP
		END
