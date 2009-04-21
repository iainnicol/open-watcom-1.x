;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosCancelEventWait
;
; DECLARATION	int BiosCancelEventWait( void );
;
PROC		BiosCancelEventWait	WATCOM_C
		mov	eax,MISC_EVENT_WAIT SHL 8 + 1	; AH = function number, AL = subfunction number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		jmp	BiosReturnZero			; Process return code
ENDP
		END
