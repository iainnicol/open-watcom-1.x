;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosGetProcessPath
;
; DECLARATION	int DosGetProcessPath( char *buffer );
;
PROC		DosGetProcessPath	WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX points to buffer
		mov	ah,DOS_GET_PROCESS_PATH		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Success ?
		ret					; Yes, return length
ENDP
		END
