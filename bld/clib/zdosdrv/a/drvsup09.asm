;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetIvtVector_
;
; DECLARATION	void DosSetIvtVector( int intnum, unsigned vector );
;
PROC		DosSetIvtVector_	STDCALL
		USES	ecx,ebx
		mov	ebx,edx				; EBX = IVT vector
		movzx	ecx,al				; ECX = vector number
		call	[DWORD SetIvtVector]		; Set vector
		ret
ENDP
		END
