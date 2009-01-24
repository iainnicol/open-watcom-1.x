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
		PUBLIC	DosCloseMutex_
;
; DECLARATION	int DosCloseMutex( MUTEX *mutex );
;
PROC		DosCloseMutex_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
		;
		; Close mutex
		;
IFDEF __ZDOSDRV__
		call	[DWORD MutexClose]
ELSE
		mov	ah,IPC_CLOSE_MUTEX
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of tasks waiting
ENDP
		END
