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
		PUBLIC	DosTraceSingleStep
;
; DECLARATION	int DosTraceSingleStep( int *event, TCPU *context );
;
PROC		DosTraceSingleStep	WATCOM_C
		push	edi				; Save context
		push	edx
		push	ebx
		mov	ebx,eax				; EBX points to event variable
		mov	edi,edx				; EDI points to context buffer
		mov	ah,TRACE_SINGLE_STEP_CLIENT	; Single step client
		int	TRACE
		mov	[ebx],edx			; Save event value
		pop	ebx				; Restore context
		pop	edx
		pop	edi
		jc	DosError			; Success ?
		ret					; Yes, return TID
ENDP
		END
