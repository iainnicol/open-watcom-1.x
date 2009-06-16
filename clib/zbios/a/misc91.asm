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
		PUBLIC	BiosDeviceReady
;
; DECLARATION	int BiosDeviceReady( void );
;
PROC		BiosDeviceReady		WATCOM_C
		mov	ah,MISC_DEVICE_READY		; AH = function number
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
