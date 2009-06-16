;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosAllocateUserTrap
;
; DECLARATION	int DosAllocateUserTrap( void ( *handler )( EXCEPTION * ),
;                                        unsigned *callback );
;
PROC		DosAllocateUserTrap	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to service routine
		call	[DWORD AllocUserTrap]		; Allocate callback trap
		mov	[edx],ebx			; Save callback offset
		pop	ebx				; Restore context
		jc	DosError			; Success
		ret					; Return callback handle
ENDP
		END
