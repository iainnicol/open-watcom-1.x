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
		PUBLIC	BiosExtendedMemorySize_
;
; DECLARATION	int BiosExtendedMemorySize( void );
;
PROC		BiosExtendedMemorySize_	STDCALL
		mov	ah,MISC_EXTENDED_MEMSIZE	; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		ret					; Return memory size in KB
ENDP
		END
