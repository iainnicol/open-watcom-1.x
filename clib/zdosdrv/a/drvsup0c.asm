;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeV86Trap_
;
; DECLARATION	int DosFreeV86Trap( int handle );
;
PROC		DosFreeV86Trap_		STDCALL
		call	[DWORD FreeV86Trap]		; Free callback trap
		jmp	DosReturnZero			; Process return code
ENDP
		END
