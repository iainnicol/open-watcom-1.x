;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosIoctlDeviceRemote
;
; DECLARATION	int DosIoctlDeviceRemote( int drive );
;
PROC		DosIoctlDeviceRemote	WATCOM_C
		USES	edx,ebx
		mov	ebx,eax				; EBX = logical drive number
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_BLOCK_DEVICE_REMOTE	; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		mov	eax,edx				; Yes, get return value in EAX
		shr	eax,12				; Return 0 or 1
		ret
@@Error:	neg	eax				; Return negated DOS error code
		ret
ENDP
		END
