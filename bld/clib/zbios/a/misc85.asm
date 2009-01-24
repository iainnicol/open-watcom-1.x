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
		PUBLIC	BiosSystemRequest_
;
; DECLARATION	int BiosSystemRequest( int flag );
;
PROC		BiosSystemRequest_	STDCALL
		mov	ah,MISC_SYSTEM_REQUEST		; AH = function number
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
