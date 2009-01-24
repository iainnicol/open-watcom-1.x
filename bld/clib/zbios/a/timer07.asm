;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosResetAlarm_
;
; DECLARATION	int BiosResetAlarm( void );
;
PROC		BiosResetAlarm_		STDCALL
		xor	eax,eax				; Clear EAX
		push	eax				; Save context
		mov	ah,TIMER_RESET_CMOS_ALARM	; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		pop	eax				; Restore context
		sbb	eax,0				; Return 0 or -1
		ret
ENDP
		END
