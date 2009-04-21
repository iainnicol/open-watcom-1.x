;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosAbsoluteDiskRead
;
; DECLARATION	int DosAbsoluteDiskRead( int drive, unsigned sector,
;		                         void *buffer, int count );
;
PROC		DosAbsoluteDiskRead	WATCOM_C
		;
		; Read sectors from disk
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosDiskRead]
ELSE
		int	ABS_DISK_READ
ENDIF
		jc	SHORT @@Exit			; Error ?
		xor	eax,eax				; No, clear EAX
@@Exit:		ret
ENDP
		END
