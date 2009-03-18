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
		PUBLIC	DosGetPriority_
;
; DECLARATION	int DosGetPriority( int TID );
;
PROC		DosGetPriority_		STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX = TID
		;
		; Get priority
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadGetPrio]
ELSE
		mov	ah,THREAD_GET_PRIORITY
		int	THREAD
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return priority
ENDP
		END
