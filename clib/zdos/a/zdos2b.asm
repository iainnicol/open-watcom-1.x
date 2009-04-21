;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetDate
;
; DECLARATION	int DosSetDate( DATE *date );
;
PROC		DosSetDate		WATCOM_C
		USES	edx,ecx
		mov	ecx,[(DATE eax).Year]		; ECX = year
		mov	dh,[(DATE eax).Month]		; DH = month
		mov	dl,[(DATE eax).Day]		; DL = day
		mov	ah,DOS_SET_DATE			; AH = DOS function
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
