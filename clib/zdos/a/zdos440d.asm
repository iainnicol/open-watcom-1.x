;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosIoctlGenericBlockIO
;
; DECLARATION	int DosIoctlGenericBlockIO( int category, void *buffer,
;		                            int drive, int function );
;
PROC		DosIoctlGenericBlockIO	WATCOM_C
		mov	ch,al				; CH = category
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_GENERIC_BLOCK_IO	; AL = subfunction number
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
