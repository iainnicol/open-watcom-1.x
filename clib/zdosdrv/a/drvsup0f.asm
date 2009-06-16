;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosHookPageFaultTrap
;
; DECLARATION	void ( *DosHookPageFaultTrap( ( void *handler )() ) )();
;
PROC		DosHookPageFaultTrap	WATCOM_C
		jmp	[DWORD TrapPageFault]		; Install new handler and return pointer to previous handler
ENDP
		END
