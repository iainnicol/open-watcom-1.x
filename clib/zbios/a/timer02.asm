;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	BiosGetTime_
;
; DECLARATION	void BiosGetTime( TIME *time );
;
PROC		BiosGetTime_		STDCALL
		push	edx				; Save context
		push	ecx
		push	ebx
		mov	ebx,eax				; EBX points to TIME block
		mov	ah,TIMER_GET_CMOS_TIME		; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosTimer]
ELSE
		int	BIOS_TIMER
ENDIF
		mov	[(TIME ebx).Hour],ch		; Store hour
		mov	[(TIME ebx).Minute],cl		; Store minute
		mov	[(TIME ebx).Second],dh		; Store second
		mov	[(TIME ebx).Daylight],dl	; Store daylight saving flag
		pop	ebx				; Restore context
		pop	ecx
		pop	edx
		ret
ENDP
		END
