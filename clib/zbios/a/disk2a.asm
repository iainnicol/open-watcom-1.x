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
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosMediaLockStatus_
;
; DECLARATION	int BiosMediaLockStatus( int device );
;
PROC		BiosMediaLockStatus_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX = device
		mov	ah,DISK_MEDIA_LOCK_STATUS	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]		; Fill in device parameters
ELSE
		int	BIOS_DISK
ENDIF
		pop	edx				; Restore context
		jmp	BiosReturnAL			; Process return code
ENDP
		END
