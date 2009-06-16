;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosResetAtapiDevice
;
; DECLARATION	int BiosResetAtapiDevice( int device );
;
PROC		BiosResetAtapiDevice	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = device
		mov	ah,DISK_DEVICE_RESET		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	edx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
