;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetTID_
;
; DECLARATION	int DosGetTID( void );
;
PROC		DosGetTID_		STDCALL
		;
		; Return TID
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadID]
ELSE
		mov	ah,THREAD_ID
		int	THREAD
ENDIF
		ret
ENDP
		END
