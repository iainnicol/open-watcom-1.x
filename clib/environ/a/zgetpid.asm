;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	getpid_
;
; DECLARATION	int getpid( void );
;
PROC		getpid_			STDCALL
		mov	eax,[_PID]			; Return process ID
		ret
ENDP
		UDATASEG
		EXTRN	C _PID				: DWORD
		END
