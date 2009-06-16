;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreeHeapBlock
;
; DECLARATION	int DosFreeHeapBlock( void *block );
;
PROC		DosFreeHeapBlock	WATCOM_C
		call	[DWORD FreeBlock]		; Free heap block
		jmp	DosReturnZero			; Process return code
ENDP
		END
