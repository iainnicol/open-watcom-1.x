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
		PUBLIC	DosOpenEvent
;
; DECLARATION	int DosOpenEvent( EVENT *event, unsigned value );
;
PROC		DosOpenEvent		WATCOM_C
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to event
		mov	eax,edx				; EAX = initial event value
		call	[DWORD EventOpen]		; Open event
		pop	ebx				; Restore context
ELSE
		push	ecx				; Save context
		push	ebx
		mov	ecx,edx				; ECX = initial event value
		mov	ebx,eax				; EBX points to event
		mov	ah,IPC_OPEN_EVENT		; Open event
		int	LOCAL_IPC
		pop	ebx				; Restore context
		pop	ecx
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
