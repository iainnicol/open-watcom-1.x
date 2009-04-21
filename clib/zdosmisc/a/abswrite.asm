;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosAbsoluteDiskWrite
;
; DECLARATION	int DosAbsoluteDiskWrite( int drive, unsigned sector,
;		                          void *buffer, int count );
;
PROC		DosAbsoluteDiskWrite 	WATCOM_C
		;
		; Write sector(s) to disk
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosDiskWrite]
ELSE
		int	ABS_DISK_WRITE
ENDIF
		jc	SHORT @@Exit			; Error ?
		xor	eax,eax				; No, clear EAX
@@Exit:		ret
ENDP
		END
