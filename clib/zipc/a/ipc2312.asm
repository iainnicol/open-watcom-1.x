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
		PUBLIC	DosClearGlobalEvent
;
; DECLARATION	int DosClearGlobalEvent( unsigned bitmask, int handle );
;
PROC		DosClearGlobalEvent	WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = bitmask
		mov	ebx,edx				; EBX = event handle
		mov	ah,IPC_CLEAR_EVENT		; Clear event
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		END
