;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		EXTRN	__filename_from_wide_		: PROC
		EXTRN	utime_				: PROC
		PUBLIC	_wutime_
;
; DECLARATION	int _wutime( char* path, struct utimbuf *times );
;
PROC		_wutime_		STDCALL
		USES	ecx
		LOCAL	Path [80] : BYTE
		mov	ecx,edx				; Save pointer to utimbuf buffer in ECX
		mov	edx,eax				; EDX points to wide character path
		lea	eax,[Path]			; EAX points to byte character path
		call	__filename_from_wide_		; Convert wide string to byte string
		mov	edx,ecx				; EDX points to utimebuf buffer
		lea	eax,[Path]			; EAX points to translated path
		call	utime_				; Get time
		ret
ENDP
		END
