;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosIoctlGenericCharIO
;
; DECLARATION	int DosIoctlGenericCharIO( int category, void *buffer,
;		                           int handle, int function );
;
PROC		DosIoctlGenericCharIO	WATCOM_C
		mov	ch,al				; CH = category
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_GENERIC_CHARACTER_IO	; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
