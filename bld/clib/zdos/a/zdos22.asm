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
		PUBLIC	DosEnvVariableLength_
;
; DECLARATION	int DosEnvVariableLength( char *name );
;
PROC		DosEnvVariableLength_	STDCALL
		push	edx				; Save context
		mov	edx,eax				; EDX points to variable name
		;
		; Get DOS function number in AH
		;
		mov	ah,DOS_ENVIRONMENT_VARIABLE_LENGTH
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		pop	edx				; Restore context
		jc	DosError			; Succes ?
		ret					; Yes, return length in EAX
ENDP
		END
