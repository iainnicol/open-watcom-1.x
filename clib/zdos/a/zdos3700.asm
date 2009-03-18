;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetSwitchCharacter_
;
; DECLARATION	int DosGetSwitchCharacter( void );
;
PROC		DosGetSwitchCharacter_	STDCALL
		USES	edx
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_SWITCH_CHARACTER SHL 8
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movzx	eax,dl				; EAX = switch character
		ret
ENDP
		END
