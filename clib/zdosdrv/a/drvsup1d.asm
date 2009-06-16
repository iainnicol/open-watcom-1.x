;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosLockDevice
;
; DECLARATION	int DosLockDevice( DEVLOCK *devicelock );
;
PROC		DosLockDevice		WATCOM_C
		push	ebx				; Save context
		mov	ebx,eax				; EBX points to DEVLOCK block
		call	[DWORD LockDevice]		; Lock device
		pop	ebx				; Restore context
		ret
ENDP
		END
