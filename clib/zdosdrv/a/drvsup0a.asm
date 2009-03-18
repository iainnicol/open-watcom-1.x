;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		EXTRN	DosError			: PROC
		PUBLIC	DosAllocateV86FarTrap_
;
; DECLARATION	int DosAllocateV86FarTrap( void ( *handler )( EXCEPTION * ),
;                                          unsigned *callback );
;
PROC		DosAllocateV86FarTrap_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to service routine
		call	[DWORD AllocV86FarTrap]		; Allocate callback trap
		mov	[edx],ebx			; Save callback segment:offset
		pop	ebx				; Restore context
		jc	DosError			; Success
		ret					; Return callback handle
ENDP
		END
