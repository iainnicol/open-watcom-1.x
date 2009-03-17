;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
;
; Assembly language variant of diskinfo_t structure
;
STRUC		DISK
Drive		DD	?				; Drive number
Head		DD	?				; Head number
Track		DD	?				; Track number
Sector		DD	?				; Sector number
Sectors		DD	?				; Number of sectors to transfer
Buffer		DD	?				; Pointer to buffer
ENDS
		CODESEG
;
; DECLARATION	unsigned _bios_disk( unsigned service,
;		                     struct diskinfo_t * diskinfo );
;
PROC		_bios_disk_		STDCALL
		USES	ebx,ecx,edx,esi
		mov	ah,al				; AH = BIOS function
		cmp	ah,2				; Reset or status function ?
		jb	SHORT @@DoFunction		; Yes, do function
		mov	esi,edx				; No, ESI points to structure
		mov	ebx,[(DISK esi).Buffer]		; EBX points to buffer
		mov	dl,[BYTE (DISK esi).Drive]	; DL = drive
		mov	dh,[BYTE (DISK esi).Head]	; DH = head
		mov	ecx,[(DISK esi).Track]		; ECX = track
		xchg	cl,ch				; Swap to BIOS order
		shl	cl,6				; Make room for sector number
		or	cl,[BYTE (DISK esi).Sector]	; Merge with sector number
		mov	al,[BYTE (DISK esi).Sectors]	; AL = number of sectors to transfer
		;
		; Call BIOS disk services
		;
IFDEF __ZDOSDRV__
@@DoFunction:	call	[DWORD BiosDisk]
ELSE
@@DoFunction:	int	BIOS_DISK
ENDIF
		ret
ENDP
		END
