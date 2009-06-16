;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeV86Trap
;
; DECLARATION	int DosFreeV86Trap( int handle );
;
PROC		DosFreeV86Trap		WATCOM_C
		call	[DWORD FreeV86Trap]		; Free callback trap
		jmp	DosReturnZero			; Process return code
ENDP
		END
