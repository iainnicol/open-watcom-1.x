;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosElapsedPeriodicTicks
;
; DECLARATION	unsigned DosElapsedPeriodicTicks( unsigned referencetime );
;
PROC		DosElapsedPeriodicTicks WATCOM_C
		USES	edx
		mov	edx,eax				; EDX = reference time
		mov	ah,DOS_ELAPSED_PERIODIC_TICKS	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret					; Return elapsed time
ENDP
		END
