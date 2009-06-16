;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosGetDate
;
; DECLARATION	void BiosGetDate( DATE *date );
;
PROC		BiosGetDate		WATCOM_C
		push	edx				; Save context
		push	ecx
		push	ebx
		mov	ebx,eax				; EBX points to DATE block
		mov	ah,TIMER_GET_CMOS_DATE		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	[(DATE ebx).Century],ch		; Store century
		mov	[(DATE ebx).Year],cl		; Store year
		mov	[(DATE ebx).Month],dh		; Store month
		mov	[(DATE ebx).Day],dl		; Store day
		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		ret
ENDP
		END
