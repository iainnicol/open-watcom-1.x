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
		PUBLIC	DosDelayTime_
;
; DECLARATION	int DosDelayTime( int hours, int seconds,
;		                  int minutes, int hundredths );
;
PROC		DosDelayTime_		STDCALL
		mov	bh,al				; BH = hours
		mov	ch,dl				; CH = seconds
		;
		; Sleep
		;
IFDEF __ZDOSDRV__
		call	[DWORD ThreadDelayTime]
ELSE
		mov	ah,THREAD_DELAY_TIME
		int	THREAD
ENDIF
		jc	DosError			; Success ?
		ret					; Yes, return 0
ENDP
		END
