;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosLockDevice_
;
; DECLARATION	int DosLockDevice( DEVLOCK *devicelock );
;
PROC		DosLockDevice_		STDCALL
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to DEVLOCK block
		call	[DWORD LockDevice]		; Lock device
		pop	ebx				; Restore context
		ret
ENDP
		END
