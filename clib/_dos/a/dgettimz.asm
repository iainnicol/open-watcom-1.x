;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
;
; Assembler variant of dostime_t
;
STRUC		DOSTIME
Hour		DB	?
Minute		DB	?
Second		DB	?
Hundredth	DB	?
ENDS
		CODESEG
		PUBLIC	_dos_gettime
;
; DECLARATION	void _dos_gettime( struct dostime_t *time );
;
PROC		_dos_gettime		WATCOM_C
		USES	edx,ecx,ebx
		mov	ebx,eax				; EBX points to buffer
		mov	ah,DOS_GET_TIME			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[(DOSTIME ebx).Hour],ch		; Store hour
		mov	[(DOSTIME ebx).Minute],cl	; Store minute
		mov	[(DOSTIME ebx).Second],dh	; Store second
		mov	[(DOSTIME ebx).Hundredth],dl	; Store hundredth
		ret
ENDP
		END
