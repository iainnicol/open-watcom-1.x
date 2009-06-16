;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZBIOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	BiosReturnZero			: PROC
		PUBLIC	BiosExtendedMemorySize
;
; DECLARATION	int BiosExtendedMemorySize( void );
;
PROC		BiosExtendedMemorySize	WATCOM_C
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
