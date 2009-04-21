;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosSignalMutex
;
; DECLARATION	int DosSignalMutex( MUTEX *mutex );
;
PROC		DosSignalMutex		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
IFDEF __ZDOSDRV__
		clc					; Clear carry flag
		call	[DWORD MutexUnlock]		; Signal mutex
ELSE
		mov	ah,IPC_SIGNAL_MUTEX		; Signal mutex
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
