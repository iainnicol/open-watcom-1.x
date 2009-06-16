;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
IFNDEF __ZDOSDRV__
		EXTRN	DosError			: PROC
ENDIF
		PUBLIC	DosGetChildReturnCode
;
; DECLARATION	int DosGetChildReturnCode( int PID );
;
PROC		DosGetChildReturnCode	WATCOM_C
IFDEF __ZDOSDRV__
		xor	eax,eax				; Clear EAX
ELSE
		push	edx				; Save context
		mov	edx,eax				; EDX = PID to wait for
		mov	ah,DOS_GET_CHILD_RETURNCODE	; AH = DOS function
		int	DOS
		pop	edx				; Restore context
		jc	DosError			; Success ?
ENDIF
		ret					; Yes, return exit code
ENDP
		END
