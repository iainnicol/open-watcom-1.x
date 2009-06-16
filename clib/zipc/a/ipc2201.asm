;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosOpenMutex
;
; DECLARATION	int DosOpenMutex( MUTEX *mutex );
;
PROC		DosOpenMutex		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
		;
		; Open mutex
		;
IFDEF __ZDOSDRV__
		call	[DWORD MutexOpen]
ELSE
		mov	ah,IPC_OPEN_MUTEX
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
