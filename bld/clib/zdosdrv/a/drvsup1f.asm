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
		PUBLIC	DosLockCpu_
;
; DECLARATION	int DosLockCpu( MUTEX *mutex );
;
PROC		DosLockCpu_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
		call	[DWORD LockCpu]			; Lock CPU
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
