;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	dosexterr
;
; Assembly variant of _DOSERROR structure
;
STRUC		DOSERROR
ErrorCode	DD	?
ClassCode	DB	?
ActionCode	DB	?
LocusCode	DB	?
ENDS
;
; DECLARATION	int dosexterr( struct _DOSERROR *doserr );
;
PROC		dosexterr		WATCOM_C
		USES	edx
		mov	edx,eax				; EDX points to ERROR structure
		mov	[(DOSERROR edx).ClassCode],13	; Unknown class
		mov	[(DOSERROR edx).ActionCode],1	; Retry operation
		mov	[(DOSERROR edx).LocusCode],1 	; Unknown locus
		mov	eax,[doserrno]			; EAX = dos error code
		mov	[(DOSERROR edx).ErrorCode],eax	; Store error code in callers structure
		ret
ENDP
		UDATASEG
		EXTRN	WATCOM_C doserrno		: DWORD
		END
