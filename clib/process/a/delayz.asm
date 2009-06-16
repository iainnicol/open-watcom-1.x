;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	delay
;
; DECLARATION	void delay( unsigned milliseconds );
;
PROC		delay			WATCOM_C
		push	edx				; Save context
		mov	edx,1000			; EDX = number of milliseconds in one second
		mul	edx				; EDX:EAX = number of milliseconds * 1000
		shrd	eax,edx,10			; EAX = corresponding number of periodic ticks
IFDEF __ZDOSDRV__
		call	[DWORD ThreadSleep]		; Sleep
ELSE
		mov	edx,eax				; EDX = ticks
		mov	ah,THREAD_SLEEP			; Sleep
		int	THREAD
ENDIF
		pop	edx				; Restore context
		ret
ENDP
		END
