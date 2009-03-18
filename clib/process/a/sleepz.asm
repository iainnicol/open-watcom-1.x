;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	sleep_
;
; DECLARATION	void sleep( unsigned seconds );
;
PROC		sleep_			STDCALL
		shl	eax,10				; Convert seconds to periodic ticks
IFDEF __ZDOSDRV__
		call	[DWORD ThreadSleep]		; Sleep
ELSE
		push	edx				; Save context
		mov	edx,eax				; EDX = ticks
		mov	ah,THREAD_SLEEP			; Sleep
		int	THREAD
		pop	edx				; Restore context
ENDIF
		ret
ENDP
		END
