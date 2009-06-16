;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosCloseEvent
;
; DECLARATION	int DosCloseEvent( EVENT *event );
;
PROC		DosCloseEvent		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to event
		;
		; Close event
		;
IFDEF __ZDOSDRV__
		call	[DWORD EventClose]
ELSE
		mov	ah,IPC_CLOSE_EVENT
		int	LOCAL_IPC
ENDIF
		pop	ebx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return number of tasks waiting
ENDP
		END
