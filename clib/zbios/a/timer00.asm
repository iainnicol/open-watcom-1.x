;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosGetTickCount
;
; DECLARATION	int BiosGetTickCount( unsigned *tickcount );
;
PROC		BiosGetTickCount	WATCOM_C
		push	edx				; Save context
		push	ecx
		mov	ecx,eax				; ECX = pointer to tickcount variable
		mov	ah,TIMER_GET_TICK_COUNT		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	[ecx],edx			; Store tick count
		pop	ecx				; Restore context
		pop	edx
		ret					; Return rolled over flag
ENDP
		END
