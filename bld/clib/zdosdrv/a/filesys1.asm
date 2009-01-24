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
		PUBLIC	DosQueryFileSystemID_
;
; DECLARATION	int DosQueryFileSystemID( char *name );
;
PROC		DosQueryFileSystemID_	STDCALL
		push	ebx				; Save context
		push	eax				; Create 8 character wide buffer
		push	eax
		mov	edx,eax				; EDX points to name
		mov	eax,esp				; EAX points to buffer
		call	BuildFileSystemName_		; Build file system name
		jc	SHORT @@Exit			; Success ?
		mov	edx,eax				; Yes, EDX points to converted file system name
		mov	ah,1				; Quearyister file system
		call	[DWORD DosFileSystem]
@@Exit:		pop	ebx				; Remove buffer
		pop	ebx
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return file system ID
ENDP
		END
