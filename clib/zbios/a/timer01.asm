;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosSetTickCount_
;
; DECLARATION	void BiosSetTickCount( unsigned tickcount );
;
PROC		BiosSetTickCount_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX = tick count
		mov	ah,TIMER_SET_TICK_COUNT		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		pop	edx				; Restore context
		ret
ENDP
		END
