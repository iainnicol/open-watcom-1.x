;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
;
; Assembly variant of diskfree_t
;
STRUC		DISK
TC		DD	?				; Total number of clusters
AC		DD	?				; Available number of clusters
SPC		DD	?				; Sectors per cluster
BPS		DD	?				; Bytes per sector
ENDS
		CODESEG
		EXTRN	C __set_EINVAL			: PROC
		PUBLIC	_dos_getdiskfree_
;
; DECLARATION	unsigned _dos_getdiskfree( unsigned drive,
;		                           struct diskfree_t *diskspace );
;
PROC		_dos_getdiskfree_	STDCALL
		USES	esi,ecx,ebx
		mov	esi,edx				; ESI points to buffer
		mov	dl,al				; DL = drive
		mov	ah,DOS_GET_DRIVE_FREE_SPACE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		or	eax,eax				; Valid drive ?
		js	SHORT @@Error			; No, error
		mov	[(DISK esi).SPC],eax		; Yes, save sectors/cluster
		mov	[(DISK esi).AC],ebx		; Save available clusters
		mov	[(DISK esi).BPS],ecx		; Save bytes/sector
		mov	[(DISK esi).TC],edx		; Save total clusters
		xor	eax,eax				; Clear EAX
@@Exit:		ret
@@Error:	call	__set_EINVAL			; Set errno to EINVAL
		jmp	@@Exit
ENDP
		END
