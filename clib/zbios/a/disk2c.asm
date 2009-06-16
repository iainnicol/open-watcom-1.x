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
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosUnlockMedia
;
; DECLARATION	int BiosUnlockMedia( int device );
;
PROC		BiosUnlockMedia		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = device
		mov	ah,DISK_UNLOCK_MEDIA		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	edx				; Restore context
		jmp	BiosReturnAL			; Process return code
ENDP
		END
