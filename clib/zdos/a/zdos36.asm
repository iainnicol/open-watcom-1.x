;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetDriveFreeSpace
;
; DECLARATION	int DosGetDriveFreeSpace( DRVSPACE *drvspace, int drive );
;
PROC		DosGetDriveFreeSpace	WATCOM_C
		USES	esi,edx,ecx,ebx
		mov	esi,eax				; ESI points to DRVSPACE block
		mov	ah,DOS_GET_DRIVE_FREE_SPACE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[(DRVSPACE esi).SPC],eax	; Store sectors/cluster
		mov	[(DRVSPACE esi).Free],ebx	; Store number of free clusters
		mov	[(DRVSPACE esi).BPS],ecx	; Store bytes/sector
		mov	[(DRVSPACE esi).Total],edx	; Store total number of clusters
		cmp	eax,-1				; Success ?
		jz	SHORT @@Exit			; No, we are done
		xor	eax,eax				; Yes, clear EAX
@@Exit:		ret
ENDP
		END
