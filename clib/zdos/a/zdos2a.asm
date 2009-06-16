;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetDate
;
; DECLARATION	int DosGetDate( DATE *date );
;
PROC		DosGetDate		WATCOM_C
		USES	edx,ecx,ebx
		mov	ebx,eax				; EBX points to DATE block
		mov	ah,DOS_GET_DATE			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[(DATE ebx).Year],ecx		; Store year
		mov	[(DATE ebx).Month],dh		; Store month
		mov	[(DATE ebx).Day],dl		; Store day
		mov	[(DATE ebx).DayOfWeek],al	; Store day of week
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
