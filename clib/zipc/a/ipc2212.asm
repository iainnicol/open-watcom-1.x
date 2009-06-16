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
		PUBLIC	DosClearEvent
;
; DECLARATION	int DosClearEvent( unsigned bitmask, EVENT *event );
;
PROC		DosClearEvent		WATCOM_C
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	ebx,edx				; EBX points to event
		call	[DWORD EventClear]		; Clear event
		pop	ebx				; Restore context
ELSE
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = bitmask
		mov	ebx,edx				; EBX points to event
		mov	ah,IPC_CLEAR_EVENT		; Clear event
		int	LOCAL_IPC
		pop	ebx				; Restore context
		pop	ecx
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
