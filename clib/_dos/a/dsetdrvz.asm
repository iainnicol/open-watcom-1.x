;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	_dos_setdrive
;
; DECLARATION	void _dos_setdrive( unsigned drive, unsigned *drives );
;
PROC		_dos_setdrive		WATCOM_C
		USES	ebx
		mov	ebx,edx				; EBX points to drives variable
		mov	dl,al				; DL = drive number
		mov	ah,DOS_SET_CURRENT_DRIVE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,al				; Convert to 32-bit value
		mov	[ebx],eax			; Store in callers variable
		ret
ENDP
		END
