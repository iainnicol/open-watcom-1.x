;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		PUBLIC	DosIoctlGetDriveMapping
;
; DECLARATION	int DosIoctlGetDriveMapping( int drive );
;
PROC		DosIoctlGetDriveMapping WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX = logical drive
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number, AL = subfunction number
			    IOCTL_GET_LOGICAL_DRIVE_MAPPING
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
