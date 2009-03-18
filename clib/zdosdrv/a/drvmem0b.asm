;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosCopyBytes_
;
; DECLARATION	int DosCopyBytes( void *dst, void *src, size_t length );
;
PROC		DosCopyBytes_		STDCALL
		xor	eax,eax				; Clear EAX
		call	[DWORD CopyBytes]		; Copy bytes
		sbb	eax,0				; EAX = return value (-1 on error, 0 on success)
		ret
ENDP
		END
