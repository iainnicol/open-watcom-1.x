;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnAL			: PROC
		PUBLIC	DosAuxiliaryInput_
;
; DECLARATION	int DosAuxiliaryInput( void );
;
PROC		DosAuxiliaryInput_	STDCALL
		mov	ah,DOS_AUXILIARY_INPUT		; AH = DOS function
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		jmp	DosReturnAL			; Process return code
ENDP
		END
