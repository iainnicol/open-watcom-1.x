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
		PUBLIC	BiosSeekDisk
;
; DECLARATION	int BiosSeekDisk( int head, int drive, int track );
;
PROC		BiosSeekDisk		WATCOM_C
		push	ecx				; Save context
		mov	ecx,ebx				; ECX = track
		shl	ch,6				; Convert track number to BIOS format
		xchg	cl,ch				; ECX = track number in BIOS format
		mov	dh,al				; DH = head number
		mov	ah,DISK_SEEK			; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		pop	ecx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
