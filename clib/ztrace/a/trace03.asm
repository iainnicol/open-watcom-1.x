;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosTraceRun
;
; DECLARATION	int DosTraceRun( int *event, TCPU *context );
;
PROC		DosTraceRun		WATCOM_C
		push	edi				; Save context
		push	edx
		push	ebx
		mov	ebx,eax				; EBX points to event variable
		mov	edi,edx				; EDI points to context buffer
		mov	ah,TRACE_RUN_CLIENT		; Run client
		int	TRACE
		mov	[ebx],edx			; Save event value
		pop	ebx				; Restore context
		pop	edx
		pop	edi
		jc	DosError			; Success ?
		ret					; Yes, return TID
ENDP
		END
