;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		EXTRN	BuildFileSystemName_		: PROC
		PUBLIC	DosRegisterFileSystem
;
; DECLARATION	int DosRegisterFileSystem( FSD *header, char *name );
;
PROC		DosRegisterFileSystem	WATCOM_C
		push	ebx				; Save context
		push	eax				; Create 8 character wide buffer
		push	eax
		mov	ebx,eax				; EBX points to driver header
		mov	eax,esp				; EAX points to buffer
		call	BuildFileSystemName_		; Build file system name
		jc	SHORT @@Exit			; Success ?
		mov	edx,eax				; Yes, EDX points to converted file system name
		xor	ah,ah				; Register file system
		call	[DWORD DosFileSystem]
@@Exit:		pop	ebx				; Remove buffer
		pop	ebx
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return file system ID
ENDP
		END
