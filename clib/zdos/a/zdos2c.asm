;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetTime_
;
; DECLARATION	int DosGetTime( TIME *time );
;
PROC		DosGetTime_		STDCALL
		USES	edx,ecx,ebx
		mov	ebx,eax				; EBX points to TIME block
		mov	ah,DOS_GET_TIME			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[(TIME ebx).Hours],ch		; Store hours
		mov	[(TIME ebx).Minutes],cl		; Store minutes
		mov	[(TIME ebx).Seconds],dh		; Store seconds
		mov	[(TIME ebx).Hundredths],dl	; Store hundredths
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
