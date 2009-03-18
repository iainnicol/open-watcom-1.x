;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosUnlockDevice_
;
; DECLARATION	void DosUnlockDevice( DEVLOCK *devicelock );
;
PROC		DosUnlockDevice_	STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to DEVLOCK block
		call	[DWORD UnlockDevice]		; Unlock device
		pop	ebx				; Restore context
		ret
ENDP
		END
