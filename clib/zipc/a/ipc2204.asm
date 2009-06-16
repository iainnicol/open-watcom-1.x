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
		PUBLIC	DosWaitMutexTimeOut
;
; DECLARATION	int DosWaitMutexTimeOut( MUTEX *mutex, unsigned timeout );
;
PROC		DosWaitMutexTimeOut	WATCOM_C
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutext
		mov	eax,edx				; EAX = timeout value
		call	[DWORD MutexLockTO]		; Wait mutex
		pop	ebx				; Restore context
ELSE
		push	ecx				; Save context
		push	ebx
		mov	ebx,eax				; EBX points to mutex
		mov	ecx,edx				; ECX = timeout value
		mov	ah,IPC_WAIT_MUTEX_TIME_OUT	; Wait mutex
		int	LOCAL_IPC
		pop	ebx				; Restore context
		pop	ecx
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
