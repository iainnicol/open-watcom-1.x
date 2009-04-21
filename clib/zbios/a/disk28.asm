;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosDeviceParameters
;
; DECLARATION	int BiosDeviceParameters( EDPT *buffer, int drive );
;
PROC		BiosDeviceParameters	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to buffer
		xor	eax,eax				; Clear EAX
IFDEF __ZDOSDRV__
		mov	al,SIZE EDPT			; EAX = length of parameter buffer
ELSE
		mov	[(EDPT ebx).Pointer],eax	; Reset pointer field
		mov	al,SIZE EDPT - 4		; EAX = length of parameter buffer
ENDIF
		mov	[(EDPT ebx).Length],ax		; Initialize length field
		mov	ah,DISK_DEVICE_PARAMETERS	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	ebx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
