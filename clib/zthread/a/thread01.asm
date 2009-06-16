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
		PUBLIC	DosDeleteThread
;
; DECLARATION	int DosDeleteThread( int TID );
;
PROC		DosDeleteThread		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = thread ID
		;
		; Delete thread
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadDelete]
ELSE
		mov	ah,THREAD_DELETE
		int	THREAD
ENDIF
		pop	edx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
