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
		PUBLIC	BiosReadSector_
;
; DECLARATION	int BiosReadSector( int sectors, int drive, void *buffer,
;		                    int track, int sector, int head );
;
PROC		BiosReadSector_		STDCALL
		ARG	Sector : DWORD, Head : DWORD
		shl	ch,6				; Convert track and sector number to BIOS format
		xchg	cl,ch
		or	cl,[BYTE Sector]		; ECX = track and sector number in BIOS format
		mov	dh,[BYTE Head]			; DH = head number
		mov	ah,DISK_READ_SECTOR		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		call	BiosReturnAL			; Process return code
		ret
ENDP
		END
