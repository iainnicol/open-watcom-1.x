;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOS.INC'
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosReturnZero			: PROC
		PUBLIC	DosUnlockCpu
;
; DECLARATION	int DosUnlockCpu( MUTEX *mutex );
;
PROC		DosUnlockCpu		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to mutex
		clc					; Clear carry flag
		call	[DWORD UnlockCpu]		; Unlock CPU
		pop	ebx				; Restore context
		jmp	DosReturnZero			; Process return code
ENDP
		END
