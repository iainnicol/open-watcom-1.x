;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosDeviceOpen
;
; DECLARATION	int BiosDeviceOpen( int device, int process );
;
PROC		BiosDeviceOpen		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = device ID
		mov	ecx,edx				; ECX = process ID
		mov	ah,MISC_DEVICE_OPEN		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnZero			; Process return code
ENDP
		END
