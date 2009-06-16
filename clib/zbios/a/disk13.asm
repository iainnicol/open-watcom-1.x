;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosDiskEmulatorConnect
;
; DECLARATION	int BiosDiskEmulatorConnect( void **dispatch, int drive );
;
PROC		BiosDiskEmulatorConnect WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to dispatcher table
		mov	ah,DISK_EMULATOR_CONNECT	; AH = disk function
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
