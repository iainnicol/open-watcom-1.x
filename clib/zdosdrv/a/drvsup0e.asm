;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeUserTrap
;
; DECLARATION	int DosFreeUserTrap( int handle );
;
PROC		DosFreeUserTrap		WATCOM_C
		call	[DWORD FreeUserTrap]		; Free callback trap
		jmp	DosReturnZero			; Process return code
ENDP
		END
