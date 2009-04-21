;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosFreePciBuffer
;
; DECLARATION	int DosFreePciBuffer( void *linear );
;
PROC		DosFreePciBuffer	WATCOM_C
		call	[DWORD FreePciBlock]		; Free block
		jmp	DosReturnZero			; Process return code
ENDP
		END
