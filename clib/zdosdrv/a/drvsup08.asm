;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosGetIvtVector_
;
; DECLARATION	unsigned DosGetIvtVector( int i );
;
PROC		DosGetIvtVector_	STDCALL
		USES	ecx,ebx
		movzx	ecx,al				; ECX = vector number
		call	[DWORD GetIvtVector]		; Get vector
		mov	eax,ebx				; EAX = interrupt vector
		ret
ENDP
		END
