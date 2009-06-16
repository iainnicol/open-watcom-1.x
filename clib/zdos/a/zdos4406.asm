;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		PUBLIC	DosIoctlDeviceInputStatus
;
; DECLARATION	int DosIoctlDeviceInputStatus( int handle );
;
PROC		DosIoctlDeviceInputStatus WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = file handle
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_DEVICE_INPUT_STATUS	; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnAL			; Process return code
ENDP
		END
