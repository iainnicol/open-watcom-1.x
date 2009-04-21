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
		EXTRN	WATCOM_C __set_EINVAL		: PROC
		PUBLIC	_dos_settime
;
; DECLARATION	unsigned _dos_settime( struct dostime_t *time );
;
PROC		_dos_settime		WATCOM_C
		USES	edx,ecx,ebx
		mov	ebx,eax				; EBX points to buffer
		mov	ch,[(DOSTIME ebx).Hour]		; CH = hour
		mov	cl,[(DOSTIME ebx).Minute]	; CL = minute
		mov	dh,[(DOSTIME ebx).Second]	; DH = second
		mov	dl,[(DOSTIME ebx).Hundredth]	; DL = hundredth
		mov	ah,DOS_SET_TIME			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movsx	eax,al				; Sign extend return code
		or	eax,eax				; Error ?
		jns	SHORT @@Exit			; No, we are done
		call	__set_EINVAL			; Yes, set _errno
@@Exit:		ret
ENDP
		END
