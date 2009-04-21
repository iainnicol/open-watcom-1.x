;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosCopyWords
;
; DECLARATION	int DosCopyWords( void *dst, void *src, size_t length );
;
PROC		DosCopyWords		WATCOM_C
		xor	eax,eax				; Clear EAX
		shr	ecx,2				; ECX = number of dwords to copy
		call	[DWORD CopyWords]		; Copy words
		sbb	eax,0				; EAX = return value (-1 on error, 0 on success)
		ret
ENDP
		END
