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
		EXTRN	WATCOM_C __set_EINVAL		: PROC
		PUBLIC	_dos_setdate
;
; DECLARATION	unsigned _dos_getdate( struct dosdate_t *date );
;
PROC		_dos_setdate		WATCOM_C
		USES	edx,ecx,ebx
		mov	ebx,eax				; EBX points to buffer
		mov	al,[(DOSDATE ebx).DayOfWeek]	; AL = day of week
		movzx	ecx,[(DOSDATE ebx).Year]	; ECX = year
		mov	dh,[(DOSDATE ebx).Month]	; DL = month
		mov	dl,[(DOSDATE ebx).Day]		; DL = day
		mov	ah,DOS_SET_DATE			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movsx	eax,al				; Signextend return code
		or	eax,eax				; Error ?
		jns	SHORT @@Exit			; No, we are done
		call	__set_EINVAL			; Yes, set _errno
@@Exit:		ret
ENDP
		END
