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
		PUBLIC	DosDelayMicroSeconds
;
; DECLARATION	int DosDelayMicroSeconds( unsigned microseconds );
;
PROC		DosDelayMicroSeconds	WATCOM_C
IFDEF __ZDOSDRV__
		call	[DWORD ThreadDelayMS]		; Sleep
ELSE
		push	edx				; Save context
		mov	edx,eax				; EDX = micro seconds
		mov	ah,THREAD_DELAY_MICRO_SECONDS	; Sleep
		int	THREAD
		pop	edx				; Restore context
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
