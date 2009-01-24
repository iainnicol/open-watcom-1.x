;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosIoctlGetDeviceInfo_
;
; DECLARATION	int DosIoctlGetDeviceInfo( int handle );
;
PROC		DosIoctlGetDeviceInfo_	STDCALL
		USES	edx,ebx
		mov	ebx,eax				; EBX = file handle
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_GET_DEVICE_INFO	; AL = subfunction number
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jc	SHORT @@Error			; Success ?
		mov	eax,edx				; Yes, return device information bits
		ret
@@Error:	neg	eax				; Return negated DOS error code
		ret
ENDP
		END
