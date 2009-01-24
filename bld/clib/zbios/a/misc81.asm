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
		PUBLIC	BiosDeviceClose_
;
; DECLARATION	int BiosDeviceClose( int device, int process );
;
PROC		BiosDeviceClose_	STDCALL
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX = device ID
		mov	ecx,edx				; ECX = process ID
		mov	ah,MISC_DEVICE_CLOSE		; AH = function number
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
