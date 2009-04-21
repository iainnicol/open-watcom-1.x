;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		EXTRN	WATCOM_C __filename_from_wide	: PROC
		EXTRN	WATCOM_C utime			: PROC
		PUBLIC	_wutime
;
; DECLARATION	int _wutime( char* path, struct utimbuf *times );
;
PROC		_wutime			WATCOM_C
		USES	ecx
		LOCAL	Path [80] : BYTE
		mov	ecx,edx				; Save pointer to utimbuf buffer in ECX
		mov	edx,eax				; EDX points to wide character path
		lea	eax,[Path]			; EAX points to byte character path
		call	__filename_from_wide		; Convert wide string to byte string
		mov	edx,ecx				; EDX points to utimebuf buffer
		lea	eax,[Path]			; EAX points to translated path
		call	utime				; Get time
		ret
ENDP
		END
