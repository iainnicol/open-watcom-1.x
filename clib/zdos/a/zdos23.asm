;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosGetEnvVariable
;
; DECLARATION	int DosGetEnvVariable( char *name, char *buffer );
;
PROC		DosGetEnvVariable	WATCOM_C
		push	edi				; Save context
		mov	edi,edx				; EDI points to buffer
		mov	edx,eax				; EDX points to variable name
		mov	ah,DOS_GET_ENVIRONMENT_VARIABLE	; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edi				; Restore context
		jc	DosError			; Succes ?
		ret					; Yes, return length in EAX
ENDP
		END
