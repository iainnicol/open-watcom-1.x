;
; ZDOS run time library function.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		CODESEG
		PUBLIC	getpid
;
; DECLARATION	int getpid( void );
;
PROC		getpid			WATCOM_C
		mov	eax,[_PID]			; Return process ID
		ret
ENDP
		UDATASEG
		EXTRN	WATCOM_C _PID			: DWORD
		END
