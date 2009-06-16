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
		PUBLIC	BiosWait
;
; DECLARATION	int BiosWait( unsigned microseconds );
;
PROC		BiosWait		WATCOM_C
		push	edx				; Save context
		mov	edx,eax				; EDX = number of micro seconds to wait
		mov	ah,MISC_WAIT			; AH = function number
		;
		; Call BIOS
		;
IFDEF __ZDOSDRV__
		call	[DWORD BiosMisc]
ELSE
		int	BIOS_MISC
ENDIF
		pop	edx				; Restore context
		jmp	BiosReturnZero			; Process return code
ENDP
		END
