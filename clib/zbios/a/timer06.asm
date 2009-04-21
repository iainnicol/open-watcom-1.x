;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosSetAlarm
;
; DECLARATION	int BiosSetAlarm( TIME *time );
;
PROC		BiosSetAlarm		WATCOM_C
		xor	eax,eax				; Clear EAX
		push	edx				; Save context
		push	ecx
		push	eax
		mov	ch,[(TIME eax).Hour]		; CH = new hour
		mov	cl,[(TIME eax).Minute]		; CL = new minute
		mov	dh,[(TIME eax).Second]		; DH = new second
		mov	ah,TIMER_SET_CMOS_ALARM		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		pop	eax				; Restore context
		pop	ecx
		pop	edx
		sbb	eax,0				; Return 0 or -1
		ret
ENDP
		END
