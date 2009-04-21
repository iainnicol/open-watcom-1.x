;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosSetTime
;
; DECLARATION	void BiosSetTime( TIME *time );
;
PROC		BiosSetTime		WATCOM_C
		push	edx				; Save context
		push	ecx
		mov	ch,[(TIME eax).Hour]		; CH = new hour
		mov	cl,[(TIME eax).Minute]		; CL = new minute
		mov	dh,[(TIME eax).Second]		; DH = new second
		mov	ah,TIMER_SET_CMOS_TIME		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		pop	ecx				; Restore context
		pop	edx
		ret
ENDP
		END
