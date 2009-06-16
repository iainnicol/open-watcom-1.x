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
		PUBLIC	DosSetGlobalEvent
;
; DECLARATION	int DosSetGlobalEvent( unsigned bitmask, int handle );
;
PROC		DosSetGlobalEvent	WATCOM_C
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = bitmask
		mov	ebx,edx				; EBX = event handle
		mov	ah,IPC_SET_EVENT		; Set event
		int	GLOBAL_IPC
		pop	ebx				; Restore context
		pop	ecx
		jmp	DosReturnZero			; Process return code
ENDP
		END
