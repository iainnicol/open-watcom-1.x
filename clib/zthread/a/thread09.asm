;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosSetPriority
;
; DECLARATION	int DosSetPriority( int priority, int TID );
;
PROC		DosSetPriority		WATCOM_C
		;
		; Set priority
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadSetPrio]
ELSE
		mov	ah,THREAD_SET_PRIORITY
		int	THREAD
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return previous priority
ENDP
		END
