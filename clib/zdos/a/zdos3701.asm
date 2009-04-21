;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetSwitchCharacter
;
; DECLARATION	int DosSetSwitchCharacter( int character );
;
PROC		DosSetSwitchCharacter	WATCOM_C
		USES	edx
		mov	dl,al				; DL = new switch character
		;
		; Get DOS function numbers in AH and AL
		;
		mov	eax,DOS_GET_SET_SWITCH_CHARACTER SHL 8 + 1
		;
		; Call DOS services
		;
IFDEF __ZDOSDRV__
		call	[DWORD DosApi]
ELSE
		int	DOS
ENDIF
		movsx	eax,al				; EAX = return code
		ret
ENDP
		END
