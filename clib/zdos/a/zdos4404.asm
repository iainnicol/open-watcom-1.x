;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosIoctlReadBlockDevice
;
; DECLARATION	int DosIoctlReadBlockDevice( int bytes, void *buffer,
;		                             int drive );
;
PROC		DosIoctlReadBlockDevice WATCOM_C
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to read
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_READ_BLOCK_DEVICE	; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ecx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of bytes read
ENDP
		END
