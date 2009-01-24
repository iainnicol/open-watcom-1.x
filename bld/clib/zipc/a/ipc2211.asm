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
		PUBLIC	DosSetEvent_
;
; DECLARATION	int DosSetEvent( unsigned bitmask, EVENT *event );
;
PROC		DosSetEvent_		STDCALL
IFDEF __ZDOSDRV__
		push	ebx				; Save context
		mov	ebx,edx				; EBX points to event
		call	[DWORD EventSet]		; Set event
		pop	ebx				; Restore context
ELSE
		push	ecx				; Save context
		push	ebx
		mov	ecx,eax				; ECX = bitmask
		mov	ebx,edx				; EBX points to event
		mov	ah,IPC_SET_EVENT		; Set event
		int	LOCAL_IPC
		pop	ebx				; Restore context
		pop	ecx
ENDIF
		jmp	DosReturnZero			; Process return code
ENDP
		END
