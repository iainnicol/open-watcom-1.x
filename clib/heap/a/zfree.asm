;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	free_
		PUBLIC	_nfree_
;
; DECLARATION	void free( void *ptr );
;
PROC		free_			STDCALL
LABEL		_nfree_			PROC
		jmp	[DWORD FreeBlock]		; Free block
ENDP
		END
