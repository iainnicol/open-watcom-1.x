;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	C _do_interrupt
;
; DECLARATION	void __cdecl _do_interrupt( int intno );
;
PROC		_do_interrupt
		push	eax				; Save context
		mov	eax,[esp + 8]			; EAX = interrupt number
IFDEF __ZDOSDRV__
		mov	eax,[KERNEL_BASE + eax * 4]	; EAX points to interrupt handler
ELSE
		lea	eax,[InterruptHandler + eax * 4]; EAX points to interrupt handler
ENDIF
		xchg	eax,[esp]			; Restore EAX and put pointer to handler on top of stack
		ret					; Invoke interrupt handler
IFNDEF __ZDOSDRV__
		ALIGN	4
LABEL		InterruptHandler	PROC
		INT_NUMBER = 0
		REPT	256
		ALIGN	4
		int	INT_NUMBER
		ret
		INT_NUMBER = INT_NUMBER + 1
		ENDM
ENDIF
ENDP
		END
