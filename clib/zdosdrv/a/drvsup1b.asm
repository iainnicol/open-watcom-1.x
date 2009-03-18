;
; Copyright (C) 2005 Zebor Technology.
;
		IDEAL
		P486
		MODEL	USE32 SMALL
		INCLUDE	'ZDOSAPI.INC'
		INCLUDE	'ZDOSDRV.INC'
		CODESEG
		PUBLIC	DosEndOfInterrupt_
;
; DECLARATION	int DosEndOfInterrupt( int irq );
;
PROC		DosEndOfInterrupt_	STDCALL
		call	[DWORD DosEOI]			; Acknowledge interrupt(s)
		xor	eax,eax				; Clear EAX
		ret
ENDP
		END
