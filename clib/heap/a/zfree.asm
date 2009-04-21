;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	free
		PUBLIC	WATCOM_C _nfree
;
; DECLARATION	void free( void *ptr );
;
PROC		free			WATCOM_C
LABEL		_nfree			PROC
		jmp	[DWORD FreeBlock]		; Free block
ENDP
		END
