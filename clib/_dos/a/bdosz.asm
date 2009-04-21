;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	bdos
;
; DECLARATION	int bdos( unsigned service, unsigned edx, unsigned char al );
;
PROC		bdos		WATCOM_C
		USES	edi,esi,ecx
		mov	ah,al				; AH = DOS function
		mov	al,bl				; Get register AL
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		ret
ENDP
		END
