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
		PUBLIC	DosCreateThread
;
; DECLARATION	int DosCreateThread(int priority,unsigned ESP,unsigned EIP);
;
PROC		DosCreateThread		WATCOM_C
IFDEF __ZDOSDRV__
		call	[DWORD ThreadCreate]		; Create thread
ELSE
		push	ecx				; Save context
		mov	ecx,edx				; ECX = thread ESP
		mov	ah,THREAD_CREATE		; Create thread
		int	THREAD
		pop	ecx				; Restore context
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return thread ID
ENDP
		END
