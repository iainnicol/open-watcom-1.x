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
		PUBLIC	DosIoctlSetDriveMapping_
;
; DECLARATION	int DosIoctlSetDriveMapping( int drive );
;
PROC		DosIoctlSetDriveMapping_ STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX = logical drive
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number, AL = subfunction number
			    IOCTL_SET_LOGICAL_DRIVE_MAPPING
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
