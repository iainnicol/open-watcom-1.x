;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
;
; Assembler variant of dosdate_t
;
STRUC		DOSDATE
Day		DB	?
Month		DB	?
Year		DW	?
DayOfWeek	DB	?
ENDS
		CODESEG
		PUBLIC	_dos_getdate_
;
; DECLARATION	void _dos_getdate( struct dosdate_t *date );
;
PROC		_dos_getdate_		STDCALL
		USES	edx,ecx,ebx
		mov	ebx,eax				; EBX points to buffer
		mov	ah,DOS_GET_DATE			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		mov	[(DOSDATE ebx).DayOfWeek],al	; Store day of week
		mov	[(DOSDATE ebx).Year],cx		; Store year
		mov	[(DOSDATE ebx).Month],dh	; Store month
		mov	[(DOSDATE ebx).Day],dl		; Store day
		ret
ENDP
		END
