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
		PUBLIC	DosWaitMutex
;
; DECLARATION	int DosWaitMutex( MUTEX *mutex );
;
PROC		DosWaitMutex		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
		;
		; Wait mutex
		;
IFDEF __ZDOSDRV__
		call	[DWORD MutexLock]
ELSE
		mov	ah,IPC_WAIT_MUTEX
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
