;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		CODESEG
		PUBLIC	DosHookPageFaultTrap_
;
; DECLARATION	void ( *DosHookPageFaultTrap( ( void *handler )() ) )();
;
PROC		DosHookPageFaultTrap_	STDCALL
		jmp	[DWORD TrapPageFault]		; Install new handler and return pointer to previous handler
ENDP
		END
