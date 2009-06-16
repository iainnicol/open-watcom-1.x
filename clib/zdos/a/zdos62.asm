;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetPID
;
; DECLARATION	int DosGetPID( void );
;
PROC		DosGetPID		WATCOM_C
		mov	ah,DOS_GET_PID			; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		jmp	[DWORD DosApi]
ELSE
		int	DOS
		ret
ENDIF
ENDP
		END
