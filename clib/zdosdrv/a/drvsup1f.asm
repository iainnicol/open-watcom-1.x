;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosLockCpu
;
; DECLARATION	int DosLockCpu( MUTEX *mutex );
;
PROC		DosLockCpu		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
		call	[DWORD LockCpu]			; Lock CPU
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
