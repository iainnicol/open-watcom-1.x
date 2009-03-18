;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeHeapBlock_
;
; DECLARATION	int DosFreeHeapBlock( void *block );
;
PROC		DosFreeHeapBlock_	STDCALL
		call	[DWORD FreeBlock]		; Free heap block
		jmp	DosReturnZero			; Process return code
ENDP
		END
