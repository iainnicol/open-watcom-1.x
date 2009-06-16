;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosIoctlHandleRemote
;
; DECLARATION	int DosIoctlHandleRemote( int handle );
;
PROC		DosIoctlHandleRemote	WATCOM_C
		USES	edx,ebx
		mov	ebx,eax				; EBX = file handle
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_HANDLE_REMOTE		; AL = subfunction number
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
		shr	eax,15				; Return 0 or 1
		ret
@@Error:	neg	eax				; Return negated DOS error code
		ret
ENDP
		END
