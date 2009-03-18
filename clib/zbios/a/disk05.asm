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
		PUBLIC	BiosFormatTrack_
;
; DECLARATION	int BiosFormatTrack( int interleave, int drive, void *buffer,
;		                     int track, int head );
;
PROC		BiosFormatTrack_	STDCALL
		ARG	Head : DWORD
		shl	ch,6				; Convert track number to BIOS format
		xchg	cl,ch				; ECX = track number in BIOS format
		mov	dh,[BYTE Head]			; DH = head number
		mov	ah,DISK_FORMAT_TRACK		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		call	BiosReturnZero			; Process return code
		ret
ENDP
		END
