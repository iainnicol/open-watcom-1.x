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
		PUBLIC	BiosGetDiskType
;
; DECLARATION	int BiosGetDiskType( int drive, unsigned long long *sectors );
;
PROC		BiosGetDiskType		WATCOM_C
		push	edx				; Save context
		push	ecx
		push	ebx
		mov	ebx,edx				; EBX points to sectors variable
		xor	ecx,ecx				; Clear ECX
		mov	dl,al				; DL = drive
		mov	ah,DISK_GET_DRIVE_TYPE		; AH = disk function
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosDisk]
ELSE
		int	BIOS_DISK
ENDIF
		jc	SHORT @@Exit			; Success ?
		mov	al,ah				; Yes, AL = drive type
		cmp	al,3				; Fixed disk type ?
		jz	SHORT @@Done			; Yes, store disk size
		xor	edx,edx				; No, clear EDX
@@Done:		mov	[ebx],edx			; Store number of sectors
		mov	[ebx + 4],ecx
@@Exit:		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		jmp	BiosReturnAL			; Process return code
ENDP
		END
