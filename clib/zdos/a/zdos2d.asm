;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetTime
;
; DECLARATION	int DosSetTime( TIME *time );
;
PROC		DosSetTime		WATCOM_C
		USES	edx,ecx
		mov	ch,[(TIME eax).Hours]		; CH = hours
		mov	cl,[(TIME eax).Minutes]		; CL = minutes
		mov	dh,[(TIME eax).Seconds]		; DH = seconds
		mov	dl,[(TIME eax).Hundredths]	; DL = hundredths
		mov	ah,DOS_SET_TIME			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movsx	eax,al				; Return 0 or -1
		ret
ENDP
		END
