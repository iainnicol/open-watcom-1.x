;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeUserTrap_
;
; DECLARATION	int DosFreeUserTrap( int handle );
;
PROC		DosFreeUserTrap_	STDCALL
		call	[DWORD FreeUserTrap]		; Free callback trap
		jmp	DosReturnZero			; Process return code
ENDP
		END
