;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnAL			: PROC
		PUBLIC	BiosDiskExtensions_
;
; DECLARATION	int BiosDiskExtensions( int drive, unsigned *support );
;
PROC		BiosDiskExtensions_	STDCALL
		push	ecx				; Save context
		push	ebx
		mov	ebx,55aah			; EBX = signature
		mov	ah,DISK_EXTENSION_PRESENT	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		mov	[edx],ecx			; Store device support flags
		mov	al,ah				; AL = version number
		pop	ebx				; Restore context
		pop	ecx
		jmp	BiosReturnAL			; Process return code
ENDP
		END
