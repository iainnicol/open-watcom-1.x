;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosDeviceType
;
; DECLARATION	int BiosDeviceType( int *numdevices, int drive );
;
PROC		BiosDeviceType		WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX points to variable
		xor	ebx,ebx				; Clear EBX
		mov	ah,DISK_DEVICE_TYPE		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		mov	[ecx],ebx			; Store number of devices
		mov	al,ah				; AL = device type
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnAL			; Process return code
ENDP
		END
