;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosSetIvtVector
;
; DECLARATION	void DosSetIvtVector( int intnum, unsigned vector );
;
PROC		DosSetIvtVector		WATCOM_C
		USES	ecx,ebx
		mov	ebx,edx				; EBX = IVT vector
		movzx	ecx,al				; ECX = vector number
		call	[DWORD SetIvtVector]		; Set vector
		ret
ENDP
		END
