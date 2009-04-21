;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosSetDate
;
; DECLARATION	void BiosSetDate( DATE *date );
;
PROC		BiosSetDate		WATCOM_C
		push	edx				; Save context
		push	ecx
		mov	ch,[(DATE eax).Century]		; CH = new century
		mov	cl,[(DATE eax).Year]		; CL = new year
		mov	dh,[(DATE eax).Month]		; DH = new month
		mov	dl,[(DATE eax).Day]		; DL = new day
		mov	ah,TIMER_SET_CMOS_DATE		; AH = function number
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
