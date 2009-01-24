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
		PUBLIC	DosIoctlWriteBlockDevice_
;
; DECLARATION	int DosIoctlWriteBlockDevice( int bytes, void *buffer,
;		                              int drive );
;
PROC		DosIoctlWriteBlockDevice_ STDCALL
		push	ecx				; Save context
		mov	ecx,eax				; ECX = number of bytes to read
		mov	eax,DOS_DEVICE_CONTROL SHL 8 + \; AH = DOS function number
			    IOCTL_WRITE_BLOCK_DEVICE	; AL = subfunction number
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
		ret					; Yes, return number of bytes written
ENDP
		END
