;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosAllocateV86IntTrap
;
; DECLARATION	int DosAllocateV86IntTrap( void ( *handler )( EXCEPTION * ),
;                                          unsigned *callback );
;
PROC		DosAllocateV86IntTrap	WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to service routine
		call	[DWORD AllocV86IntTrap]		; Allocate callback trap
		mov	[edx],ebx			; Save callback segment:offset
		pop	ebx				; Restore context
		jc	DosError			; Success
		ret					; Return callback handle
ENDP
		END
