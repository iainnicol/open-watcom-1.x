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
		PUBLIC	BiosDiskParameters_
;
; DECLARATION	int BiosDiskParameters( DISK *disk, int drive );
;
PROC		BiosDiskParameters_	STDCALL
		push	edi				; Save context
		push	esi
		push	ecx
		push	ebx
		mov	esi,eax				; ESI points to DISK block
		xor	edi,edi				; Clear EDI
		xor	al,al				; Clear AL
		mov	ah,DISK_DRIVE_PARAMETERS	; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		mov	[(DISK esi).DPT],edi		; Store pointer to DPT
		mov	[(DISK esi).MaxHead],dh		; Store maximum head number
		mov	[(DISK esi).MaxSector],cl	; Store maximum sector number
		shr	cl,6				; CL = bit 8 - 9 of maximum track number
		and	[(DISK esi).MaxSector],3fh	; Clear track bits
		xchg	cl,ch				; ECX = maximum track number
		mov	[(DISK esi).MaxTrack],cx	; Store maximum track number
		xchg	al,dl				; AL = number of drives, DL = 0
		pop	ebx				; Restore context
		pop	ecx
		pop	esi
		pop	edi
		cmp	dl,ah				; Set or clear carry flag
		jmp	BiosReturnAL			; Process return code
ENDP
		END
